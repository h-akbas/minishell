/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:07:14 by hakbas            #+#    #+#             */
/*   Updated: 2024/07/02 18:27:14 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"
#include <stdlib.h>

char	*get_env_value(char *name, t_env *ms_env)
{
	t_env	*tmp;

	tmp = get_env_node(name, ms_env);
	if (!tmp)
		return (NULL);
	return(get_value_only(tmp->key_pair));
}

t_env	*get_env_node(char *name, t_env *ms_env)
{
	t_env	*tmp;
	size_t	size;

	if (!name || !ms_env)
		return (NULL);
	tmp = ms_env;
	size = ft_strlen(name);
	while(tmp)
	{
		if (!ft_strncmp(name, tmp->key_pair, size))
		{
			if (tmp->key_pair[size] == '=')
				return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

