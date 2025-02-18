/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:25:12 by kitaoryoma        #+#    #+#             */
/*   Updated: 2025/02/18 19:22:49 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int is_in_wall(t_data *data, t_vector position)
{
	int x;
	int y;

	x = position.x / PX;
	y = position.y / PX;
	if (data->map[data->rows - 1 - y][x] == '1')
		return (1);
	return (0);
}

int	key_hook(int keycode, t_data *data)
{
	// 移動前の座標を保持
	t_vector old_position = data->player.position;
	if (keycode == ESC)
		exit_game(data);
	if (keycode == W)
	{
		data->player.position.x += PACE * data->player.direction.x;
		data->player.position.y += PACE * data->player.direction.y;
	}
	else if (keycode == S)
	{
		data->player.position.x -= PACE * data->player.direction.x;	
		data->player.position.y -= PACE * data->player.direction.y;
	}
	else if (keycode == A)
	{
		data->player.position.x -= PACE * data->player.direction.y;
		data->player.position.y += PACE * data->player.direction.x;
	}
	else if (keycode == D)
	{
		data->player.position.x += PACE * data->player.direction.y;
		data->player.position.y -= PACE * data->player.direction.x;
	}
	else if (keycode == LA)
		data->player.angle += TURNANGLE;
	else if (keycode == RA)
		data->player.angle -= TURNANGLE;
	if (is_in_wall(data, data->player.position))
		data->player.position = old_position;
	// 回転によって向きが変わったのでdirectionを再計算
	data->player.direction.x = cos(data->player.angle);
	data->player.direction.y = sin(data->player.angle);
	PRINTF("player position: %f, %f\n", data->player.position.x, data->player.position.y);
	PRINTF("player direction: %f, %f\n", data->player.direction.x, data->player.direction.y);
	ft_put_floor_and_ceiling(data);
	ft_draw_wall(data);
	mlx_put_image_to_window(data->graphic.mlx, data->graphic.win, data->graphic.image.img, 0, 0);
	return (0);
}
