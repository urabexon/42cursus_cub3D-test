/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:05:19 by kitaoryoma        #+#    #+#             */
/*   Updated: 2025/02/18 19:25:23 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_init_sub(t_data *data, t_ray *ray)
{
	if (ray->direction.x > 0)
	{
		ray->step.x = 1;
		ray->next_grid.x = fabs(((ray->vct.x + 1) * PX
				- data->player.position.x) / ray->direction.x);
	}
	else
	{
		ray->step.x = -1;
		ray->next_grid.x = fabs((data->player.position.x
				- ray->vct.x * PX) / ray->direction.x);
	}
	if (ray->direction.y > 0)
	{
		ray->step.y = 1;
		ray->next_grid.y = fabs((((ray->vct.y + 1) * PX
				- data->player.position.y)) / ray->direction.y);
	}
	else
	{
		ray->step.y = -1;
		ray->next_grid.y = fabs((data->player.position.y
				- ray->vct.y * PX) / ray->direction.y);
	}
}

// レイキャスティングのデータの初期化
static void	ft_raycasting_init(t_data *data, t_ray *ray, int width)
{
	double	diff;

	ray->vct.x = data->player.position.x / PX;
	ray->vct.y = data->player.position.y / PX;
	diff = -atan((width - WIDTH / 2) / (WIDTH / 2 * sqrt(3)));
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
		if (data->map[data->rows - ray->vct.y - 1][ray->vct.x] == '1')
			break ;
	}
}

// レイキャスtェイングの結果をまとめ、壁の描画に必要な情報を求める
static void	ft_raycasting_result(t_data *data, t_ray *ray)
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
		ray->wall_hit_point = fmod((data->player.position.y + ray->distance
					* ray->direction.y), PX) / PX;
	else
		ray->wall_hit_point = fmod((data->player.position.x + ray->distance
					* ray->direction.x), PX) / PX;
	// 壁の高さを求める（あとで綺麗な描画になる値を見つける）
	ray->wall_height = HEIGHT / 4 * PX / ray->distance / cos(ray->angle - data->player.angle);
}

// 壁の一辺を描画する
static void	ft_draw_line_of_wall(t_data *data, t_ray *ray, int width)
{
	int			i;
	t_vct_int	texture; // テクスチャ内の描画する座標を求める
	char		*src;
	long		color;
	int			height;

	i = 0;
	while (i < ray->wall_height)
	{
		height = HEIGHT / 2 - ray->wall_height / 2 + i;
		if (height < 0 || height >= HEIGHT)
		{
			i++;
			continue ;
		}
		if (ray->hit_wall)
		{
			texture.x = (int)(data->textures[ray->wall_dir].width * (1
						- ray->wall_hit_point));
		}
		else
		{
			texture.x = (int)(data->textures[ray->wall_dir].width
					* ray->wall_hit_point);
		}
		texture.y = (int)(data->textures[ray->wall_dir].height * ((double)i
					/ ray->wall_height));
		src = data->textures[ray->wall_dir].image.addr + (texture.y
				* data->textures[ray->wall_dir].image.line_size) + (texture.x
				* (data->textures[ray->wall_dir].image.bits_per_pixel / 8));
		color = *(unsigned int *)src;
		*(unsigned int *)(data->graphic.image.addr + height * data->graphic.image.line_size
				+ width * (data->graphic.image.bits_per_pixel / 8)) = color;
		i++;
	}
}

void	ft_draw_wall(t_data *data)
{
	t_ray	*ray;
	int		width;

	width = 0;
	data->rays = (t_ray *)malloc(sizeof(t_ray) * WIDTH);
	while (width < WIDTH)
	{
		ray = &data->rays[width];
		// レイキャスティングのデータの初期化
		ft_raycasting_init(data, ray, width);
		ft_raycasting(data, ray);
		ft_raycasting_result(data, ray);
		// 壁の一辺を描画する
		ft_draw_line_of_wall(data, ray, width);
		width++;
	}
	free(data->rays);
}
