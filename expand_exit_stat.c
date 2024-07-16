/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exit_stat.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:17:19 by hakbas            #+#    #+#             */
/*   Updated: 2024/07/16 14:14:21 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

static char	*get_exit_stat_pos(char *input);
static void	update_input(char **input, char *exit_code, char *second_part);

void	expand_exit_stat(char **input, int exit_stat)
{
	char	*exit_stat_pos;
	char	*exit_stat_str;

	exit_stat_pos = get_exit_stat_pos(*input);
	if (exit_stat_pos)
	{
		*exit_stat_pos = '\0';
		exit_stat_str = ft_itoa(exit_stat);
		update_input(input, exit_stat_str, exit_stat_pos + 2);
		free (exit_stat_str);
		expand_exit_stat(input, exit_stat);
	}
}

static char	*get_exit_stat_pos(char *input)
{
	while (input && *input)
	{
		if (*input == '\'')
		{
			input++;
			while (*input && *input != '\'')
				input++;
		}
		if (*input == '\"')
		{
			input++;
			while (*input && *input != '\"')
			{
				if (*input == '$' && input[1] == '?')
					return (input);
				input++;
			}
		}
		if (*input == '$' && input[1] == '?')
			return (input);
		input++;
	}
	return (NULL);
}

/*
	check this function in case of error with memory or leaks
	because added null checks can break the calling functions
 */
static void	update_input(char **input, char *exit_code, char *second_part)
{
	char	*first_part;
	char	*updated_input;

	first_part = ft_strjoin(*input, exit_code);
	if (!first_part)
	{
		free (*input);
		*input = NULL;
		return ;
	}
	updated_input = ft_strjoin(first_part, second_part);
	if (!updated_input)
	{
		free (*input);
		free (first_part);
		*input = NULL;
		return ;
	}
	free (*input);
	free (first_part);
	*input = updated_input;
}
