/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_cmd_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 16:08:39 by hakbas            #+#    #+#             */
/*   Updated: 2024/07/19 17:26:20 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../minishell.h"

int	handle_input_redir(char *cmd, int org_fds[2])
{
	save_org_fd_in(org_fds);
	if (!redirect_input(cmd))
	{
		redirect_fd(org_fds[IN], STDIN_FILENO);
		return (0);
	}
	return (1);
}

int	handle_output_redir(char *cmd, int org_fds[2])
{
	save_org_fd_out(org_fds);
	if (!redirect_output(cmd))
	{
		redirect_fd(org_fds[OUT], STDOUT_FILENO);
		return (0);
	}
	return (1);
}

void	save_org_fd_in(int org_fds[2])
{
	if (org_fds[IN] == NO_REDIR)
		org_fds[IN] = dup(STDIN_FILENO);
}

void	save_org_fd_out(int org_fds[2])
{
	if (org_fds[OUT] == NO_REDIR)
		org_fds[OUT] = dup(STDOUT_FILENO);
}
