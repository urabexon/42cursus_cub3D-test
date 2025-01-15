/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hurabe <hurabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:37:53 by hurabe            #+#    #+#             */
/*   Updated: 2024/07/15 21:16:18 by hurabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	char	*null_free(char	**n)
{
	free(*n);
	*n = NULL;
	return (NULL);
}

static char	*gnl_result(int num, char **buffer_s)
{
	char	*result;
	char	*save;

	save = NULL;
	if (num <= 0)
	{
		if (**buffer_s == '\0')
		{
			free(*buffer_s);
			*buffer_s = NULL;
			return (NULL);
		}
		result = *buffer_s;
		*buffer_s = NULL;
		return (result);
	}
	save = ft_substr(*buffer_s, num, BUFFER_SIZE);
	result = *buffer_s;
	result[num] = '\0';
	*buffer_s = save;
	return (result);
}

static char	*gnl_read(int fd, char **buffer_save, char *buffer)
{
	ssize_t	count_byte;
	char	*tmp;

	count_byte = 0;
	tmp = NULL;
	while (ft_strchr(*buffer_save, '\n') == NULL)
	{
		count_byte = read(fd, buffer, BUFFER_SIZE);
		if (count_byte < 0)
		{
			null_free(buffer_save);
			return (NULL);
		}
		if (count_byte == 0)
			return (gnl_result(count_byte, buffer_save));
		buffer[count_byte] = '\0';
		tmp = ft_strjoin(*buffer_save, buffer);
		if (tmp == NULL)
			return (null_free(buffer_save), NULL);
		null_free(buffer_save);
		*buffer_save = tmp;
	}
	return (gnl_result((ft_strchr(*buffer_save, '\n') \
	- *buffer_save) + 1, buffer_save));
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*str;
	char		*result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (str == NULL)
		return (NULL);
	if (!save)
	{
		save = ft_strdup("");
		if (save == NULL)
		{
			free(str);
			free(save);
			return (NULL);
		}
	}
	result = gnl_read(fd, &save, str);
	null_free(&str);
	return (result);
}
/*
int	main(void)
{
	int		fd;
	int		i;
	char	*str;

	fd = open("text.txt", O_RDONLY);
	i = 0;
	while (i < 6)
	{
		str = get_next_line(fd);
		printf("%s", str);
		free(str);
		i++;
	}
	close(fd);
	return (0);
}
*/