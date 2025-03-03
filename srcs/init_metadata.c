/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_metadata.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hurabe <hurabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 19:31:13 by hurabe            #+#    #+#             */
/*   Updated: 2025/03/03 17:29:13 by hurabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	set_rgb_value(char **numbers, int *rgb)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (ft_strlen(numbers[i]) > 3 || !is_str_type(numbers[i], ft_isdigit))
			return (EXIT_FAILURE);
		rgb[i] = ft_atoi(numbers[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	set_rgb(int *rgb, char *splited)
{
	char	**numbers;

	if (rgb[0] != -1 || rgb[1] != -1 || rgb[2] != -1)
	{
		error_msg("Duplicate rgb!");
		return (EXIT_FAILURE);
	}
	if (!splited)
		return (EXIT_FAILURE);
	else
	{
		numbers = ft_split(splited, ',');
		if (strarr_size(numbers) != 3 || set_rgb_value(numbers, rgb))
		{
			free_all(numbers);
			error_msg("Invalid rgb value!");
			return (EXIT_FAILURE);
		}
		free_all(numbers);
	}
	return (EXIT_SUCCESS);
}

static int	set_texture_path(t_data *data, int dir, char *path)
{
	int	fd;

	if (data->texture_paths[dir] != NULL)
	{
		error_msg("Duplicate texture!");
		return (EXIT_FAILURE);
	}
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		error_msg("Invalid texture path!");
		return (EXIT_FAILURE);
	}
	data->texture_paths[dir] = ft_strdup(path);
	close(fd);
	return (EXIT_SUCCESS);
}

static int	handle_metadata(t_data *data, char **splited)
{
	if (!ft_strcmp(splited[0], "NO"))
		return (set_texture_path(data, NORTH, splited[1]));
	else if (!ft_strcmp(splited[0], "SO"))
		return (set_texture_path(data, SOUTH, splited[1]));
	else if (!ft_strcmp(splited[0], "WE"))
		return (set_texture_path(data, WEST, splited[1]));
	else if (!ft_strcmp(splited[0], "EA"))
		return (set_texture_path(data, EAST, splited[1]));
	else if (!ft_strcmp(splited[0], "C"))
		return (set_rgb(data->ceiling_rgb, splited[1]));
	else if (!ft_strcmp(splited[0], "F"))
		return (set_rgb(data->floor_rgb, splited[1]));
	return (EXIT_SUCCESS);
}

void	set_metadata(t_data	*data, char ***file)
{
	char	**split_line;

	while (*file && **file)
	{
		split_line = ft_split(**file, ' ');
		if (split_line && split_line[0])
		{
			if (handle_metadata(data, split_line))
			{
				free_all(split_line);
				exit_error(NULL, data);
			}
		}
		free_all(split_line);
		(*file)++;
		if (strarr_size(data->texture_paths) == 4 \
			&& data->ceiling_rgb[2] != -1 && data->floor_rgb[2] != -1)
			break ;
	}
}
