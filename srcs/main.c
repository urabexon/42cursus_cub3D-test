/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hurabe <hurabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 17:45:40 by hurabe            #+#    #+#             */
/*   Updated: 2025/01/24 19:26:04 by hurabe           ###   ########.fr       */
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
	// MLXの初期化、ウィンドウ作成
	// キー入力設定
	// ウィンドウ、ボタン設定
	// ループ処理する
	mlx_loop(data.graphic.mlx);
	return (0);
}
