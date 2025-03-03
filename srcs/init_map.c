/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hurabe <hurabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 20:30:13 by hurabe            #+#    #+#             */
/*   Updated: 2025/03/03 21:33:50 by hurabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// マップの最大列数を取得する関数
int	get_map_columns(char **file)
{
	int	columns;

	columns = 0;
	while (file && *file)
	{
		// // より長い行があれば値を更新する(\0文字文を足しておく)
		// if ((int)ft_strlen(*file) + 1 > columns)
		// 	columns = (int)ft_strlen(*file) + 1;
		if ((int)ft_strlen(*file) > columns)
			columns = (int)ft_strlen(*file);
		file++;
	}
	return (columns);
}

// マップの行数を取得する関数
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

// マップデータをdata->mapにコピーする関数
void	set_map(t_data *data, char **file)
{
	int	y;
	int	x;

	// マップ全体のメモリ確保
	data->map = (char **)ft_calloc(data->rows + 1, sizeof(char *));
	if (!data->map)
		exit_error("error : malloc", data);
	// マップを取得する
	y = 0;
	while (y < data->rows)
	{
		// マップ(各行)のメモリを確保する
		data->map[y] = (char *)ft_calloc(data->columns + 1, sizeof(char));
		if (!data->map[y])
			exit_error("error : malloc", data);
		x = 0;
		// コピー
		while (file[y][x])
		{
			data->map[y][x] = file[y][x];
			x++;
		}
		// 残りはスペースで埋める(\0だと探索の時にセグフォするため)
		while (x < data->columns - 1)
		{
			data->map[y][x] = ' ';
			x++;
		}
		y++;
	}
}
