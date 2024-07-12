/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:53:57 by hakbas            #+#    #+#             */
/*   Updated: 2024/07/12 22:39:41 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

static void	replace_pipes(char *str, char delim);
static void	restore_pipes(char **exec_cmds);

char	**split_cmds(char *input)
{
	char **cmds;

	if (!input)
		return (NULL);
	replace_pipes(input, '"');
	replace_pipes(input, '\'');
	cmds = ft_split(input, '|');
	if (!cmds)
		return (NULL);
	restore_pipes(cmds);
	return (cmds);
}

static void	replace_pipes(char *str, char delim)
{
	while (*str)
	{
		while (*str && *str != delim)
			str++;
		if (*str)
			str++;
		while (*str && *str != delim)
		{
			if (*str == '|')
				*str = -1;
			str++;
		}
		if (*str)
			str++;
	}
}

static void	restore_pipes(char **exec_cmds)
{
	char	*str;

	while (*exec_cmds)
	{
		str = *exec_cmds;
		while (*str)
		{
			if (*str == -1)
				*str = '|';
			str++;
		}
		exec_cmds++;
	}
}
