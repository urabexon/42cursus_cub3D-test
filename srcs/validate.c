/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hurabe <hurabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 21:45:16 by hurabe            #+#    #+#             */
/*   Updated: 2025/01/19 22:10:07 by hurabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	validate(int argc, char **argv)
{
	char	*extension;

	if (argc != 2)
	{
		error_msg("Invalid argument!");
		return (EXIT_FAILURE);
	}
	extension = ft_strchr(argv[1], '.');
	if (!extension || ft_strcmp(extension, ".cub"))
	{
		error_msg("Invalid map file!");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
