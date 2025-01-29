/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hurabe <hurabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 19:09:23 by hurabe            #+#    #+#             */
/*   Updated: 2025/01/29 23:23:35 by hurabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// プレイヤーの向きをラジアン角で設定する関数
static void	set_player_angle(t_player *player, char dir)
{
	// ラジアンでは、１周は2π（2×3.14）
	// ラジアンの周期性により、角度は2πの周期を持つので3π/2と-π/2は同じ方向を向いていることになる
	// -90度に360度を加えれば270度になる。計算がわかりやすいので北は-PI/2で表現
	// 北（-90度）3π/2ラジアン
	if (dir == 'N')
		player->angle = -PI / 2;
	// 南（90度）π/2ラジアン
	else if (dir == 'S')
		player->angle = PI / 2;
	// 東（0度）0ラジアン
	else if (dir == 'E')
		player->angle = 0;
	// 西（180度）πラジアン
	else if (dir == 'W')
		player->angle = PI;
}

// プレイヤーの座標と進行方向を設定する関数
static void	set_player_position(t_player *player, int y, int x, char dir)
{
	// インデックスからマップのどの座標にいるか取得（PX：タイルのピクセル数）
	// タイルの幅 × 枚数 ＋ タイルの半分（中心）
	player->position.y = PX * y + (PX / 2);
	player->position.x = PX * x + (PX / 2);
	// どの方角を向いているかを三角比で設定する
	// 半径1の円の中心にいる場合、北(0,-1)、南(0,1)、西(1,0)、東(-1,0)
	if (dir == 'N')
	{
		player->direction.y = -1;
		player->direction.x = 0;
	}
	else if (dir == 'S')
	{
		player->direction.y = 1;
		player->direction.x = 0;
	}
	else if (dir == 'E')
	{
		player->direction.y = 0;
		player->direction.x = 1;
	}
	else if (dir == 'W')
	{
		player->direction.y = 0;
		player->direction.x = -1;
	}

}

// プレイヤーのデータを設定する関数
void	set_player_info(t_data *data, int y, int x, char **map)
{
	// map配列の座標を取得する(探索用)
	data->player.array_pos.y = y;
	data->player.array_pos.x = x;
	// 画面上の座標と方角を取得する(描画用)
	set_player_position(&data->player, y, x, map[y][x]);
	// 角度情報を持っておく
	set_player_angle(&data->player, map[y][x]);
}

// マップ上にプレイヤーが1人だけ存在するかをチェックする関数
void	check_player(t_data *data, char **map)
{
	int		y;
	int		x;
	bool	player_found;

	y = 0;
	player_found = false;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			// プレイヤーを見つけたらプレイヤー情報を取得
			if (ft_strchr("NSEW", map[y][x]))
			{
				// プレイヤーが複数人いたらエラー
				if (player_found)
					exit_error("Some players on map!", data);
				player_found = true;
				set_player_info(data, y, x, map);
			}
			x++;
		}
		y++;
	}
	// プレイヤーが一人もいなかったらエラー
	if (!player_found)
		exit_error("No player on map!", data);
}
