/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hurabe <hurabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:37:47 by kitaoryoma        #+#    #+#             */
/*   Updated: 2025/03/03 17:23:49 by hurabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_draw_minimap_sub(t_data *data, int x, int y)
{
	unsigned int	color;
	t_vector		pos;

	pos.x = data->player.position.x + (data->player.direction.x * y
			+ data->player.direction.y * x) * data->minimap_scale;
	pos.y = data->player.position.y + (data->player.direction.y * y
			- data->player.direction.x * x) * data->minimap_scale;
	if ((int)pos.y / PX < 0 || (int)pos.y / PX >= data->rows || (int)pos.x
		/ PX < 0 || (int)pos.x / PX >= data->columns)
		color = 0x101010;
	else if (data->map[data->rows - 1 - (int)pos.y / PX][(int)pos.x
		/ PX] == '1')
		color = 0x696969;
	else
		color = 0xf0f8ff;
	*(unsigned int *)(data->graphic.minimap_img.addr + (MINIMAP_SIZE / 2 - y
				- 1) * data->graphic.minimap_img.line_size + (x + MINIMAP_SIZE
				/ 2) * (data->graphic.minimap_img.bits_per_pixel / 8)) = color;
}

static void	ft_draw_player(t_data *data)
{
	int	x;
	int	y;

	x = MINIMAP_SIZE / 2 - PLYLEN / 2;
	while (x < MINIMAP_SIZE / 2 + PLYLEN / 2)
	{
		y = MINIMAP_SIZE / 2 - PLYLEN / 2;
		while (y < MINIMAP_SIZE / 2 + PLYLEN / 2)
		{
			*(unsigned int *)(data->graphic.minimap_img.addr + y
					* data->graphic.minimap_img.line_size + x
					* (data->graphic.minimap_img.bits_per_pixel
						/ 8)) = 0xff0000;
			y++;
		}
		x++;
	}
}

void	ft_draw_minimap(t_data *data)
{
	int	x;
	int	y;

	x = -MINIMAP_SIZE / 2;
	while (x < MINIMAP_SIZE / 2)
	{
		y = -MINIMAP_SIZE / 2;
		while (y < MINIMAP_SIZE / 2)
		{
			ft_draw_minimap_sub(data, x, y);
			y++;
		}
		x++;
	}
	ft_draw_player(data);
}
