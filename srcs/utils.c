/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hurabe <hurabe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 22:01:14 by hurabe            #+#    #+#             */
/*   Updated: 2025/01/25 23:08:11 by hurabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// 2次元配列のfree
void	free_all(char **arr)
{
	size_t	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i] != 0)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

// 指定した文字が文字列's'に含まれているかをチェックする関数
bool	is_include_char(char *s, int c)
{
	c = (char)c;
	while (*s)
	{
		if (*s == c)
			return (true);
		s++;
	}
	// 終端があるかチェック
	if (c == '\0')
		return (true);
	return (false);
}

// str内のremoveに含まれる文字をreplaseに置き換える関数
// removeは置換する文字のリスト（"\f\r\t\v"）
void	replace_str(char *str, char *remove, char replace)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_include_char(remove, str[i]))
			str[i] = replace;
		i++;
	}
}

// 2次元配列の要素数を取得する関数
int	strarr_size(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}

// 文字列が特定の条件を満たしているかチェックする関数
// 文字の条件を判定する関数ポインタ(ft_isdigitなど)
bool	is_str_type(char *str, int (*function)(int))
{
	size_t	i;

	if (!str || !function)
		return (false);
	i = 0;
	while (str[i])
	{
		if (!function(str[i]))
			return (false);
		i++;
	}
	return (true);
}
