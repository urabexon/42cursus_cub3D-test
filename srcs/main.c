/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hurabe <hurabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 17:45:40 by hurabe            #+#    #+#             */
/*   Updated: 2025/03/03 20:43:01 by hurabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_print_screen(t_data *data)
{
	ft_put_floor_and_ceiling(data);
	ft_draw_wall(data);
	mlx_put_image_to_window(data->graphic.mlx, data->graphic.win, \
		data->graphic.image.img, 0, 0);
	if (data->show_minimap)
	{	
		ft_draw_minimap(data);
		mlx_put_image_to_window(data->graphic.mlx, data->graphic.win, \
			data->graphic.minimap_img.img, 0, 0);
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (validate(argc, argv))
		return (EXIT_FAILURE);
	init_data(&data, argv[1]);
	check_map(&data);
	ft_mlx_init(&data);
	ft_print_screen(&data);
	mlx_hook(data.graphic.win, ON_DESTROY, 0, exit_game, &data);
	mlx_mouse_hook(data.graphic.win, mouse_hook, &data);
	mlx_key_hook(data.graphic.win, key_hook, &data);
	mlx_loop(data.graphic.mlx);
	return (0);
}
