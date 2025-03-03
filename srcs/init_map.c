/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hurabe <hurabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 20:30:13 by hurabe            #+#    #+#             */
/*   Updated: 2025/03/03 17:30:06 by hurabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_map_columns(char **file)
{
	int	columns;

	columns = 0;
	while (file && *file)
	{
		if ((int)ft_strlen(*file) > columns)
			columns = (int)ft_strlen(*file);
		file++;
	}
	return (columns);
}

int	get_map_rows(char **file)
{
	int	rows;

	rows = 0;
	while (file && file[rows])
	{
		if (is_str_type(file[rows], ft_isspace))
			return (-1);
		rows++;
	}
	return (rows);
}

void	set_map(t_data *data, char **file)
{
	int	y;
	int	x;

	data->map = (char **)ft_calloc(data->rows + 1, sizeof(char *));
	if (!data->map)
		exit_error("error : malloc", data);
	y = 0;
	while (y < data->rows)
	{
		data->map[y] = (char *)ft_calloc(data->columns + 1, sizeof(char));
		if (!data->map[y])
			exit_error("error : malloc", data);
		x = 0;
		while (file[y][x])
		{
			data->map[y][x] = file[y][x];
			x++;
		}
		while (x < data->columns - 1)
		{
			data->map[y][x] = ' ';
			x++;
		}
		y++;
	}
}
