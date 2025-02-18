/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:25:12 by kitaoryoma        #+#    #+#             */
/*   Updated: 2025/02/18 18:35:04 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_hook(int keycode, t_data *data)
{
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
