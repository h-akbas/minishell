/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:36:30 by hakbas            #+#    #+#             */
/*   Updated: 2024/07/12 22:59:46 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <errno.h>

void	close_extra_fds(void)
{
	int	fd;
	int	max_fd;

	max_fd = 1024;
	fd = STDERR_FILENO + 1;
	while (fd < max_fd)
	{
		if (close(fd) == -1 && errno != EBADF)
		{
			perror("close");
			return ;
		}
		fd++;
	}
}

void	close_all_fds(void)
{
	close_extra_fds();
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}
