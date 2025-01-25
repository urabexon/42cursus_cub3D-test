/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hurabe <hurabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:49:10 by hurabe            #+#    #+#             */
/*   Updated: 2025/01/25 19:21:05 by hurabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// t_data解放用
static void	free_data(t_data *data)
{
	int	i;

	i = 0;
	// 東西南北のテクスチャを解放する
	while (i < 4)
	{
		if (data->texture_paths[i])
			free(data->texture_paths[i]);
		// 各テクスチャのmlx
		if (data->textures[i].image.img)
			mlx_destroy_image(data->graphic.mlx, data->textures[i].image.img);
		i++;
	}
	if (data->file)
		free_all(data->file);
	if (data->map)
		free_all(data->map);
	// mlx
	if (data->graphic.image.img)
		mlx_destroy_image(data->graphic.mlx, data->graphic.image.img);
	if (data->graphic.win)
		mlx_destroy_window(data->graphic.mlx, data->graphic.win);
	if (data->graphic.mlx)
	{
		mlx_destroy_display(data->graphic.mlx);
		free(data->graphic.mlx);
	}
}

// エラーメッセージ用
void	error_msg(char *message)
{
	if (message)
	{
		ft_putstr_fd("Error\n", STDERR_FILENO);
		ft_putstr_fd(message, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
}

// エラーが発生したらfreeしてプログラム終了
void	exit_error(char *message, t_data *data)
{
	free_data(data);
	if (message)
		error_msg(message);
	exit(EXIT_FAILURE);
}

// ゲームの正常終了用
void	exit_game(t_data *data)
{
	free_data(data);
	ft_putstr_fd(" THANKS FOR PLAYING! ", STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	exit(EXIT_SUCCESS);
}
