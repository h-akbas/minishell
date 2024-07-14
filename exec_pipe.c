/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 19:07:45 by hakbas            #+#    #+#             */
/*   Updated: 2024/07/14 19:12:56 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdbool.h>
#include <unistd.h>

void	handle_pipe(int fd_out, char *cur_cmd, char **cmds)
{
	bool		is_first_cmd;
	bool		has_next_cmd;
	char		*last_cmd;
	static int	pipe_fds[2];
	
	last_cmd = cmds[arr_len(cmds) - 1];
	is_first_cmd = cur_cmd == cmds[0];
	has_next_cmd = cur_cmd != last_cmd;
	if (!is_first_cmd)
		redirect_fd(pipe_fds[IN], STDIN_FILENO);
	if (has_next_cmd)
	{
		if (pipe(pipe_fds) == -1)
			print_perror_msg("pipe", cur_cmd);
		redirect_fd(pipe_fds[OUT], STDOUT_FILENO);
	}
	else
		redirect_fd(fd_out, STDOUT_FILENO);
}