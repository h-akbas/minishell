/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 12:32:14 by hakbas            #+#    #+#             */
/*   Updated: 2024/08/22 22:35:58 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"
#include <stdlib.h>
#include <unistd.h>

static t_env	*create_dummy_env(void);

t_env	*init_env(char	**envp)
{
	t_env	*list;
	int		i;

	list = NULL;
	if (envp == NULL || *envp == NULL)
		list = create_dummy_env();
	else
	{
		i = 0;
		while (envp[i])
		{
			append_list(envp[i], &list);
			i++;
		}
	}
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

static t_env	*create_dummy_env(void)
{
	t_env	*dummy_env;
	char	*cwd;

	dummy_env = NULL;
	append_list(create_keypair("PATH", "/usr/bin:/bin:/usr/local/bin"),
		&dummy_env);
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		append_list(create_keypair("PWD", cwd), &dummy_env);
		free (cwd);
	}
	append_list(create_keypair("SHLVL", "1"), &dummy_env);
	append_list(create_keypair("_", "/usr/bin/env"), &dummy_env);
	return (dummy_env);
}
