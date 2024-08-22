/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 20:10:13 by hakbas            #+#    #+#             */
/*   Updated: 2024/08/22 16:23:31 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"
#include <stdbool.h>
#include <stdlib.h>

static void	remove_from_env(char *varname, t_env **ms_env);
static bool	should_remove_node(char *key_pair, char *varname, size_t len);
static void	remove_first_node(t_env **ms_env);
static void	remove_next_node(t_env *current);

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
	t_env	*current;
	size_t	len;

	len = ft_strlen(varname);
	if (should_remove_node((*ms_env)->key_pair, varname, len))
		remove_first_node(ms_env);
	current = *ms_env;
	while (current && current->next)
	{
		if (should_remove_node(current->next->key_pair, varname, len))
		{
			remove_next_node(current);
			return ;
		}
		current = current->next;
	}
}

static bool	should_remove_node(char *key_pair, char *varname, size_t len)
{
	return (ft_strncmp(key_pair, varname, len) == 0
		&& key_pair[len] == '=');
}

static void	remove_first_node(t_env **ms_env)
{
	t_env	*tmp;

	tmp = *ms_env;
	*ms_env = tmp->next;
	free(tmp->key_pair);
	free(tmp);
}

static void	remove_next_node(t_env *current)
{
	t_env	*tmp;

	tmp = current->next;
	current->next = tmp->next;
	free(tmp->key_pair);
	free(tmp);
}
