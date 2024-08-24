/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_io.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:56:25 by hakbas            #+#    #+#             */
/*   Updated: 2024/08/23 18:46:51 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int	redirect_output(char *cmd)
{
	char	*redir_out;
	char	*file_name;
	int		fd;
	int		o_flags;

	redir_out = get_redir_pos(cmd, '>');
	if (redir_out[1] == '>')
		o_flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		o_flags = O_WRONLY | O_CREAT | O_TRUNC;
	file_name = get_label_name(redir_out);
	fd = open(file_name, o_flags, 0644);
	if (fd == -1)
	{
		print_perror_msg("open", file_name);
		free(file_name);
		return (0);
	}
	else
		redirect_fd(fd, STDOUT_FILENO);
	free(file_name);
	return (1);
}

int	redirect_input(char *cmd)
{
	char	*redir_in;
	char	*file_name;
	int		fd;

	redir_in = get_redir_pos(cmd, '<');
	file_name = get_label_name(redir_in);
	fd = open(file_name, O_RDONLY, FD_CLOEXEC);
	if (fd == -1)
	{
		print_perror_msg("open", file_name);
		free(file_name);
		return (0);
	}
	else
		redirect_fd(fd, STDIN_FILENO);
	free(file_name);
	return (1);
}
