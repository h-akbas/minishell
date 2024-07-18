/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:33:57 by hakbas            #+#    #+#             */
/*   Updated: 2024/07/18 14:31:15 by hakbas           ###   ########.fr       */
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
	printf("Before: fd1: %d, fd2: %d \n", fd1, fd2);
	if (dup2(fd1, fd2) == -1)
		perror("dup2 58:");
	if (close(fd1) == -1)
		perror("close 60:");
	printf("After: fd1: %d, fd2: %d \n", fd1, fd2);
}

void	redirect_io_fds(int fd_in, int fd_out)
{
	if (fd_in != STDIN_FILENO)
		redirect_fd(fd_in, STDIN_FILENO);
	if (fd_out != STDOUT_FILENO)
		redirect_fd(fd_out, STDOUT_FILENO);
}
