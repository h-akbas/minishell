/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:43:11 by hakbas            #+#    #+#             */
/*   Updated: 2024/06/26 18:10:14 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_shell_env(t_env *env, char **envp)
{
	int	i;
	int	j;
	size_t	len;

	env->original_env = parse_envp(envp);
	while (envp[i])
		i++;
		

}
