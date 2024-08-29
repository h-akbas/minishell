/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:33:57 by hakbas            #+#    #+#             */
/*   Updated: 2024/08/29 15:01:26 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>
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
	while (*str)
	{
		if (*str == '\'')
		{
			str++;
			while (*str && *str != '\'')
				str++;
			if (!*str)
				return (0);
		}
		if (*str == '"')
		{
			str++;
			while (*str && *str != '"')
				str++;
			if (!*str)
				return (0);
		}
		if (*str == '<' || *str == '>' || *str == -1)
			return (*str);
		str++;
	}
	return (0);
}

int	redirect_fd(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
	{
		print_error_msg("dup2", strerror(errno));
		close(fd1);
		return (0);
	}
	close(fd1);
	return (1);
}
