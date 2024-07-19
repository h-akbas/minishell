/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_str_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:06:22 by hakbas            #+#    #+#             */
/*   Updated: 2024/07/19 17:25:56 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <stdnoreturn.h>

char	*get_name_only(char *key_pair)
{
	int	i;

	i = 0;
	while (key_pair[i] != '=' && key_pair[i])
		i++;
	return (ft_substr(key_pair, 0, i));
}

char	*get_value_only(char *key_pair)
{
	int	i;

	i = 0;
	while (key_pair[i] != '=' && key_pair[i])
		i++;
	if (!key_pair[i])
		return (NULL);
	return (&key_pair[i + 1]);
}

char	*create_keypair(char *name, char *value)
{
	char	*key_pair;
	int		size;
	int		i;

	size = ft_strlen(name) + ft_strlen(value) + 2;
	key_pair = (char *)malloc(size * sizeof(char));
	if (!key_pair)
		return (NULL);
	i = 0;
	while (*name)
		key_pair[i++] = *name++;
	key_pair[i++] = '=';
	while (*value)
		key_pair[i++] = *value++;
	key_pair[i] = '\0';
	return (key_pair);
}
