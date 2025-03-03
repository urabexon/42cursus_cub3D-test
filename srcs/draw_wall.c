/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hurabe <hurabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 23:10:28 by kitaoryoma        #+#    #+#             */
/*   Updated: 2025/03/03 21:33:00 by hurabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_draw_line_of_wall_sub(t_data *data, t_ray *ray, int width, int i)
{
	char		*src;
	long		color;
	int			height;
	t_vct_int	texture;	// テクスチャ内の描画する座標を求める

	height = HEIGHT / 2 - ray->wall_height / 2 + i;
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
	*(unsigned int *)(data->graphic.image.addr + height
			* data->graphic.image.line_size + width
			* (data->graphic.image.bits_per_pixel / 8)) = color;
}

// 壁の一辺を描画する
static void	ft_draw_line_of_wall(t_data *data, t_ray *ray, int width)
{
	int	i;
	int	height;

	i = 0;
	while (i < ray->wall_height)
	{
		height = HEIGHT / 2 - ray->wall_height / 2 + i;
		if (height < 0 || height >= HEIGHT)
		{
			i++;
			continue ;
		}
		ft_draw_line_of_wall_sub(data, ray, width, i);
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
