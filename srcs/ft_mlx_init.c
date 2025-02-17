/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:13:37 by kitaoryoma        #+#    #+#             */
/*   Updated: 2025/02/17 11:18:37 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
}