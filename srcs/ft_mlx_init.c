/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hurabe <hurabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:13:37 by kitaoryoma        #+#    #+#             */
/*   Updated: 2025/03/03 21:33:27 by hurabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_mlx_init_sub(t_data *data)
{
	data->graphic.win = mlx_new_window(data->graphic.mlx, WIDTH, HEIGHT,
			"cub3D");
	data->graphic.image.img = mlx_new_image(data->graphic.mlx, WIDTH, HEIGHT);
	data->graphic.image.addr = mlx_get_data_addr(data->graphic.image.img,
			&data->graphic.image.bits_per_pixel, &data->graphic.image.line_size,
			&data->graphic.image.endian);
	data->graphic.minimap_img.img = mlx_new_image(data->graphic.mlx,
			MINIMAP_SIZE, MINIMAP_SIZE);
	data->graphic.minimap_img.addr
		= mlx_get_data_addr(data->graphic.minimap_img.img,
			&data->graphic.minimap_img.bits_per_pixel,
			&data->graphic.minimap_img.line_size,
			&data->graphic.minimap_img.endian);
}

// MLXの初期化、ウィンドウ作成
void	ft_mlx_init(t_data *data)
{
	t_direction	dir;

	data->graphic.mlx = mlx_init();
	if (!data->graphic.mlx)
		exit_error("mlx_init failed", data);
	// テクスチャの読み出し
	dir = NORTH;
	while (dir < NONE)
	{
		data->textures[dir].image.img = mlx_xpm_file_to_image(data->graphic.mlx,
				data->texture_paths[dir], &data->textures[dir].width,
				&data->textures[dir].height);
		if (!data->textures[dir].image.img)
			exit_error("mlx_xpm_file_to_image failed", data);
		data->textures[dir].image.addr
			= mlx_get_data_addr(data->textures[dir].image.img,
				&data->textures[dir].image.bits_per_pixel,
				&data->textures[dir].image.line_size,
				&data->textures[dir].image.endian);
		dir++;
	}
	ft_mlx_init_sub(data);
}
