/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:33:57 by hakbas            #+#    #+#             */
/*   Updated: 2024/07/19 06:16:38 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

char	*get_redir_pos(char *str, char redir_c)
{
	char	q;

	q = '\0';
	while (*str)
	{
		if (q == '\0' && (*str == '\'' || *str == '"'))
			q = *str;
		else if (*str == q)
			q = '\0';
		else if (*str == redir_c && q == '\0')
			return (str);
		str++;
	}
	return (NULL);
}

char	get_next_redir(char *str)
{
	char	q;

	q = '\0';
	while (*str)
	{
		if (q == '\0')
		{
			if (*str == '\'' || *str == '"')
				q = *str;
			else if (*str == '<' || *str == '>' || *str < 0)
				return (*str);
		}
		else if (*str == q)
			q = '\0';
		str++;
	}
	return ('\0');
}

void	redirect_fd(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
		print_perror_msg("dup2", "redirect fd");
	if (fd1 != STDIN_FILENO && fd1 != STDOUT_FILENO)
	{
		if (close(fd1) == -1)
			print_perror_msg("close", "redirect fd");
	}
}

void	redirect_io_fds(int fd_in, int fd_out)
{
	if (fd_in != STDIN_FILENO)
		redirect_fd(fd_in, STDIN_FILENO);
	if (fd_out != STDOUT_FILENO)
		redirect_fd(fd_out, STDOUT_FILENO);
}
