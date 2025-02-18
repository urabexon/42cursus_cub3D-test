/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:05:19 by kitaoryoma        #+#    #+#             */
/*   Updated: 2025/02/18 15:15:38 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void ft_init_sub(t_data *data, t_ray *ray)
{
	if (ray->direction.x > 0)
	{
		ray->step.x = 1;
		ray->next_grid.x = (ceil(data->player.position.x / PX) * PX - data->player.position.x) / ray->direction.x;
	}
	else
	{
		ray->step.x = -1;
		ray->next_grid.x = (data->player.position.x - floor(data->player.position.x / PX) * PX) / ray->direction.x;
	}
	if (ray->direction.y > 0)
	{
		ray->step.y = 1;
		ray->next_grid.y = (ceil(data->player.position.y / PX) * PX - data->player.position.y) / ray->direction.y;
	}
	else
	{
		ray->step.y = -1;
		ray->next_grid.y = (data->player.position.y - floor(data->player.position.y / PX) * PX) / ray->direction.y;
	}
}

// レイキャスティングのデータの初期化
static void ft_raycasting_init(t_data *data, t_ray *ray, int width)
{
	ray->vct.x = data->player.position.x / PX;
	ray->vct.y = data->player.position.y / PX;
	double diff = -atan((width - WIDTH / 2) / (WIDTH / 2 * sqrt(3)));
	ray->angle = data->player.angle + diff;
	ray->direction.x = cos(ray->angle);
	ray->direction.y = sin(ray->angle);
	ray->distance = 0;
	ray->delta.x = fabs(PX / ray->direction.x);
	ray->delta.y = fabs(PX / ray->direction.y);
	ft_init_sub(data, ray);
}

// レイキャスティングを行う
static void	ft_raycasting(t_data *data, t_ray *ray)
{
	while (1)
	{
		PRINTF("vct.x: %d, vct.y: %d\n", ray->vct.x, ray->vct.y);
		if (ray->next_grid.x < ray->next_grid.y)
		{
			ray->distance = ray->next_grid.x;
			ray->next_grid.x += ray->delta.x;
			ray->vct.x += ray->step.x;
			ray->hit_wall = 1;
		}
		else
		{
			ray->distance = ray->next_grid.y;
			ray->next_grid.y += ray->delta.y;
			ray->vct.y += ray->step.y;
			ray->hit_wall = 0;
		}
		// 壁があるか確認
		if (data->map[data->rows - ray->vct.y][ray->vct.x] == '1')
			break ;
	}
}

// レイキャスtェイングの結果をまとめ、壁の描画に必要な情報を求める
static void ft_raycasting_result(t_data *data, t_ray *ray)
{
	// 壁のテクスチャ（方向）を求める
	if (ray->hit_wall)
	{
		if (ray->direction.x > 0)
			ray->wall_dir = EAST;
		else
			ray->wall_dir = WEST;
	}
	else
	{
		if (ray->direction.y > 0)
			ray->wall_dir = NORTH;
		else
			ray->wall_dir = SOUTH;
	}
	// 壁のどの位置にあたったかを求める
	if (ray->hit_wall)
		ray->wall_hit_point = fmod((data->player.position.y + ray->distance * ray->direction.y), PX) / PX;
	else
		ray->wall_hit_point = fmod((data->player.position.x + ray->distance * ray->direction.x), PX) / PX;
	// 壁の高さを求める（あとで綺麗な描画になる値を見つける）
	ray->wall_height = HEIGHT / 4 * PX * (data->player.direction.y) / (ray->distance * ray->direction.y);
	PRINTF("hit_wall: %d\n", ray->hit_wall);
	PRINTF("wall_dir: %d\n", ray->wall_dir);
	PRINTF("wall_hit_point: %f\n", ray->wall_hit_point);
	PRINTF("wall_height: %d\n", ray->wall_height);
}

// 壁の一辺を描画する
static void ft_draw_line_of_wall(t_data *data, t_ray *ray, int width)
{
	int i = 0;
	while (i < ray->wall_height)
	{
		int texture_x;
		int texture_y;
		// テクスチャの座標を求める
		if (ray->hit_wall)
		{
			texture_x = (int)(data->textures[ray->wall_dir].width * (1 - ray->wall_hit_point));
		}
		else
		{
			texture_x = (int)(data->textures[ray->wall_dir].width * ray->wall_hit_point);
		}
		texture_y = (int)(data->textures[ray->wall_dir].height * ((double)i / ray->wall_height));
		char *src;
		src = data->textures[ray->wall_dir].image.addr + (texture_y * data->textures[ray->wall_dir].image.line_size) + (texture_x * (data->textures[ray->wall_dir].image.bits_per_pixel / 8));
		long color = *(unsigned int *)src;
		*(unsigned int *)(data->graphic.image.addr + (HEIGHT / 2 - ray->wall_height / 2 + i)
				* data->graphic.image.line_size + width
				* (data->graphic.image.bits_per_pixel / 8)) = color;
		i++;
	}
}

void	ft_draw_wall(t_data *data)
{
	t_ray *ray;
	int width = 0;
	data->rays = (t_ray *)malloc(sizeof(t_ray) * WIDTH);
	while (width < WIDTH)
	{
		ray = &data->rays[width];
		// レイキャスティングのデータの初期化
		ft_raycasting_init(data, ray, width);
		PRINTF("start\n");
		PRINTF("vct.x: %d, vct.y: %d\n", ray->vct.x, ray->vct.y);
		PRINTF("direction.x: %f, direction.y: %f\n", ray->direction.x, ray->direction.y);
		PRINTF("angle: %f\n", ray->angle);
		PRINTF("next_grid.x: %f, next_grid.y: %f\n", ray->next_grid.x, ray->next_grid.y);
		PRINTF("delta.x: %f, delta.y: %f\n", ray->delta.x, ray->delta.y);
		ft_raycasting(data, ray);
		ft_raycasting_result(data, ray);
		// 壁の一辺を描画する
		ft_draw_line_of_wall(data, ray, width);
		width++;
	}
}
