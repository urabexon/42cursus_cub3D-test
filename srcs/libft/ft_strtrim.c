/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hurabe <hurabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:08:23 by hurabe            #+#    #+#             */
/*   Updated: 2024/05/21 21:45:54 by hurabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_set(char const c, char const *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	const char	*str;
	const char	*end;
	char		*new;
	size_t		len;

	if (!s1 || !set)
		return (NULL);
	str = s1;
	while (*str && ft_set(*str, set))
		str++;
	end = s1 + ft_strlen(s1);
	while (end > str && ft_set(*(end - 1), set))
		end--;
	len = end - str;
	new = (char *)malloc(len + 1);
	if (!new)
		return (NULL);
	ft_strlcpy(new, str, len + 1);
	return (new);
}
