/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 20:10:13 by hakbas            #+#    #+#             */
/*   Updated: 2024/07/14 20:21:11 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"
#include <stdlib.h>

static void	remove_from_env(char *varname, t_env **ms_env);
static void	ms_env_del_next_node(t_env **node);

int	unset(char **args, t_env **ms_env)
{
	char	*varname;
	int		exit_stat;

	args++;
	exit_stat = EXIT_SUCCESS;
	if (!*args)
		return (0);
	while (*args)
	{
		varname = *args;
		if (!valid_varname(varname))
		{
			print_varname_error("unset", varname);
			exit_stat = EXIT_FAILURE;
		}
		else
			remove_from_env(varname, ms_env);
		args++;
	}
	return (exit_stat);
}

static void	remove_from_env(char *varname, t_env **ms_env)
{
	t_env	*tmp;
	size_t	len;

	tmp = *ms_env;
	len = ft_strlen(varname);
	while (tmp && tmp->next)
	{
		if (ft_strncmp((tmp->next)->key_pair, varname, len) == 0)
		{
			if ((tmp->next)->key_pair[len] == '=')
				return (ms_env_del_next_node(&tmp));
		}
		tmp = tmp->next;
	}
}

static void	ms_env_del_next_node(t_env **node)
{
	t_env	*tmp;

	tmp = (*node)->next;
	(*node)->next = (*node)->next->next;
	free(tmp->key_pair);
	free(tmp);
}