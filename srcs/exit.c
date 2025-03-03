/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hurabe <hurabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:49:10 by hurabe            #+#    #+#             */
/*   Updated: 2025/03/03 20:52:28 by hurabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_textures(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (data->texture_paths[i])
			free(data->texture_paths[i]);
		if (data->textures[i].image.img)
			mlx_destroy_image(data->graphic.mlx, data->textures[i].image.img);
		i++;
	}
}

static void	free_data(t_data *data)
{
	free_textures(data);
	if (data->file)
		free_all(data->file);
	if (data->map)
		free_all(data->map);
	if (data->graphic.image.img)
		mlx_destroy_image(data->graphic.mlx, data->graphic.image.img);
	if (data->graphic.minimap_img.img)
		mlx_destroy_image(data->graphic.mlx, data->graphic.minimap_img.img);
	if (data->graphic.win)
		mlx_destroy_window(data->graphic.mlx, data->graphic.win);
	if (data->graphic.mlx)
	{
		mlx_destroy_display(data->graphic.mlx);
		free(data->graphic.mlx);
	}
}

void	error_msg(char *message)
{
	if (message)
	{
		ft_putstr_fd("Error\n", STDERR_FILENO);
		ft_putstr_fd(message, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
}

void	exit_error(char *message, t_data *data)
{
	free_data(data);
	if (message)
		error_msg(message);
	exit(EXIT_FAILURE);
}

int	exit_game(t_data *data)
{
	free_data(data);
	ft_putstr_fd(" THANKS FOR PLAYING! ", STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	exit(EXIT_SUCCESS);
	return (0);
}
