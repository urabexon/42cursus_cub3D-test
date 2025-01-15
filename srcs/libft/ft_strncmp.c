/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hurabe <hurabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:08:14 by hurabe            #+#    #+#             */
/*   Updated: 2024/05/21 21:29:17 by hurabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	strncmp_char(char c1, char c2)
{
	return ((unsigned char)c1 - (unsigned char)c2);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		result;

	i = 0;
	while (i < n && s1[i] && s2[i])
	{
		result = strncmp_char(s1[i], s2[i]);
		if (result != 0)
			return (result);
		i++;
	}
	if (i < n)
		if (s1[i] || s2[i])
			return (strncmp_char(s1[i], s2[i]));
	return (0);
}
