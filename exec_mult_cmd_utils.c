/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_mult_cmd_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 18:32:29 by hakbas            #+#    #+#             */
/*   Updated: 2024/07/14 18:35:58 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"
#include <readline/readline.h>
#include <stdlib.h>

int	*init_children_pid(char **cmds)
{
	int		*children_pid;
	size_t	size;
	
	size = sizeof(int) * (arr_len(cmds) + 1);
	children_pid = malloc(size);
	if (!children_pid)
		return (NULL);
	ft_bzero(children_pid, size);
	return (children_pid);
}

void	clean_after_exec(int *children_pid)
{
	close_extra_fds();
	free(children_pid);
}

void	quit_child(char **cmds, t_env **ms_env)
{
	rl_clear_history();
	free_env(ms_env);
	free_array(cmds);
	close_all_fds();
	exit(EXIT_FAILURE);
}