/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hurabe <hurabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 22:01:14 by hurabe            #+#    #+#             */
/*   Updated: 2025/03/03 17:17:44 by hurabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_all(char **arr)
{
	size_t	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i] != 0)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

bool	is_include_char(char *s, int c)
{
	c = (char)c;
	while (*s)
	{
		if (*s == c)
			return (true);
		s++;
	}
	if (c == '\0')
		return (true);
	return (false);
}

void	replace_str(char *str, char *remove, char replace)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_include_char(remove, str[i]))
			str[i] = replace;
		i++;
	}
}

int	strarr_size(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}

bool	is_str_type(char *str, int (*function)(int))
{
	size_t	i;

	if (!str || !function)
		return (false);
	i = 0;
	while (str[i])
	{
		if (!function(str[i]))
			return (false);
		i++;
	}
	return (true);
}
