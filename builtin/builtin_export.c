/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 19:51:26 by hakbas            #+#    #+#             */
/*   Updated: 2024/09/01 23:37:29 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdlib.h>
#include <unistd.h>

static int	declare_env(t_env *ms_env);
static int	process_export_arg(char *key_pair, t_env **ms_env);

int	builtin_export(char **args, t_env **ms_env)
{
	int		exit_stat;

	args++;
	exit_stat = EXIT_SUCCESS;
	if (!*args)
		return (declare_env(*ms_env));
	while (*args)
	{
		if (process_export_arg(*args, ms_env) == EXIT_FAILURE)
			exit_stat = EXIT_FAILURE;
		args++;
	}
	return (exit_stat);
}

int	process_export_arg(char *key_pair, t_env **ms_env)
{
	char	*varname;
	int		exit_stat;

	exit_stat = EXIT_SUCCESS;
	varname = get_name_only(key_pair);
	if (!valid_varname(varname) || str_equal(key_pair, "="))
	{
		print_varname_error("export", key_pair);
		exit_stat = EXIT_FAILURE;
	}
	else if (get_env_node(varname, *ms_env))
		update_env_var(varname, get_value_only(key_pair), *ms_env);
	else
		append_list(key_pair, ms_env);
	free(varname);
	return (exit_stat);
}

static int	declare_env(t_env *ms_env)
{
	t_env	*tmp;
	char	**envp;

	envp = ms_env_to_envp(ms_env);
	tmp = init_env(envp);
	merge_sort(&tmp);
	declare_statement(tmp);
	free_env(&tmp);
	free_array(envp);
	return (EXIT_SUCCESS);
}
