/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:36:30 by hakbas            #+#    #+#             */
/*   Updated: 2024/07/20 16:44:09 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <errno.h>
#include "../minishell.h"

void	close_extra_fds(void)
{
	int			max_fd;
	int			fd;
	struct stat	statbuf;

	fd = STDERR_FILENO + 1;
	max_fd = 1024;
	while (fd <= max_fd)
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
