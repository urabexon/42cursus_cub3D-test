/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hurabe <hurabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 17:59:42 by hurabe            #+#    #+#             */
/*   Updated: 2025/01/19 22:17:52 by hurabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include "get_next_line.h"
# include "libft.h"
# include <math.h>

// direction(方向,壁の向きやプレイヤーの向き)
enum	e_direction
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
	NONE
};

// player_vector(プレイヤーやレイの位置、方向を保持する用のベクトル)
typedef struct s_vector
{
	double	x;
	double	y;
}				t_vector;

// integer_vector(整数座標、マップ配列の探索用のベクトル)
typedef struct s_vct_int
{
	int	x;
	int	y;	
}				t_vct_int;

// player(プレイヤーの情報)
typedef struct s_player
{
	t_vector	position;  // 現在位置 (x, y座標)
	t_vct_int	array_pos; // 現在位置 (x, y座標) map配列の探索用にintの値を格納
	t_vector	direction; // 向きベクトル (x, y座標)
	double		angle;     // 向きの角度 (ラジアン)
}				t_player;

// raycasting(レイのデータ、壁衝突位置、角度、テクスチャの座標)
typedef struct s_ray
{
	t_vector	vst;            // 現在のY座標
	t_vector	next_grid;      // 次のグリッドラインまでの距離
	t_vector	direction;      // レイの進行方向(ベクトル)
	double		angle;          // レイの角度(ラジアン)
	double		distance;       // 壁に当たるまでの距離
	int			hit_wall;       // 壁の衝突判定フラグ（1: 垂直、0: 水平）1:vertical 2:horizontal
	int			wall_dir;       // 衝突した壁のテクスチャID(e_direction)
	double		wall_hit_point; // 1:vertical 2:horizontal 垂直な壁に衝突したかを示すフラグ（1: 垂直、0: 水平）
	int			wall_height;    // レイの結果として計算された壁の高さ
}				t_ray;

// MinilibX_image(MinilibXで扱う画像データを保持する)
typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixed;
	int		line_size;
	int		endian;
}			t_image;

// texture_data(画像データを格納する)
typedef struct s_texture
{
	t_image		image;
	int			width;
	int			height;	
}				t_texture;

// MinilibX_window(MinilibXのウィンドウと画像データ)
typedef struct s_window
{
	t_image		image;
	void		*mlx;
	void		*win;
}				t_window;

// all_data(全体のデータ)
typedef struct s_data
{
	char		**file;             //.cubファイルの中身
	char		**texture_paths[5]; // テクスチャファイルパス 5つ目はNULL
	int			floor_rgb[3];       // 床の色（RGB）
	int			ceiling_rgb[3];     // 天井の色（RGB）
	char		**map;              // マップデータ（2D配列）
	int			rows;               // マップの行数
	int			columns;            // マップの列数
	t_player	player;				// プレイヤー情報
	t_window	graphic;			// mlx関連（ウィンドウ、イメージ）
	t_texture	textures[5];		// mlx関連（テクスチャ）
	t_ray		*rays;              // mlx関連（レイキャスティング）
	bool		show_minimap;       // ミニマップ表示フラグ
	int			minimap_scale;      // ミニマップのスケール
}				t_data;

// validate.c
int		validate(int argc, char **argv);

// utils.c
void	error_msg(char *message);

#endif