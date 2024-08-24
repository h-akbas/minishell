/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_io.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:56:25 by hakbas            #+#    #+#             */
/*   Updated: 2024/08/24 15:50:36 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/fcntl.h>
#include <time.h>
#include <unistd.h>

static int	open_redirection_file(char *redir, int o_flags);
char		*extract_file_name(char *redir);

int	redirect_output(char *cmd)
{
	char	*redir_out;
	int		fd;
	int		o_flags;

	redir_out = get_redir_pos(cmd, '>');
	if (redir_out == NULL)
		return (0);
	if (redir_out && redir_out[1] == '<')
		o_flags = O_WRONLY | O_CREAT | O_APPEND;
	else
	 	o_flags = O_WRONLY | O_CREAT | O_TRUNC;
	fd = open_redirection_file(redir_out, o_flags);
	if (fd == -1)
		return (0);
	return (redirect_fd(fd, STDOUT_FILENO));
}

int	redirect_input(char *cmd)
{
	char	*redir_in;
	int		fd;

	redir_in = get_redir_pos(cmd, '<');
	if (redir_in == NULL)
		return (0);
	fd = open_redirection_file(redir_in, O_RDONLY);
	if (fd == -1)
		return (0);
	return (redirect_fd(fd, STDIN_FILENO));

}

static int	open_redirection_file(char *redir, int o_flags)
{
	char	*filename;
	int		fd;

	if (redir == NULL)
		return (-1);
	filename = get_label_name(redir);
	if (filename == NULL)
	{
		print_error_msg("get_label_name", "Failed to extract filename.");
		return (-1);
	}
	fd = open(filename, o_flags, 0644);
	if (fd == -1)
	{
		print_error_msg(filename, strerror(errno));
		free(filename);
		return (-1);
	}
	free(filename);
	return (fd);
}
