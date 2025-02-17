/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 17:45:40 by hurabe            #+#    #+#             */
/*   Updated: 2025/02/17 15:18:02 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
int	main(int argc, char **argv)
{
	t_data	data;

	// 入力チェック
	if (validate(argc, argv))
		return (EXIT_FAILURE);
	// 初期化する(ファイルからデータを取得してdataに格納する)
	init_data(&data, argv[1]);
	// マップの内容を確認する
	check_map(&data);
	// mlxの初期化
	ft_mlx_init(&data);
	// 天井と床の色を描画
	ft_put_floor_and_ceiling(&data);
	// imageを表示
	mlx_put_image_to_window(data.graphic.mlx, data.graphic.win, data.graphic.image.img, 0, 0);
	// キー入力設定
	// ウィンドウ、ボタン設定
	// ループ処理する
	sleep(5);
	return (0);
}
