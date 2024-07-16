/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 19:28:37 by hakbas            #+#    #+#             */
/*   Updated: 2024/07/16 14:15:22 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

int	env(t_env *ms_env)
{
	t_env	*tmp;

	tmp = ms_env;
	while (tmp)
	{
		if (ft_strchr(tmp->key_pair, '='))
			ft_putendl_fd(tmp->key_pair, STDOUT_FILENO);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
