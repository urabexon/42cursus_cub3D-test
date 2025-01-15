/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hurabe <hurabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:07:55 by hurabe            #+#    #+#             */
/*   Updated: 2024/05/21 21:31:35 by hurabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
