/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hurabe <hurabe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:07:40 by hurabe            #+#    #+#             */
/*   Updated: 2024/05/21 21:35:39 by hurabe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**free_array(char **array, size_t i)
{
	while (i > 0)
	{
		i--;
		free(array[i]);
	}
	free(array);
	return (NULL);
}

static int	ft_count_words(char	const *s, char c)
{
	int	count;
	int	word;

	count = 0;
	word = 0;
	if (!s)
		return (0);
	while (*s)
	{
		if (*s != c && !word)
		{
			word = 1;
			count++;
		}
		else if (*s == c)
		{
			word = 0;
		}
		s++;
	}
	return (count);
}

static char	*ft_malloc_word(char const *start, char const *end)
{
	size_t	i;
	size_t	len;
	char	*word;

	i = 0;
	len = end - start;
	word = (char *)malloc((len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (i < len)
	{
		word[i] = start[i];
		i++;
	}
	word[len] = '\0';
	return (word);
}

static char	**ft_input_word(char const *s, char c, size_t *index, int num_count)
{
	size_t	start;
	size_t	end;
	char	**words;
	int		i;

	i = 0;
	words = (char **)malloc(sizeof(char *) * (num_count + 1));
	if (!words)
		return (NULL);
	while (i < num_count)
	{
		while (s[*index] && s[*index] == c)
			(*index)++;
		start = *index;
		while (s[*index] && s[*index] != c)
			(*index)++;
		end = *index;
		words[i] = ft_malloc_word(s + start, s + end);
		if (!words[i])
			return (free_array(words, i));
		i++;
	}
	words[i] = (NULL);
	return (words);
}

char	**ft_split(char const *s, char c)
{
	size_t	num_count;
	size_t	index;

	if (!s)
		return (NULL);
	index = 0;
	num_count = ft_count_words(s, c);
	return (ft_input_word(s, c, &index, num_count));
}
