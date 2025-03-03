/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hurabe <hurabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:13:30 by kitaoryoma        #+#    #+#             */
/*   Updated: 2025/03/03 21:33:35 by hurabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// 床と天井の色を描画
void	ft_put_floor_and_ceiling(t_data *data)
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
