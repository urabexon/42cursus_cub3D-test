/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hurabe <hurabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 22:01:14 by hurabe            #+#    #+#             */
/*   Updated: 2025/01/25 19:22:08 by hurabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		if (is_include_char(remove. str[i]))
			str[i] = replace;
		i++;
	}
}
