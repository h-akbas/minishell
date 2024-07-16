/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 19:51:26 by hakbas            #+#    #+#             */
/*   Updated: 2024/07/16 14:11:01 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

static int	declare_env(t_env *ms_env);

int	builtin_export(char **args, t_env **ms_env)
{
	char	*key_pair;
	char	*varname;
	int		exit_stat;

	args++;
	exit_stat = EXIT_SUCCESS;
	if (!*args)
		return (declare_env(*ms_env));
	while (*args)
	{
		key_pair = *args;
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
		args++;
	}
	exit(exit_stat);
}

static int	declare_env(t_env *ms_env)
{
	t_env	*tmp;

	tmp = ms_env;
	while (tmp)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(get_name_only(tmp->key_pair), STDOUT_FILENO);
		if (ft_strchr(tmp->key_pair, '='))
		{
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
			ft_putstr_fd(get_value_only(tmp->key_pair), STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
