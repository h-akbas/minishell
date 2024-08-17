/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 12:32:14 by hakbas            #+#    #+#             */
/*   Updated: 2024/08/17 15:10:29 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"
#include <stdlib.h>

t_env	*init_env(char	**envp)
{
	t_env	*list;
//	char	*home;
	int		i;

	list = NULL;
	i = 0;
	while (envp[i])
	{
		append_list(envp[i], &list);
		i++;
	}
	if (!get_env_node("OLDPWD", list))
		append_list("OLDPWD", &list);
/* 	home = ft_strjoin("__HOME=", get_env_value("HOME", list));
	if (!home)
		return (NULL);
	append_list(home, &list);
	free(home); */
	return (list);
}

void	append_list(char *key_pair, t_env **lst)
{
	t_env	*new_env;
	t_env	*tmp;

	new_env = (t_env *)malloc(sizeof(t_env));
	if (!new_env)
		return ;
	new_env->key_pair = ft_strdup(key_pair);
	if (new_env->key_pair == NULL)
	{
		free(new_env);
		return ;
	}
	new_env->next = NULL;
	if (!*lst)
	{
		*lst = new_env;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_env;
}
