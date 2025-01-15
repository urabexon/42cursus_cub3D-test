/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hurabe <hurabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:37:49 by hurabe            #+#    #+#             */
/*   Updated: 2024/07/08 16:37:05 by hurabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	t;

	t = 0;
	while (s[t] != '\0')
	{
		t++;
	}
	return (t);
}

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s != (char)c)
	{
		if (*s == '\0')
			return (NULL);
		s++;
	}
	return ((char *)s);
}

char	*ft_strdup(const char *s1)
{
	return (ft_substr(s1, 0, ft_strlen(s1)));
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str1;
	char	*str2;

	if (!s1 || !s2)
		return (NULL);
	str1 = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str1)
		return (NULL);
	str2 = str1;
	while (*s1)
		*str2++ = *s1++;
	while (*s2)
		*str2++ = *s2++;
	*str2 = '\0';
	return (str1);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	sub_len;
	size_t	i;

	if (!s)
		return (NULL);
	sub_len = ft_strlen(s);
	if (sub_len <= start)
	{
		substr = (char *)malloc(1);
		if (substr == NULL)
			return (NULL);
		substr[0] = '\0';
		return (substr);
	}
	if (sub_len < start + len)
		len = sub_len - start;
	substr = (char *)malloc((len + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	i = -1;
	while (++i < len && s[start + i])
		substr[i] = s[start + i];
	substr[i] = '\0';
	return (substr);
}
