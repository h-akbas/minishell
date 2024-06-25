/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:05:26 by hakbas            #+#    #+#             */
/*   Updated: 2024/06/25 19:11:00 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

t_list	*init_env(char	**envp, t_data *data);
{
	char	*eq;
	char	*name;
	char	*home;
	t_list	*env_lst;

	env_lst = NULL;
	while (*envp)
	{
		eq = ft_strchr(*env, '=');
		
		envp++;
	}
}