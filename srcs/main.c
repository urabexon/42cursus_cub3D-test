/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 17:45:40 by hurabe            #+#    #+#             */
/*   Updated: 2025/02/18 22:43:20 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// スクリーンに描画する関数
void	ft_print_screen(t_data *data)
{
	// 天井と床の色を描画
	ft_put_floor_and_ceiling(data);
	// 壁を描画
	ft_draw_wall(data);
	// imageを表示
	mlx_put_image_to_window(data->graphic.mlx, data->graphic.win, data->graphic.image.img, 0, 0);
	// ミニマップを表示
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
	// 入力チェック
	if (validate(argc, argv))
		return (EXIT_FAILURE);
	// 初期化する(ファイルからデータを取得してdataに格納する)
	init_data(&data, argv[1]);
	// マップの内容を確認する
	check_map(&data);
	// mlxの初期化
	ft_mlx_init(&data);
	// プレイヤー情報出力
	PRINTF("player position: %f, %f\n", data.player.position.x, data.player.position.y);
	PRINTF("player array_pos: %d, %d\n", data.player.array_pos.x, data.player.array_pos.y);
	PRINTF("player direction: %f, %f\n", data.player.direction.x, data.player.direction.y);
	PRINTF("player angle: %f\n", data.player.angle);
	// スクリーンに描画
	ft_print_screen(&data);
	// ウィンドウを閉じた時の処理
	mlx_hook(data.graphic.win, ON_DESTROY, 0, exit_game, &data);
	// キー入力設定
	mlx_key_hook(data.graphic.win, key_hook, &data);
	// ウィンドウ、ボタン設定
	// ループ処理する
	mlx_loop(data.graphic.mlx);
	return (0);
}
