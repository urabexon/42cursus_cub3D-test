/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hurabe <hurabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 22:15:31 by hurabe            #+#    #+#             */
/*   Updated: 2025/03/03 21:34:15 by hurabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// ファイルの内容を再帰的に取得し、配列に格納する関数
static	void	get_content(t_data *data, int fd, int counter)
{
	char	*line;

	if (counter < 0)
		exit_error("Invalid file!", data);
	line = get_next_line(fd);
	// もし行を取得できたら、もう一度行を読み込む
	if (line)
		get_content(data, fd, counter + 1);
	// 初回は行を取得できない、中身がないのでエラー表示
	else if (counter == 0)
		exit_error("Invalid file!", data);
	// それ以降行を取得できない場合はファイルの終端なので配列を準備する
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
	// メモリ確保できたら行を配列にセットする
	if (data->file)
		data->file[counter] = line;
}

// 指定されたファイルを開き、その内容を取得する
static	void	get_file_contents(t_data *data, char *filedata)
{
	int	fd;

	fd = open(filedata, O_RDONLY);
	if (fd == -1)
		exit_error("Invalid file path!", data);
	get_content(data, fd, 0);
	close(fd);
}

// 取得したファイルの内容をt_dataにセットする関数
void	set_data_from_file(t_data *data, char **file)
{
	int	i;

	// スペース系を' 'に統一
	i = 0;
	while (file[i])
	{
		replace_str(file[i], "\f\r\t\v", ' ');
		replace_str(file[i], "\n", '\0');
		i++;
	}
	// 設定情報をdataに取得する
	set_metadata(data, &file);
	// 不要な行をスキップ
	while (file && *file && is_str_type(*file, ft_isspace))
		file++;
	if (!*file)
		exit_error("Invalid file!", data);
	// マップの行数と最大長を取得
	data->rows = get_map_rows(file);
	data->columns = get_map_columns(file);
	if (data->rows <= 0 || data->columns <= 0)
		exit_error("Invalid map!", data);
	// マップをdataに取得する
	set_map(data, file);
}

// 初期化処理を行う関数
void	init_data(t_data *data, char *filedata)
{
	// データに初期値をセットする
	setup(data);
	// ファイルの中身を配列にする
	get_file_contents(data, filedata);
	// ファイルの中身をdataに格納する
	set_data_from_file(data, data->file);
}
