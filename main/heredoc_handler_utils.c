/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:58:49 by hakbas            #+#    #+#             */
/*   Updated: 2024/08/29 15:15:01 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdlib.h>
#include <sys/fcntl.h>
#include <stdio.h>
#include <readline/readline.h>
#include "../libft/libft.h"

int	open_temp_file(char *filename, char *delim, t_env **ms_env)
{
	int	tmp_fd;

	tmp_fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (tmp_fd == -1)
	{
		print_perror_msg("open", "heredoc tmp file");
		free(delim);
		free_env(ms_env);
		rl_clear_history();
		exit(1);
	}
	return (tmp_fd);
}

void	process_heredoc_line(char **line_read, int *tmp_fd,
				t_env *ms_env, int *exit_stat)
{
	expand_exit_stat(line_read, *exit_stat);
	expand_vars(line_read, ms_env);
	ft_putendl_fd(*line_read, *tmp_fd);
	free(*line_read);
}
