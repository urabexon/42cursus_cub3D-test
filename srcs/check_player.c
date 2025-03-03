/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hurabe <hurabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 19:09:23 by hurabe            #+#    #+#             */
/*   Updated: 2025/03/03 17:33:52 by hurabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_player_angle(t_player *player, char dir)
{
	if (dir == 'N')
		player->angle = PI / 2;
	else if (dir == 'S')
		player->angle = -PI / 2;
	else if (dir == 'E')
		player->angle = 0;
	else if (dir == 'W')
		player->angle = PI;
}

static void	set_player_direction(t_player *player, char dir)
{
	if (dir == 'N')
	{
		player->direction.y = 1;
		player->direction.x = 0;
	}
	else if (dir == 'S')
	{
		player->direction.y = -1;
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

void	set_player_info(t_data *data, int y, int x, char **map)
{
	data->player.array_pos.y = y;
	data->player.array_pos.x = x;
	data->player.position.y = PX * (data->rows - y) - (PX / 2);
	data->player.position.x = PX * x + (PX / 2);
	set_player_direction(&data->player, map[y][x]);
	set_player_angle(&data->player, map[y][x]);
}

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
			if (ft_strchr("NSEW", map[y][x]))
			{
				if (player_found)
					exit_error("Some players on map!", data);
				player_found = true;
				set_player_info(data, y, x, map);
			}
			x++;
		}
		y++;
	}
	if (!player_found)
		exit_error("No player on map!", data);
}
