/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_split_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 15:23:39 by hakbas            #+#    #+#             */
/*   Updated: 2024/07/14 15:53:04 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"
#include <stdbool.h>

static bool	has_quotes(char *cmd);
static void	replace_spaces(char *cmd, char delim);
static void	remove_quotes(char *cmd);
static void	restore_spaces(char **args);

char	**split_args(char *cmd)
{
	char	**exec_args;

	if (!has_quotes(cmd))
		return (ft_split(cmd, ' '));
	replace_spaces(cmd, '"');
	replace_spaces(cmd, '\'');
	remove_quotes(cmd);
	exec_args = ft_split(cmd, ' ');
	if (!exec_args)
		return (NULL);
	restore_spaces(exec_args);
	return (exec_args);
}

static bool	has_quotes(char *cmd)
{
	while (*cmd)
	{
		if (is_quote(*cmd))
			return (true);
		cmd++;
	}
	return (false);
}

static void	replace_spaces(char *cmd, char delim)
{
	while (*cmd)
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
		if (!*cmd)
			break ;
	}
}

static void	remove_quotes(char *cmd)
{
	char	last_open_q;

	last_open_q = 0;
	while (*cmd)
	{
		if ((*cmd == '\'' || *cmd == '"') && !last_open_q)
		{
			last_open_q = *cmd;
			ft_memmove(cmd, cmd + 1, ft_strlen(cmd + 1) + 1);
		}
		else if (*cmd == last_open_q)
		{
			last_open_q = 0;
			ft_memmove(cmd, cmd + 1, ft_strlen(cmd + 1) + 1);
		}
		else
			cmd++;
	}
}

static void	restore_spaces(char **args)
{
	char	*cmd;

	while (args)
	{
		cmd = *args;
		{
			while (*cmd)
			{
				if (*cmd == -1)
					*cmd = ' ';
				cmd++;
			}
		}
		args++;
	}
}
