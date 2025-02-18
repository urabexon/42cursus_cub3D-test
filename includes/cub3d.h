/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 17:59:42 by hurabe            #+#    #+#             */
/*   Updated: 2025/02/18 14:42:37 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include "get_next_line.h"
# include "libft.h"
# include <math.h>

// KEYBOARD CODE(仮)
# define ESC 65307 // ESCキー
# define W 119     // Wキー
# define S 115     // Sキー
# define A 97      // Aキー
# define D 100     // Dキー
# define LA 65361  // 矢印キー左
# define RA 65363  // 矢印キー右
//# define M 109     // Mキー(ミニマップ表示切替用,やらなければ削除する)

// SIZE(仮)
# define PX 64              // 各タイルのピクセル数
# define PACE 10            // プレイヤーの移動ペース
# define TURNANGLE 0.1      // プレイヤーの回転角度
# define PLYLEN 9           // プレイヤーの描画サイズ
# define FOV 1.047198       // 視野角（Field of View）60°
# define HALF_FOV 0.523599  // 視野角の半分 30°
# define PLANE_DIST 652.719 // 平面の投影距離
# define WIDTH 1000         // ウィンドウ幅
# define HEIGHT 1000        // ウィンドウ高さ

// MATH
# define PI 3.14159265      // 円周率（ラジアン計算用）
# define TOLERANCE 0.000001 // 計算誤差の許容値
# define X 0                // X方向のインデックス
# define Y 1                // Y方向のインデックス

// flood_fill用　チェック済みの印(使用しなければ削除)
# define CHECKED 'V'

// デバッグ用printf
#ifdef DEBUG
# define PRINTF(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
# define PRINTF(fmt, ...)
#endif

// direction(方向,壁の向きやプレイヤーの向き)
typedef enum	e_direction
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
	NONE
}			t_direction;

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

// playerとraycasting構造体の変数は、計算しやすいように全て左下(0,0)座標にする

// player(プレイヤーの情報)
typedef struct s_player
{
	t_vector	position;  // 現在位置 (x, y座標)
	t_vct_int	array_pos; // 初期位置 (x, y座標) map配列の探索用にintの値を格納(左上(0,0)座標)
	t_vector	direction; // 向きベクトル (x, y座標)
	double		angle;     // 向きの角度 (ラジアン)
}				t_player;

// raycasting(レイのデータ、壁衝突位置、角度、テクスチャの座標)
typedef struct s_ray
{
	t_vct_int	vct;            // 現在の座標（整数）
	t_vct_int	step;           // レイの進行方向(1 or -1)
	t_vector	next_grid;      // 次のグリッドラインまでの距離
	t_vector	direction;      // レイの進行方向(ベクトル)
	t_vector	delta;          // x,y方向に1マス進めた時のレイの長さの変化
	double		angle;          // レイの角度(ラジアン)
	double		distance;       // 壁に当たるまでの距離
	int			hit_wall;       // 壁の衝突判定フラグ（1: 垂直、0: 水平）1:vertical 2:horizontal
	int			wall_dir;       // 衝突した壁のテクスチャID(e_direction)
	double		wall_hit_point; // テクスチャのどの部分に当たったか(0-1, 左下(0,0)座標)
	int			wall_height;    // レイの結果として計算された壁の高さ
}				t_ray;

// MinilibX_image(MinilibXで扱う画像データを保持する)
typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
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
	char		*texture_paths[5];  // テクスチャファイルパス 5つ目はNULL
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

// init.c
void	init_data(t_data *data, char *filedata);

// setup.c
void	set_data_from_file(t_data *data, char **file);
void	setup(t_data *data);

// init_metadata.c
void	set_metadata(t_data	*data, char ***file);

// init_map.c
int		get_map_columns(char **file);
int		get_map_rows(char **file);
void	set_map(t_data *data, char **file);

// check_map.c
void	check_map(t_data *data);

// check_player.c
void	set_player_info(t_data *data, int y, int x, char **map);
void	check_player(t_data *data, char **map);

// exit.c
void	error_msg(char *message);
void	exit_error(char *message, t_data *data);
void	exit_game(t_data *data);

// utils.c
void	free_all(char **arr);
bool	is_include_char(char *s, int c);
void	replace_str(char *str, char *remove, char replace);
int		strarr_size(char **arr);
bool	is_str_type(char *str, int (*function)(int));

// ft_mlx_init.c
void	ft_mlx_init(t_data *data);

// ft_put_color.c
void	ft_put_floor_and_ceiling(t_data *data);

// raycasting.c
void	ft_raycasting(t_data *data);


#endif
