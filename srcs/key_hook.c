/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hurabe <hurabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:25:12 by kitaoryoma        #+#    #+#             */
/*   Updated: 2025/03/03 20:55:51 by hurabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_in_wall(t_data *data, t_vector position)
{
	int	x;
	int	y;

	x = (int)position.x / PX;
	y = (int)position.y / PX;
	if (x < 0 || y < 0 || x >= data->columns || y >= data->rows)
		return (1);
	if (data->map[data->rows - 1 - y][x] == '1' || data->map[data->rows - 1
		- y][x] == ' ')
		return (1);
	return (0);
}

static int	is_near_wall(t_data *data, t_vector position)
{
	t_vector	pos;

	pos = position;
	pos.x += PACE;
	if (is_in_wall(data, pos))
		return (1);
	pos.x -= 2 * PACE;
	if (is_in_wall(data, pos))
		return (1);
	pos.x += PACE;
	pos.y += PACE;
	if (is_in_wall(data, pos))
		return (1);
	pos.y -= 2 * PACE;
	if (is_in_wall(data, pos))
		return (1);
	return (0);
}

static void	ft_key_hook_sub(int keycode, t_data *data)
{
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
}

int	key_hook(int keycode, t_data *data)
{
	t_vector	old_position;

	old_position = data->player.position;
	if (keycode == ESC)
		exit_game(data);
	ft_key_hook_sub(keycode, data);
	if (keycode == LA)
		data->player.angle += TURNANGLE;
	else if (keycode == RA)
		data->player.angle -= TURNANGLE;
	else if (keycode == M)
		data->show_minimap = !data->show_minimap;
	if (is_near_wall(data, data->player.position))
		data->player.position = old_position;
	data->player.direction.x = cos(data->player.angle);
	data->player.direction.y = sin(data->player.angle);
	ft_print_screen(data);
	return (0);
}
