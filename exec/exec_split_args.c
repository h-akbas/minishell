/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_split_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 15:23:39 by hakbas            #+#    #+#             */
/*   Updated: 2024/08/29 00:11:41 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"
#include <stdbool.h>

static bool	has_quotes(char *cmd);
static void	replace_spaces(char *cmd, char delim);
static void	restore_spaces(char **args);
static void	remove_quotes_preserved(char **args);

char	**split_args(char *cmd)
{
	char	**exec_args;

	if (!has_quotes(cmd))
		return (ft_split(cmd, ' '));
	replace_spaces(cmd, '"');
	replace_spaces(cmd, '\'');
	exec_args = ft_split_preserve_quotes(cmd, ' ');
	if (!exec_args)
		return (NULL);
	remove_quotes_preserved(exec_args);
	restore_spaces(exec_args);
	return (exec_args);
}

static bool	has_quotes(char *cmd)
{
	if (!cmd)
		return (false);
	while (*cmd && cmd)
	{
		if (*cmd == '\'' || *cmd == '"')
			return (true);
		cmd++;
	}
	return (false);
}

static void	replace_spaces(char *cmd, char delim)
{
	while (*cmd && *cmd != delim)
		cmd++;
	if (*cmd)
		cmd++;
	while (*cmd && *cmd != delim)
	{
		if (*cmd == ' ')
			*cmd = -1;
		cmd++;
	}
	if (*cmd)
		cmd++;
	if (*cmd)
		replace_spaces(cmd, delim);
}

static void	remove_quotes_preserved(char **args)
{
	while (*args)
	{
		if (ft_strncmp(*args, "\"\"", 4) == 0
			|| ft_strncmp(*args, "''", 2) == 0)
		{
			ft_strclr(*args);
		}
		else
		{
			remove_quotes(*args);
		}
		args++;
	}
}

static void	restore_spaces(char **args)
{
	char	*cmd;

	while (*args)
	{
		cmd = *args;
		while (*cmd)
		{
			if (*cmd == -1)
				*cmd = ' ';
			cmd++;
		}
		args++;
	}
	return ;
}
