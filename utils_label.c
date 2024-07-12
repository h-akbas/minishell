/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_label.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 18:26:57 by hakbas            #+#    #+#             */
/*   Updated: 2024/07/12 20:13:36 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

static int	get_name_end(char *name)
{
	int	i;

	i = 0;
	while (name[i] && !is_name_delim(name[i]))
	{
		if (name[i] == '\'')
		{
			move_one_forward(&name[i]);
			while (name[i] && name[i] != '\'')
				i++;
			move_one_forward(&name[i]);
		}
		else if (name[i] == '"')
		{
			move_one_forward(&name[i]);
			while(name[i] && name[i] != '"')
				i++;
			move_one_forward(&name[i]);
		}
		else if (name[i] && !is_name_delim(name[i]))
			i++;
	}
	return (i);
}

char	*get_label_name(char *redir_str)
{
	int	start;
	int	end;
	char	*name;
	char	*remaining;

	start = 0;
	move_one_forward(redir_str);
	if (redir_str[start] == '>')
		move_one_forward(&redir_str[start]);
	while (redir_str[start] == ' ' || redir_str[start] == '\t')
		start++;
	end = get_name_end(&redir_str[start]);
	name = ft_substr(&redir_str[start], 0, end);
	remaining = &redir_str[start + end];
	ft_memmove(redir_str, remaining, ft_strlen(remaining) + 2);
	return (name);
}
