/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:07:51 by hakbas            #+#    #+#             */
/*   Updated: 2024/08/17 13:51:02 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

static char	*get_heredoc_pos(char *str);
static char	*temp_filename(int hd_no);
static void	read_heredoc(int *exit_stat, t_env *ms_env, char *delim, int hd_no);
static int	exec_heredoc(char *delim, int hd_no, int *exit_stat, t_env *ms_env);

int	handle_heredoc(char *input, int *exit_stat, t_env *ms_env)
{
	static int	heredoc_number;
	char		*heredoc_pos;
	char		*delim;

	heredoc_number = -1;
	heredoc_pos = get_heredoc_pos(input);
	if (!heredoc_pos)
		return (1);
	heredoc_number--;
	*heredoc_pos = heredoc_number;
	heredoc_pos++;
	delim = get_label_name(heredoc_pos);
	if (!exec_heredoc(delim, heredoc_number, exit_stat, ms_env))
	{
		free(delim);
		return (0);
	}
	free(delim);
	return (handle_heredoc(input, exit_stat, ms_env));
}

static char	*get_heredoc_pos(char *str)
{
	while (*str && str[1])
	{
		if (*str == '\'')
		{
			str++;
			while (*str != '\'')
				str++;
		}
		if (*str == '"')
		{
			str++;
			while (*str != '"')
				str++;
		}
		if (*str == '<' && str[1] == '<')
			return (str);
		str++;
	}
	return (NULL);
}

static char	*temp_filename(int hd_no)
{
	char	filename[30];
	char	*num_str;

	ft_bzero(filename, 30);
	num_str = ft_itoa(hd_no);
	ft_strlcat(filename, "/tmp/heredoc", 30);
	ft_strlcat(filename, num_str, 30);
	free(num_str);
	return (ft_strdup(filename));
}

static void	read_heredoc(int *exit_stat, t_env *ms_env, char *delim, int hd_no)
{
	char	*line_read;
	char	*filename;
	int		tmp_fd;

	filename = temp_filename(hd_no);
	tmp_fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	free(filename);
	line_read = readline("> ");
	while (line_read && !str_equal(line_read, delim))
	{
		expand_exit_stat(&line_read, *exit_stat);
		expand_vars(&line_read, ms_env);
		ft_putendl_fd(line_read, tmp_fd);
		free(line_read);
		line_read = readline("> ");
	}
	if (!line_read)
		print_error_msg("Warning: HEREDOC delimited by EOF. Wanted", delim);
	free(line_read);
	close(tmp_fd);
	free(delim);
	free_env(&ms_env);
	rl_clear_history();
	exit(0);
}

static int	exec_heredoc(char *delim, int hd_no, int *exit_stat, t_env *ms_env)
{
	int	child_pid;

	child_pid = fork();
	set_heredoc_signals(child_pid);
	if (child_pid == -1)
		print_error_msg("fork - heredoc_prompt", delim);
	else if (child_pid == 0)
		read_heredoc(exit_stat, ms_env, delim, hd_no);
	else
	{
		*exit_stat = wait_for_child(child_pid, true);
		set_main_signals();
		if (*exit_stat != 0)
			return (0);
	}
	return (1);
}
