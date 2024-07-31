/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 21:59:00 by hakbas            #+#    #+#             */
/*   Updated: 2024/07/31 21:59:41 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdlib.h>

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
