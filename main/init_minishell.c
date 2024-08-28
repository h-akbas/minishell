/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 21:59:00 by hakbas            #+#    #+#             */
/*   Updated: 2024/08/29 02:15:30 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include "../libft/libft.h"

static void	handle_pipe_at_end(char **input);

int	init_minishell(t_env *ms_env)
{
	int		exit_stat;
	char	*input;
	char	**cmds;

	exit_stat = EXIT_SUCCESS;
	while (1)
	{
		set_main_signals();
		input = parse_prompt(ms_env);
		handle_pipe_at_end(&input);
		if (input_error(input, &exit_stat, ms_env))
			continue ;
		handle_expansions(&input, ms_env, exit_stat);
		if (!has_pipe(input))
			exit_stat = single_cmd(input, &ms_env);
		else
		{
			cmds = split_cmds(input);
			free(input);
			exit_stat = multiple_cmd(cmds, &ms_env);
			free_array(cmds);
		}
	}
	return (exit_stat);
}

static void	handle_pipe_at_end(char **input)
{
	char	*next_input;
	char	*full_input;

	next_input = NULL;
	full_input = NULL;
	while (pipe_at_end(*input))
	{
		next_input = readline("> ");
		full_input = ft_strjoin(*input, next_input);
		free(*input);
		free(next_input);
		*input = full_input;
	}
}
