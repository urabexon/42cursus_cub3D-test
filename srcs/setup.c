/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hurabe <hurabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 22:29:40 by hurabe            #+#    #+#             */
/*   Updated: 2025/01/24 20:51:08 by hurabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	setup_map_info(t_data *data)
{
	data->file = NULL;
	data->floor_rgb[0] = -1;
	data->floor_rgb[1] = -1;
	data->floor_rgb[2] = -1;
	data->ceiling_rgb[0] = -1;
	data->ceiling_rgb[1] = -1;
	data->ceiling_rgb[2] = -1;
	data->map = NULL;
	data->rows = 0;
	data->columns = 0;
	data->rays = NULL;
	data->show_minimap = false;
	data->minimap_scale = 0;
}

static void	setup_texture(t_data *data)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		data->texture_paths[i] = NULL;
		data->textures[i].width = 0;
		data->textures[i].height = 0;
		data->textures[i].image.img = NULL;
		data->textures[i].image.addr = NULL;
		data->textures[i].image.bits_per_pixel = 0;
		data->textures[i].image.endian = 0;
		data->textures[i].image.line_size = 0;
		i++;
	}
}

static void	setup_player(t_player *player)
{
	player->position.x = 0;
	player->position.y = 0;
	player->array_pos.x = 0;
	player->array_pos.y = 0;
	player->direction.x = 0;
	player->direction.y = 0;
	player->angle = 0;
}

static void	setup_graphic(t_window *graphic)
{
	graphic->mlx = NULL;
	graphic->win = NULL;
	graphic->image.img = NULL;
	graphic->image.addr = NULL;
	graphic->image.bits_per_pixel = 0;
	graphic->image.endian = 0;
	graphic->image.line_size = 0;
}

void	setup(t_data *data)
{
	setup_map_info(data);
	setup_texture(data);
	setup_player(&data->player);
	setup_graphic(&data->graphic);
}
