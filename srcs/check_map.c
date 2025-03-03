/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hurabe <hurabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 19:03:49 by hurabe            #+#    #+#             */
/*   Updated: 2025/03/03 21:32:31 by hurabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// マップが壁に囲まれているかを確認する関数(資料参考)
static int	flood_fill(t_data *data, int y, int x, t_vct_int *dir)
{
	int	i;

	// インデックスがマップの範囲外ならエラー
	if (x < 0 || x >= data->columns || y < 0 || y >= data->rows)
		return (EXIT_FAILURE);
	// 対象がスペースならエラー
	if (data->map[y][x] == ' ')
		return (EXIT_FAILURE);
	//  対象が壁かチェック済みなら探索終了
	if (data->map[y][x] == '1' || data->map[y][x] == CHECKED)
		return (EXIT_SUCCESS);
	// 問題なければ今の位置をチェック済みにする
	data->map[y][x] = CHECKED;
	// 8方向を再帰的にチェック
	i = 0;
	while (i < 8)
	{
		if (flood_fill(data, y + dir[i].y, x + dir[i].x, dir))
			return (EXIT_FAILURE);
		i++;
	}
	// 問題なければ正常終了する
	return (EXIT_SUCCESS);
}

// 4方向+斜め4方向の8方向を探索するためのベクトルを設定する関数
static void	set_directions(t_vct_int *directions)
{
	directions[0] = (t_vct_int){-1, -1}; // 左上
	directions[1] = (t_vct_int){-1, 0};  // 上
	directions[2] = (t_vct_int){-1, 1};  // 右上
	directions[3] = (t_vct_int){0, -1};  // 左
	directions[4] = (t_vct_int){0, 1};   // 右
	directions[5] = (t_vct_int){1, -1};  // 左下
	directions[6] = (t_vct_int){1, 0};   // 下
	directions[7] = (t_vct_int){1, 1};   // 右下
}

// マップが壁で囲まれているかを確認する関数
// プレイヤーの位置からflood_fillを開始し、マップの境界が閉じているか判定する
static void	check_map_structure(t_data *data, char **map)
{
	int			x;
	int			y;
	char		org;
	t_vct_int	dir[8];

	// 扱いやすいように代入(プレイヤーの位置を取得)
	x = data->player.array_pos.x;
	y = data->player.array_pos.y;
	// "NSEW"を保存しておく
	org = map[y][x];
	// 探索対象にするため'0'にしておく
	map[y][x] = '0';
	// 探索方向を初期化する
	set_directions(dir);
	// 探索開始
	if (flood_fill(data, y, x, dir))
		exit_error("Invalid map!", data);
	// マップを復元する
	map[y][x] = org;
	// チェック済みのマス('V')を元の'0'に戻す
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == CHECKED)
				map[y][x] = '0';
			x++;
		}
		y++;
	}
}

// マップに不正な文字が含まれていないかをチェックする関数
// 使用可能な文字は"0, 1, N, S, E, W, ' '"のみ
static void	check_components(t_data *data, char **map)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			// 無効な文字が含まれていないか確認する
			if (!ft_strchr(" 01NSEW", map[y][x]))
				exit_error("Invalid characters on map!", data);
			x++;
		}
		y++;
	}
}

// マップの検証を行う関数本体
void	check_map(t_data *data)
{
	// 不正な文字がないか確認する
	check_components(data, data->map);
	// プレイヤーが1人だけいるか確認する
	check_player(data, data->map);
	// マップが壁で囲まれているか確認する
	check_map_structure(data, data->map);
}
