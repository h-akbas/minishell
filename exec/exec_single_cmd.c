/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 14:55:00 by hakbas            #+#    #+#             */
/*   Updated: 2024/07/19 17:26:20 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

static int	handle_redirs(char *cmd, int org_fds[2]);
static void	restore_org_fds(int org_fds[2]);
static int	exec_forked_extern(char **args, t_env *ms_env);

int	single_cmd(char	*cmd, t_env **ms_env)
{
	char	**args;
	int		stat;
	int		org_fds[2];

	if (!handle_redirs(cmd, &org_fds[0]))
	{
		restore_org_fds(org_fds);
		free(cmd);
		return (EXIT_FAILURE);
	}
	args = split_args(cmd);
	if (!args)
	{
		free(cmd);
		return (EXIT_FAILURE);
	}
	free(cmd);
	if (is_builtin(args[0]))
		stat = exec_builtin(args, ms_env);
	else
		stat = exec_forked_extern(args, *ms_env);
	free_array(args);
	restore_org_fds(org_fds);
	return (stat);
}

static int	handle_redirs(char *cmd, int org_fds[2])
{
	char	redir;

	org_fds[IN] = NO_REDIR;
	org_fds[OUT] = NO_REDIR;
	redir = get_next_redir(cmd);
	while (redir)
	{
		if (redir == '<' && !handle_input_redir(cmd, org_fds))
			return (0);
		if (redir == '>' && !handle_output_redir(cmd, org_fds))
			return (0);
		if (redir < 0)
		{
			save_org_fd_in(org_fds);
			redirect_heredoc(cmd, redir);
		}
		redir = get_next_redir(cmd);
	}
	return (1);
}

static void	restore_org_fds(int org_fds[2])
{
	if (org_fds[IN] != NO_REDIR)
		redirect_fd(org_fds[IN], STDIN_FILENO);
	if (org_fds[OUT] != NO_REDIR)
		redirect_fd(org_fds[OUT], STDOUT_FILENO);
}

static int	exec_forked_extern(char **args, t_env *ms_env)
{
	int		child_pid;
	char	*cmd;

	cmd = args[0];
	child_pid = fork();
	set_exec_signals(child_pid);
	if (child_pid == -1)
		print_perror_msg("fork", cmd);
	else if (child_pid == 0)
		exec_external(args, ms_env);
	else
		return (wait_for_child(child_pid, true));
	exit (EXIT_FAILURE);
}
