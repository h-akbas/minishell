/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndogan <ndogan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:16:35 by hakbas            #+#    #+#             */
/*   Updated: 2024/07/11 13:08:54 by ndogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "minishell.h"

static int	init_minishell(t_env *ms_env);
//deneme
int	main(int argc, char **argv, char **envp)
{
	int	exit_stat;

	exit_stat = EXIT_SUCCESS;
	(void)argv;
	if (argc > 1)
	{
		ft_putendl_fd("Invalid number of arguments.", 2);
		exit_stat = EXIT_FAILURE;
	}
	else
		exit_stat = init_minishell(init_env(envp));
	return(exit_stat);
}

static int	init_minishell(t_env *ms_env)
{
	int		exit_stat;
	char	*input;
	char	**cmds;

	if (!ms_env)
		return (EXIT_FAILURE);
	exit_stat = EXIT_SUCCESS;
	while (1)
	{
		init_main_signals();
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
			exit_stat = multiple_commands(cmds, &ms_env);
			free_matrix(cmds);
		}
	}
	return (exit_stat);
}
