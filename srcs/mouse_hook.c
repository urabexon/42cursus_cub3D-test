/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 22:48:32 by kitaoryoma        #+#    #+#             */
/*   Updated: 2025/02/18 22:53:18 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mouse_hook(int event, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (event == SCROLL_UP)
		data->player.angle += TURNANGLE;
	else if (event == SCROLL_DOWN)
		data->player.angle -= TURNANGLE;
	// 回転によって向きが変わったのでdirectionを再計算
	data->player.direction.x = cos(data->player.angle);
	data->player.direction.y = sin(data->player.angle);
	PRINTF("player position: %f, %f\n", data->player.position.x, data->player.position.y);
	PRINTF("player direction: %f, %f\n", data->player.direction.x, data->player.direction.y);
	ft_print_screen(data);
	return (0);
}
