/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hurabe <hurabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:08:20 by hurabe            #+#    #+#             */
/*   Updated: 2024/05/17 17:08:29 by hurabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;
	int		i;

	ptr = NULL;
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			ptr = (char *)&s[i];
		i++;
	}
	if ((char)c == '\0')
		return ((char *)(&s[i]));
	return (ptr);
}
