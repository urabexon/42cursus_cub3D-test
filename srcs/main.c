/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hurabe <hurabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 17:45:40 by hurabe            #+#    #+#             */
/*   Updated: 2025/03/03 17:52:19 by hurabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_print_screen(t_data *data)
{
	ft_put_floor_and_ceiling(data);
	ft_draw_wall(data);
	mlx_put_image_to_window(data->graphic.mlx, data->graphic.win, data->graphic.image.img, 0, 0);
	if (data->show_minimap)
	{	
		ft_draw_minimap(data);
		mlx_put_image_to_window(data->graphic.mlx, data->graphic.win, data->graphic.minimap_img.img, 0, 0);
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	PRINTF("DEBUG MODE\n");
	if (validate(argc, argv))
		return (EXIT_FAILURE);
	init_data(&data, argv[1]);
	check_map(&data);
	ft_mlx_init(&data);
	// プレイヤー情報出力
	PRINTF("player position: %f, %f\n", data.player.position.x, data.player.position.y);
	PRINTF("player array_pos: %d, %d\n", data.player.array_pos.x, data.player.array_pos.y);
	PRINTF("player direction: %f, %f\n", data.player.direction.x, data.player.direction.y);
	PRINTF("player angle: %f\n", data.player.angle);
	ft_print_screen(&data);
	mlx_hook(data.graphic.win, ON_DESTROY, 0, exit_game, &data);
	mlx_mouse_hook(data.graphic.win, mouse_hook, &data);
	mlx_key_hook(data.graphic.win, key_hook, &data);
	mlx_loop(data.graphic.mlx);
	return (0);
}
