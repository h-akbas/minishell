/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:33:57 by hakbas            #+#    #+#             */
/*   Updated: 2024/07/16 14:08:47 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	{
		perror("dup2");
		return ;
	}
	if (close(fd1) == -1)
	{
		perror("close");
		return ;
	}
}

void	redirect_io_fds(int fd_in, int fd_out)
{
	if (fd_in != STDIN_FILENO)
		redirect_fd(fd_in, STDIN_FILENO);
	if (fd_out != STDOUT_FILENO)
		redirect_fd(fd_out, STDOUT_FILENO);
}
