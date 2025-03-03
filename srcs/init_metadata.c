/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_metadata.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hurabe <hurabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 19:31:13 by hurabe            #+#    #+#             */
/*   Updated: 2025/03/03 21:34:01 by hurabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// RGB値のバリデーションと数値変換を行う関数
static int	set_rgb_value(char **numbers, int *rgb)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		// 文字列が3桁以上、または数字以外の文字を含む場合、エラー
		if (ft_strlen(numbers[i]) > 3 || !is_str_type(numbers[i], ft_isdigit))
			return (EXIT_FAILURE);
		rgb[i] = ft_atoi(numbers[i]);
		// RGB(0~255)でない場合はエラー
		if (rgb[i] < 0 || rgb[i] > 255)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

// RGBの色情報を取得し、CかFにセットする関数
static int	set_rgb(int *rgb, char *splited)
{
	char	**numbers;

	// 設定していたらエラー
	if (rgb[0] != -1 || rgb[1] != -1 || rgb[2] != -1)
	{
		error_msg("Duplicate rgb!");
		return (EXIT_FAILURE);
	}
	// rgbの中身がない、CまたはFのみの場合
	if (!splited)
		return (EXIT_FAILURE);
	else
	{
		// rgb値をカンマ区切りで取得する
		numbers = ft_split(splited, ',');
		// rgb値が３つじゃない、または不正な値だったらエラー、問題なければ値をセット
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

// テクスチャパスをバリデーション、データをセットする関数
static int	set_texture_path(t_data *data, int dir, char *path)
{
	int	fd;

	// 設定していたらエラー
	if (data->texture_paths[dir] != NULL)
	{
		error_msg("Duplicate texture!");
		return (EXIT_FAILURE);
	}
	// テクスチャファイルを読み込み専用で開く
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		error_msg("Invalid texture path!");
		return (EXIT_FAILURE);
	}
	// 正常に開けた場合はテクスチャパスを保存する
	data->texture_paths[dir] = ft_strdup(path);
	close(fd);
	return (EXIT_SUCCESS);
}

// '.cub'ファイルの1行を解析し、テクスチャかRGBを設定する設定する関数
static int	handle_metadata(t_data *data, char **splited)
{
	// 壁(東西南北)の行ならテクスチャファイルを確認する
	if (!ft_strcmp(splited[0], "NO"))
		return (set_texture_path(data, NORTH, splited[1]));
	else if (!ft_strcmp(splited[0], "SO"))
		return (set_texture_path(data, SOUTH, splited[1]));
	else if (!ft_strcmp(splited[0], "WE"))
		return (set_texture_path(data, WEST, splited[1]));
	else if (!ft_strcmp(splited[0], "EA"))
		return (set_texture_path(data, EAST, splited[1]));
	// 天井、床の行ならRGBを確認する
	else if (!ft_strcmp(splited[0], "C"))
		return (set_rgb(data->ceiling_rgb, splited[1]));
	else if (!ft_strcmp(splited[0], "F"))
		return (set_rgb(data->floor_rgb, splited[1]));
	// 空白の行なら何もしない
	return (EXIT_SUCCESS);
}

// '.cub'ファイルのデータ(テクスチャとRGB)を解析する関数
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
		// fileを進めて読み終わった部分を飛ばす(最終的にマップ部分が残る)
		(*file)++;
		// メタデータの設定が終わったら処理終了
		if (strarr_size(data->texture_paths) == 4 \
			&& data->ceiling_rgb[2] != -1 && data->floor_rgb[2] != -1)
			break ;
	}
}
