/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 16:00:29 by hakbas            #+#    #+#             */
/*   Updated: 2024/07/21 17:53:12 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"
#include <stdbool.h>
#include <unistd.h>

bool	is_builtin(char *cmd)
{
	if (!cmd)
		return (false);
	return (
		str_equal(cmd, "echo")
		|| str_equal(cmd, "cd")
		|| str_equal(cmd, "pwd")
		|| str_equal(cmd, "export")
		|| str_equal(cmd, "unset")
		|| str_equal(cmd, "env")
		|| str_equal(cmd, "exit")
	);
}

void	update_wd(t_env *ms_env)
{
	char	*pwd;
	char	*oldpwd;
	char	cwd[PATH_MAX];

	pwd = get_env_value("PWD", ms_env);
	oldpwd = get_env_value("OLDPWD", ms_env);
	if (oldpwd && pwd && *pwd)
		update_env_var("OLDPWD", pwd, ms_env);
	if (pwd && *pwd)
		update_env_var("PWD", getcwd(cwd, PATH_MAX), ms_env);
}

void	declare_statement(t_env *env)
{
	char	*name;
	char	*value;

	while (env)
	{
		name = get_name_only(env->key_pair);
		value = get_value_only(env->key_pair);
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(name, STDOUT_FILENO);
		if (ft_strchr(env->key_pair, '='))
		{
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
			ft_putstr_fd(value, STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
		free(name);
		env = env->next; 	
	}
}