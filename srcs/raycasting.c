/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:05:19 by kitaoryoma        #+#    #+#             */
/*   Updated: 2025/02/18 12:29:10 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_raycasting(t_data *data)
{
	// まずは視点の真ん中のレイだけ計算する
	int width = WIDTH / 2;
	
	data->rays = (t_ray *)malloc(sizeof(t_ray) * WIDTH);
	// レイキャスティングのデータの初期化
	data->rays[width].vct.x = data->player.position.x / PX;
	data->rays[width].vct.y = data->player.position.y / PX;
	double diff = -atan((width - WIDTH / 2) / (WIDTH / 2 * sqrt(3)));
	data->rays[width].angle = data->player.angle + diff;
	data->rays[width].direction.x = cos(data->rays[width].angle);
	data->rays[width].direction.y = sin(data->rays[width].angle);
	data->rays[width].distance = 0;
	// 次にx,y方向に1マス進めた時のレイの長さの変化
	t_vector delta = {fabs(PX / data->rays[width].direction.x), fabs(PX / data->rays[width].direction.y)};
	// レイがx,y方向に進む向き(-1or1)
	t_vct_int step;
	if (data->rays[width].direction.x > 0)
	{
		step.x = 1;
		data->rays[width].next_grid.x = (ceil(data->player.position.x / PX) * PX - data->player.position.x) / data->rays[width].direction.x;
	}
	else
	{
		step.x = -1;
		data->rays[width].next_grid.x = (data->player.position.x - floor(data->player.position.x / PX) * PX) / data->rays[width].direction.x;
	}
	if (data->rays[width].direction.y > 0)
	{
		step.y = 1;
		data->rays[width].next_grid.y = (ceil(data->player.position.y / PX) * PX - data->player.position.y) / data->rays[width].direction.y;
	}
	else
	{
		step.y = -1;
		data->rays[width].next_grid.y = (data->player.position.y - floor(data->player.position.y / PX) * PX) / data->rays[width].direction.y;
	}
	PRINTF("start\n");
	PRINTF("vct.x: %d, vct.y: %d\n", data->rays[width].vct.x, data->rays[width].vct.y);
	PRINTF("direction.x: %f, direction.y: %f\n", data->rays[width].direction.x, data->rays[width].direction.y);
	PRINTF("angle: %f\n", data->rays[width].angle);
	PRINTF("next_grid.x: %f, next_grid.y: %f\n", data->rays[width].next_grid.x, data->rays[width].next_grid.y);
	PRINTF("delta.x: %f, delta.y: %f\n", delta.x, delta.y);
	// レイキャスティングの計算
	while (1)
	{
		PRINTF("vct.x: %d, vct.y: %d\n", data->rays[width].vct.x, data->rays[width].vct.y);
		if (data->rays[width].next_grid.x < data->rays[width].next_grid.y)
		{
			data->rays[width].distance = data->rays[width].next_grid.x;
			data->rays[width].next_grid.x += delta.x;
			data->rays[width].vct.x += step.x;
			data->rays[width].hit_wall = 1;
		}
		else
		{
			data->rays[width].distance = data->rays[width].next_grid.y;
			data->rays[width].next_grid.y += delta.y;
			data->rays[width].vct.y += step.y;
			data->rays[width].hit_wall = 0;
		}
		// 壁があるか確認
		if (data->map[data->rows - data->rays[width].vct.y][data->rays[width].vct.x] == '1')
			break ;
	}
	// 壁のテクスチャ（方向）を求める
	if (data->rays[width].hit_wall)
	{
		if (data->rays[width].direction.x > 0)
			data->rays[width].wall_dir = EAST;
		else
			data->rays[width].wall_dir = WEST;
	}
	else
	{
		if (data->rays[width].direction.y > 0)
			data->rays[width].wall_dir = NORTH;
		else
			data->rays[width].wall_dir = SOUTH;
	}
	// 壁のどの位置にあたったかを求める
	if (data->rays[width].hit_wall)
		data->rays[width].wall_hit_point = fmod((data->player.position.y + data->rays[width].distance * data->rays[width].direction.y), PX) / PX;
	else
		data->rays[width].wall_hit_point = fmod((data->player.position.x + data->rays[width].distance * data->rays[width].direction.x), PX) / PX;
	// 壁の高さを求める（あとで綺麗な描画になる値を見つける）
	data->rays[width].wall_height = HEIGHT / 5 * PX * (data->player.direction.y) / (data->rays[width].distance * data->rays[width].direction.y);
	PRINTF("hit_wall: %d\n", data->rays[width].hit_wall);
	PRINTF("wall_dir: %d\n", data->rays[width].wall_dir);
	PRINTF("wall_hit_point: %f\n", data->rays[width].wall_hit_point);
	PRINTF("wall_height: %d\n", data->rays[width].wall_height);
}