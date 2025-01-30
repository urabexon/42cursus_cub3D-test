/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hurabe <hurabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:06:22 by hurabe            #+#    #+#             */
/*   Updated: 2025/01/30 21:06:09 by hurabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	ft_handle_overflow(char *str, int sign)
{
	unsigned long	ret;
	unsigned long	over;
	int				digit;

	ret = 0;
	over = (unsigned long)LONG_MAX;
	while (ft_isdigit(*str))
	{
		digit = *str - '0';
		if (sign == 1 && ret > ((over - digit) / 10))
			return (LONG_MAX);
		if (sign == -1 && ret > ((over + 1 - digit) / 10))
			return (LONG_MIN);
		ret = ret * 10 + digit;
		str++;
	}
	return (ret);
}

int	ft_atoi(const char *str)
{
	int		sign;
	long	result;

	sign = 1;
	result = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		sign = -1;
		str++;
	}
	result = (int)ft_handle_overflow((char *)str, sign);
	return ((int)(result * sign));
}
