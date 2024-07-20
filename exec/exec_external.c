/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 16:58:53 by hakbas            #+#    #+#             */
/*   Updated: 2024/07/20 14:18:48 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>

static bool	is_folder(char *cmd);
static void	handle_execve_err(char **args, char *path, char **envp);
static void	external_exit(char **args, t_env *ms_env, int stat);

int	exec_external(char **args, t_env *ms_env)
{
	char	*path;
	char	*cmd;
	char	**envp;

	cmd = args[0];
	if (is_empty(cmd))
		external_exit(args, ms_env, EXIT_SUCCESS);
	if (is_folder(cmd))
		external_exit(args, ms_env, NOT_EXECUTABLE);
	path = get_path(cmd, ms_env);
	if (!path && get_env_value("PATH", ms_env) != NULL)
		external_exit(args, ms_env, CMD_NOT_FOUND);
	else if (path == NULL)
		path = ft_strdup(cmd);
	rl_clear_history();
	close_extra_fds();
	envp = ms_env_to_envp(ms_env);
	free_env(&ms_env);
	if (execve(path, args, envp) == -1)
		handle_execve_err(args, path, envp);
	exit(EXIT_SUCCESS);
}

static bool	is_folder(char *cmd)
{
	struct stat	statbuf;

	if (stat(cmd, &statbuf) != 0)
		return (false);
	if (S_ISDIR(statbuf.st_mode))
	{
		if (*cmd == '.')
			cmd++;
		if (*cmd == '.')
			cmd++;
		if (*cmd == '/')
			return (true);
	}
	return (false);
}

static void	handle_execve_err(char **args, char *path, char **envp)
{
	int	err;

	err = EXIT_FAILURE;
	print_perror_msg("execve", args[0]);
	if (access(path, F_OK))
		err = CMD_NOT_FOUND;
	else if (access(path, X_OK))
		err = NOT_EXECUTABLE;
	free_array(args);
	free_array(envp);
	free(path);
	exit(err);
}

static void	external_exit(char **args, t_env *ms_env, int stat)
{
	if (stat == NOT_EXECUTABLE)
		print_error_msg(args[0], NOT_EXECUTABLE_MSG);
	if (stat == CMD_NOT_FOUND)
		print_error_msg(args[0], CMD_NOT_FOUND_MSG);
	rl_clear_history();
	free_env(&ms_env);
	free_array(args);
	close_all_fds();
	exit(stat);
}
