/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 16:42:15 by hakbas            #+#    #+#             */
/*   Updated: 2024/07/16 19:53:28 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <readline/readline.h>

int	exec_forked_builtin(char **args, t_env **ms_env)
{
	int	stat;

	stat = exec_builtin(args, ms_env);
	free_array(args);
	free_env(ms_env);
	rl_clear_history();
	exit(stat);
}

int	exec_builtin(char **args, t_env **ms_env)
{
	char	*cmd;

	cmd = args[0];
	if (str_equal(cmd, "echo"))
		return (echo(args));
	else if (str_equal(cmd, "pwd"))
		return (pwd());
	else if (str_equal(cmd, "env"))
		return (env(*ms_env));
	else if (str_equal(cmd, "export"))
		return (builtin_export(args, ms_env));
	else if (str_equal(cmd, "unset"))
		return (unset(args, ms_env));
	else if (str_equal(cmd, "cd"))
		return (cd(args, *ms_env));
	else if (str_equal(cmd, "exit"))
		return (builtin_exit(args, ms_env));
	else
		return (EXIT_FAILURE);
}
