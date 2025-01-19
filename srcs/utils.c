/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hurabe <hurabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 22:01:14 by hurabe            #+#    #+#             */
/*   Updated: 2025/01/19 22:16:03 by hurabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_msg(char *message)
{
	if (message)
	{
		ft_putstr_fd("Error\n", STDERR_FILENO);
		ft_putstr_fd(message, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
}
