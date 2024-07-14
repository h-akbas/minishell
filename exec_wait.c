/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_wait.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 18:38:11 by hakbas            #+#    #+#             */
/*   Updated: 2024/07/14 18:56:22 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"
#include <signal.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <unistd.h>

static int	handle_sigint(int status, bool is_last_child);

int	wait_for_child(int cpid, bool is_last_child)
{
	int	status;
	
	if (cpid == -1)
		return (EXIT_FAILURE);
	if (waitpid(cpid, &status, 0) == -1)
		print_perror_msg("waitpid", ft_itoa(cpid));
	if (WIFSIGNALED(status))
		return (handle_sigint(status, is_last_child));
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}

int	wait_for_children(int children_pid[1024])
{
	int		i;
	int		exit_stat;
	bool	is_last_child;

	i = 0;
	exit_stat = 0;
	while (children_pid[i] != 0)
	{
		is_last_child = children_pid[i + 1] == 0;
		exit_stat = wait_for_child(children_pid[i], is_last_child);
		i++;
	}
	clean_after_exec(children_pid);
	return (exit_stat);
}

static int	handle_sigint(int status, bool is_last_child)
{
	if (WTERMSIG(status) == SIGINT)
		ft_putstr_fd("\n", STDOUT_FILENO);
	if (WTERMSIG(status) == SIGQUIT && is_last_child)
		ft_putstr_fd("Quit\n", STDOUT_FILENO);
	return (128 + WTERMSIG(status));
}