/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hurabe <hurabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 19:03:49 by hurabe            #+#    #+#             */
/*   Updated: 2025/03/03 17:35:58 by hurabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	flood_fill(t_data *data, int y, int x, t_vct_int *dir)
{
	int	i;

	if (x < 0 || x >= data->columns || y < 0 || y >= data->rows)
		return (EXIT_FAILURE);
	if (data->map[y][x] == ' ')
		return (EXIT_FAILURE);
	if (data->map[y][x] == '1' || data->map[y][x] == CHECKED)
		return (EXIT_SUCCESS);
	data->map[y][x] = CHECKED;
	i = 0;
	while (i < 8)
	{
		if (flood_fill(data, y + dir[i].y, x + dir[i].x, dir))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

static void	set_directions(t_vct_int *directions)
{
	directions[0] = (t_vct_int){-1, -1};
	directions[1] = (t_vct_int){-1, 0};
	directions[2] = (t_vct_int){-1, 1};
	directions[3] = (t_vct_int){0, -1};
	directions[4] = (t_vct_int){0, 1};
	directions[5] = (t_vct_int){1, -1};
	directions[6] = (t_vct_int){1, 0};
	directions[7] = (t_vct_int){1, 1};
}

static void	check_map_structure(t_data *data, char **map)
{
	int			x;
	int			y;
	char		org;
	t_vct_int	dir[8];

	x = data->player.array_pos.x;
	y = data->player.array_pos.y;
	org = map[y][x];
	map[y][x] = '0';
	set_directions(dir);
	if (flood_fill(data, y, x, dir))
		exit_error("Invalid map!", data);
	map[y][x] = org;
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
			if (!ft_strchr(" 01NSEW", map[y][x]))
				exit_error("Invalid characters on map!", data);
			x++;
		}
		y++;
	}
}

void	check_map(t_data *data)
{
	check_components(data, data->map);
	check_player(data, data->map);
	check_map_structure(data, data->map);
}
