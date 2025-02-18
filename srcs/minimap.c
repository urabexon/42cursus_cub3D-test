/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:37:47 by kitaoryoma        #+#    #+#             */
/*   Updated: 2025/02/18 22:31:47 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// ミニマップを描画
void	ft_draw_minimap(t_data *data)
{
	int x, y;//ミニマップ内の座標（プレイヤー(0,0)座標）
	t_vector pos;// 表示する点の座標
	unsigned int color;
	x = -MINIMAP_SIZE / 2;
	while (x < MINIMAP_SIZE / 2)
	{
		y = -MINIMAP_SIZE / 2;
		while (y < MINIMAP_SIZE / 2)
		{
			pos.x = data->player.position.x + (data->player.direction.x * y + data->player.direction.y * x) * data->minimap_scale;
			pos.y = data->player.position.y + (data->player.direction.y * y - data->player.direction.x * x) * data->minimap_scale;
			if ((int)pos.y / PX < 0 || (int)pos.y / PX >= data->rows
				|| (int)pos.x / PX < 0 || (int)pos.x / PX >= data->columns)
				color = 0x101010;//マップ範囲外（黒色）
			else if (data->map[data->rows - 1 - (int)pos.y / PX][(int)pos.x / PX] == '1')
				color = 0x696969;//壁（灰色）
			else
				color = 0xf0f8ff;//通路（薄い水色）
			*(unsigned int *)(data->graphic.minimap_img.addr + (MINIMAP_SIZE / 2 - y - 1) * data->graphic.minimap_img.line_size
				+ (x + MINIMAP_SIZE / 2) * (data->graphic.minimap_img.bits_per_pixel / 8)) = color;
			y++;
		}
		x++;
	}
}
