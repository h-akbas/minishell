/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <halilakbas1992@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 13:03:12 by hakbas            #+#    #+#             */
/*   Updated: 2023/10/23 15:21:53 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**free_all(char **result, int j)
{
	while (j >= 0)
	{
		free(result[j]);
		j--;
	}
	free(result);
	return (NULL);
}

static int	count_words(char const *s, char c)
{
	int		count;
	int		in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
		{
			in_word = 0;
		}
		s++;
	}
	return (count);
}

static char	**fill_result(char **res, char const *s, char c, int wc)
{
	int		i;
	int		j;
	int		start;

	i = 0;
	j = 0;
	while (wc--)
	{
		while (s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		res[j] = (char *)malloc(i - start + 1);
		if (!res[j])
			return (free_all(res, j - 1));
		ft_strlcpy(res[j++], s + start, i - start + 1);
	}
	res[j] = 0;
	return (res);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		wc;

	result = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!s || !result)
		return (NULL);
	wc = count_words(s, c);
	return (fill_result(result, s, c, wc));
}
