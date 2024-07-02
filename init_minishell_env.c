/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell_env.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:27:13 by hakbas            #+#    #+#             */
/*   Updated: 2024/06/26 17:35:17 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

int	init_data(t_env *env, char **envp)
{
	int	i;
	int	status;
	int sh_lvl;

	status = init_shell_env(env, envp, 0);
	sh_lvl = get_env_index(env, "SHLVL");
	i = 0;
	if (sh_lvl >= 0)
		i = ft_atoi(env->parsed_env[sh_lvl][1]);
	update_env_stat(env, i + 1, "SHLVL=");
	init_defaults(env, 0);
	return (status);
}
