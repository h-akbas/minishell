/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_io.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:56:25 by hakbas            #+#    #+#             */
/*   Updated: 2024/07/12 23:05:46 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>

int	redirect_output(char *cmd)
{
	char	*redir_out;
	char	*f_name;
	int		fd;
	int		o_flags;

	if ((redir_out = get_redir_pos(cmd, '>')) == NULL)
		return (1);
	if (redir_out[1] == '>')
		o_flags = O_WRONLY | O_CREAT | O_APPEND;
	else
	 	o_flags = O_WRONLY | O_CREAT | O_TRUNC;
	f_name = get_label_name(redir_out);
	fd = open(f_name, o_flags, 0644);
	if (fd == 1)
	{
		print_perror_msg("open", f_name);
		free(f_name);
		return (0);
	}
	else
		redirect_fd(fd, STDOUT_FILENO);
	free(f_name);
	return (1);
}

int	redirect_input (char *cmd)
{
	char	*redir_in;
	char	*f_name;
	int		fd;

	if ((redir_in = get_redir_pos(cmd, '<')) == NULL)
		return (1);
	f_name = get_label_name(redir_in);
	fd = open(f_name, O_RDONLY, FD_CLOEXEC);
	if (fd == -1)
	{
		print_perror_msg("open", f_name);
		free(f_name);
		return (0);
	}
	else
		redirect_fd(fd, STDIN_FILENO);
	free(f_name);
	return (1);
}
