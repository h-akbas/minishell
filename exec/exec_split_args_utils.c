/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_split_args_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 23:30:04 by hakbas            #+#    #+#             */
/*   Updated: 2024/08/29 00:02:03 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../libft/libft.h"
#include "../minishell.h"

static bool	is_delimiter(char c, char delimiter)
{
	return (c == delimiter || c == '\0');
}

static int	count_words(char *str, char delimiter)
{
	int		count;
	bool	in_quotes;
	char	quote_char;

	count = 0;
	in_quotes = false;
	quote_char = '\0';
	while (*str)
	{
		while (*str && is_delimiter(*str, delimiter) && !in_quotes)
			str++;
		if (*str)
			count++;
		while (*str && (!is_delimiter(*str, delimiter) || in_quotes))
		{
			toggle_quotes(*str, &in_quotes, &quote_char);
			str++;
		}
	}
	return (count);
}

static char	*extract_word(char **str, char delimiter)
{
	char	*start;
	char	*word;
	bool	in_quotes;
	char	quote_char;
	size_t	length;

	start = *str;
	in_quotes = false;
	quote_char = '\0';
	length = 0;
	while (**str && (!is_delimiter(**str, delimiter) || in_quotes))
	{
		toggle_quotes(**str, &in_quotes, &quote_char);
		(*str)++;
		length++;
	}
	word = (char *)malloc((length + 1) * sizeof(char));
	if (!word)
		return (NULL);
	ft_strlcpy(word, start, length + 1);
	word[length] = '\0';
	return (word);
}

static void	free_result(char **result, int i)
{
	while (i > 0)
		free(result[--i]);
	free(result);
}

char	**ft_split_preserve_quotes(char *cmd, char delimiter)
{
	char	**result;
	int		words_count;
	int		i;

	if (!cmd)
		return (NULL);
	words_count = count_words(cmd, delimiter);
	result = (char **)malloc((words_count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	while (*cmd)
	{
		while (*cmd && is_delimiter(*cmd, delimiter))
			cmd++;
		if (*cmd)
		{
			result[i] = extract_word(&cmd, delimiter);
			if (!result[i])
				return (free_result(result, i), NULL);
			i++;
		}
	}
	result[i] = NULL;
	return (result);
}
