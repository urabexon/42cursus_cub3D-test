/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hurabe <hurabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 17:59:42 by hurabe            #+#    #+#             */
/*   Updated: 2025/03/03 17:04:15 by hurabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include "get_next_line.h"
# include "libft.h"
# include <math.h>

// KEYBOARD CODE
# define ESC 65307 // ESC
# define W 119     // W
# define S 115     // S
# define A 97      // A
# define D 100     // D
# define LA 65361  // arrow key left
# define RA 65363  // arrow key right
# define M 109     // Minimap key

// SIZE
# define PX 64
# define PACE 10
# define TURNANGLE 0.1
# define PLYLEN 9
# define FOV 1.047198
# define HALF_FOV 0.523599
# define PLANE_DIST 652.719
# define WIDTH 1000
# define HEIGHT 1000
# define MINIMAP_SIZE 100

// MATH
# define PI 3.14159265
# define TOLERANCE 0.000001
# define X 0
# define Y 1

// flood_fill
# define CHECKED 'V'

/*

// debug printf
#ifdef DEBUG
# define PRINTF(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
# define PRINTF(fmt, ...)
#endif

*/

// minilibx-linux event
enum				e_event
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

enum				e_mouse_event
{
	LEFT_CLICK = 1,
	RIGHT_CLICK = 2,
	MIDDLE_CLICK = 3,
	SCROLL_UP = 4,
	SCROLL_DOWN = 5
};

// direction
typedef enum e_direction
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
	NONE
}			t_direction;

// player_vector
typedef struct s_vector
{
	double	x;
	double	y;
}				t_vector;

// integer_vector
typedef struct s_vct_int
{
	int	x;
	int	y;	
}				t_vct_int;

// player
typedef struct s_player
{
	t_vector	position;
	t_vct_int	array_pos;
	t_vector	direction;
	double		angle;
}				t_player;

// raycasting
typedef struct s_ray
{
	t_vct_int	vct;
	t_vct_int	step;
	t_vector	next_grid;
	t_vector	direction;
	t_vector	delta;
	double		angle;
	double		distance;
	int			hit_wall;
	int			wall_dir;
	double		wall_hit_point;
	int			wall_height;
}				t_ray;

// MinilibX_image
typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_size;
	int		endian;
}			t_image;

// texture_data
typedef struct s_texture
{
	t_image		image;
	int			width;
	int			height;	
}				t_texture;

// MinilibX_window
typedef struct s_window
{
	t_image		image;
	t_image		minimap_img;
	void		*mlx;
	void		*win;
}				t_window;

// all_data
typedef struct s_data
{
	char		**file;
	char		*texture_paths[5];
	int			floor_rgb[3];
	int			ceiling_rgb[3];
	char		**map;
	int			rows;
	int			columns;
	t_player	player;
	t_window	graphic;
	t_texture	textures[5];
	t_ray		*rays;
	bool		show_minimap;
	double		minimap_scale;
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
int		exit_game(t_data *data);

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
void	ft_raycasting_init(t_data *data, t_ray *ray, int width);
void	ft_raycasting(t_data *data, t_ray *ray);
void	ft_raycasting_result(t_data *data, t_ray *ray);

// draw_wall.c
void	ft_draw_wall(t_data *data);

// key_hook.c
int		key_hook(int keycode, t_data *data);

// mouse_hook.c
int		mouse_hook(int event, int x, int y, t_data *data);

// minimap.c
void	ft_draw_minimap(t_data *data);

// main.c
void	ft_print_screen(t_data *data);

#endif
