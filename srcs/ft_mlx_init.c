/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:13:37 by kitaoryoma        #+#    #+#             */
/*   Updated: 2025/02/17 14:53:38 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// 床と天井の色を描画
static void	ft_put_floor_and_ceiling(t_data *data)
{
	int		x;
	int		y;
	long	floor_color;
	long	ceiling_color;

	// 色を設定
	floor_color = data->floor_rgb[0] << 16 | data->floor_rgb[1] << 8 | data->floor_rgb[2];
	ceiling_color = data->ceiling_rgb[0] << 16 | data->ceiling_rgb[1] << 8 | data->ceiling_rgb[2];
	y = 0;
	while (y < HEIGHT / 2)
	{
		x = 0;
		while (x < WIDTH)
		{
			*(unsigned int *)(data->graphic.image.addr + y
					* data->graphic.image.line_size + x
					* (data->graphic.image.bits_per_pixel / 8)) = ceiling_color;
			*(unsigned int *)(data->graphic.image.addr + (HEIGHT - y - 1)
					* data->graphic.image.line_size + x
					* (data->graphic.image.bits_per_pixel / 8)) = floor_color;
			x++;
		}
		y++;
	}
}

// MLXの初期化、ウィンドウ作成
void	ft_mlx_init(t_data *data)
{
	data->graphic.mlx = mlx_init();
	data->graphic.win = mlx_new_window(data->graphic.mlx, WIDTH, HEIGHT,
			"cub3D");
	data->graphic.image.img = mlx_new_image(data->graphic.mlx, WIDTH, HEIGHT);
	data->graphic.image.addr = mlx_get_data_addr(data->graphic.image.img,
			&data->graphic.image.bits_per_pixel, &data->graphic.image.line_size,
			&data->graphic.image.endian);
	// テクスチャの読み出し
	t_direction dir = NORTH;
	while (dir < NONE)
	{
		data->textures[dir].image.img = mlx_xpm_file_to_image(data->graphic.mlx,
				data->texture_paths[dir], &data->textures[dir].width,
				&data->textures[dir].height);
		if (!data->textures[dir].image.img)
			exit_error("mlx_xpm_file_to_image failed", data);
		data->textures[dir].image.addr = mlx_get_data_addr(data->textures[dir].image.img,
				&data->textures[dir].image.bits_per_pixel,
				&data->textures[dir].image.line_size,
				&data->textures[dir].image.endian);
		dir++;
	}
	ft_put_floor_and_ceiling(data);
}
