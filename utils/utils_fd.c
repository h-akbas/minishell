/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:36:30 by hakbas            #+#    #+#             */
/*   Updated: 2024/09/01 23:39:58 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include "../minishell.h"

void	close_extra_fds(void)
{
	int			max_fd;
	int			fd;
	struct stat	statbuf;

	fd = STDERR_FILENO + 1;
	max_fd = 1024;
	while (fd < max_fd)
	{
		if (fstat(fd, &statbuf) == 0)
		{
			if (close(fd) == -1)
				print_error_msg("close", "extra fds");
		}
		fd++;
	}
	return ;
}

void	close_all_fds(void)
{
	close_extra_fds();
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}

int	is_valid_fd(int fd)
{
	struct stat	buf;

	if (fstat(fd, &buf) == 0)
		return (1);
	else
		return (0);
}
