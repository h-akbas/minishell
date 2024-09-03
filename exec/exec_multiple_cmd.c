/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multiple_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 18:10:07 by hakbas            #+#    #+#             */
/*   Updated: 2024/09/03 17:57:42 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void	save_org_fds(int org_fds[2]);
static void	handle_redirects(char *cmd, char **cmds, t_env **ms_env);
static void	exec_forked_cmd(char *cmd, char **cmds, t_env **ms_env);
static void	restore_org_fds(int org_fds[2]);

int	multiple_cmd(char **cmds, t_env **ms_env)
{
	int	org_fds[2];
	int	*children_pid;
	int	i;

	save_org_fds(org_fds);
	children_pid = init_children_pid(cmds);
	i = 0;
	while (cmds[i])
	{
		handle_pipe(org_fds[OUT], cmds[i], cmds);
		children_pid[i] = fork();
		set_exec_signals(children_pid[i]);
		if (children_pid[i] == -1)
			print_perror_msg("fork", cmds[i]);
		else if (children_pid[i] == 0)
		{
			free(children_pid);
			handle_redirects(cmds[i], cmds, ms_env);
			exec_forked_cmd(cmds[i], cmds, ms_env);
		}
		i++;
	}
	restore_org_fds(org_fds);
	return (wait_for_children(children_pid));
}

static void	save_org_fds(int org_fds[2])
{
	org_fds[0] = dup(STDIN_FILENO);
	if (org_fds[0] == -1)
		perror("dup stdin");
	org_fds[1] = dup(STDOUT_FILENO);
	if (org_fds[1] == -1)
		perror("dup stdout");
}

static void	handle_redirects(char *cmd, char **cmds, t_env **ms_env)
{
	char	redir;

	redir = get_next_redir(cmd);
	while (redir)
	{
		if (redir == '<' && !redirect_input(cmd))
			quit_child(cmds, ms_env);
		if (redir == '>' && !redirect_output(cmd))
			quit_child(cmds, ms_env);
		if (redir < 0)
			redirect_heredoc(cmd, redir);
		redir = get_next_redir(cmd);
	}
}

static void	exec_forked_cmd(char *cmd, char **cmds, t_env **ms_env)
{
	char	**args;

	close_extra_fds();
	args = split_args(cmd);
	free_array(cmds);
	if (is_builtin(args[0]))
		exec_forked_builtin(args, ms_env);
	else
		exec_external(args, *ms_env);
}

static void	restore_org_fds(int org_fds[2])
{
	if (org_fds[IN] != -1 && org_fds[IN] != STDIN_FILENO)
		redirect_fd(org_fds[IN], STDIN_FILENO);
	if (org_fds[OUT] != -1 && org_fds[OUT] != STDOUT_FILENO)
		redirect_fd(org_fds[OUT], STDOUT_FILENO);
}
