/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:16:35 by hakbas            #+#    #+#             */
/*   Updated: 2024/07/16 14:27:59 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "minishell.h"

static int	init_minishell(t_env *ms_env);
static void	increment_shlvl(t_env *ms_env);

int	main(int argc, char **argv, char **envp)
{
	t_env	*ms_env;

	(void)argv;
	if (argc > 1)
	{
		ft_putendl_fd("Invalid number of arguments.", STDOUT_FILENO);
		return (EXIT_FAILURE);
	}
	ms_env = init_env(envp);
	if (!ms_env)
	{
		ft_putendl_fd("Failed to create environment variables!", STDOUT_FILENO);
		return (EXIT_FAILURE);
	}
	increment_shlvl(ms_env);
	return (init_minishell(ms_env));
}

static int	init_minishell(t_env *ms_env)
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

static void	increment_shlvl(t_env *ms_env)
{
	int		shlvl;
	char	*current_value;
	char	*new_value;

	current_value = get_env_value("SHLVL", ms_env);
	if (!current_value)
		shlvl = 1;
	else
	{
		shlvl = ft_atoi(current_value);
		if (shlvl < 0 || shlvl > 1000)
			shlvl = 1;
		else
			shlvl += 1;
	}
	new_value = ft_itoa(shlvl);
	if (!new_value)
		return ;
	update_env_var("SHLVL", new_value, ms_env);
	free(new_value);
}
