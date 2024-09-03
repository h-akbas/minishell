/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:07:14 by hakbas            #+#    #+#             */
/*   Updated: 2024/09/03 17:02:27 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"
#include <stdlib.h>

char	*get_env_value(char *name, t_env *ms_env)
{
	t_env	*tmp;

	tmp = get_env_node(name, ms_env);
	if (!tmp)
		return (NULL);
	return (get_value_only(tmp->key_pair));
}

t_env	*get_env_node(char *name, t_env *ms_env)
{
	t_env	*tmp;
	size_t	size;

	if (!name || !ms_env)
		return (NULL);
	tmp = ms_env;
	size = ft_strlen(name);
	while (tmp)
	{
		if (!ft_strncmp(name, tmp->key_pair, size))
		{
			if (tmp->key_pair[size] == '=' || tmp->key_pair[size] == '\0')
				return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	update_env_var(char *name, char *value, t_env *ms_env)
{
	t_env	*tmp;
	char	*new_kp;

	if (!name || !value)
		return ;
	tmp = get_env_node(name, ms_env);
	new_kp = create_keypair(name, value);
	if (!new_kp)
		return ;
	if (!tmp)
	{
		append_list(new_kp, &ms_env);
		free(new_kp);
		return ;
	}
	free(tmp->key_pair);
	tmp->key_pair = new_kp;
}

size_t	get_env_size(t_env *ms_env)
{
	size_t	size;
	t_env	*tmp;

	size = 0;
	tmp = ms_env;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	return (size);
}

char	**ms_env_to_envp(t_env *ms_env)
{
	char	**envp;
	t_env	*tmp;
	size_t	i;

	envp = malloc((get_env_size(ms_env) + 1) * sizeof(char *));
	if (!envp)
		return (NULL);
	tmp = ms_env;
	i = 0;
	while (tmp)
	{
		envp[i] = ft_strdup(tmp->key_pair);
		if (!envp[i])
		{
			while (i > 0)
				free(envp[--i]);
			free(envp);
			return (NULL);
		}
		i++;
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}
