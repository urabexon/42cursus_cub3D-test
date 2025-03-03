/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hurabe <hurabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 22:15:31 by hurabe            #+#    #+#             */
/*   Updated: 2025/03/03 17:27:23 by hurabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	void	get_content(t_data *data, int fd, int counter)
{
	char	*line;

	if (counter < 0)
		exit_error("Invalid file!", data);
	line = get_next_line(fd);
	if (line)
		get_content(data, fd, counter + 1);
	else if (counter == 0)
		exit_error("Invalid file!", data);
	else
	{
		data->file = (char **)malloc(sizeof(char *) * (counter + 1));
		if (!data->file)
		{
			free(line);
			exit_error("error", data);
		}
		data->file[counter] = NULL;
	}
	if (data->file)
		data->file[counter] = line;
}

static	void	get_file_contents(t_data *data, char *filedata)
{
	int	fd;

	fd = open(filedata, O_RDONLY);
	if (fd == -1)
		exit_error("Invalid file path!", data);
	get_content(data, fd, 0);
	close(fd);
}

void	set_data_from_file(t_data *data, char **file)
{
	int	i;

	i = 0;
	while (file[i])
	{
		replace_str(file[i], "\f\r\t\v", ' ');
		replace_str(file[i], "\n", '\0');
		i++;
	}
	set_metadata(data, &file);
	while (file && *file && is_str_type(*file, ft_isspace))
		file++;
	if (!*file)
		exit_error("Invalid file!", data);
	data->rows = get_map_rows(file);
	data->columns = get_map_columns(file);
	if (data->rows <= 0 || data->columns <= 0)
		exit_error("Invalid map!", data);
	set_map(data, file);
}

void	init_data(t_data *data, char *filedata)
{
	setup(data);
	get_file_contents(data, filedata);
	set_data_from_file(data, data->file);
}
