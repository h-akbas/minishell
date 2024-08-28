/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_split_args_utils2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 00:00:06 by hakbas            #+#    #+#             */
/*   Updated: 2024/08/29 00:11:21 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "../libft/libft.h"

void	toggle_quotes(char c, bool *in_quotes, char *quote_char)
{
	if (!*in_quotes && (c == '\'' || c == '"'))
	{
		*in_quotes = true;
		*quote_char = c;
	}
	else if (*in_quotes && c == *quote_char)
	{
		*in_quotes = false;
		*quote_char = '\0';
	}
}

void	ft_strclr(char *s)
{
	if (s == NULL)
		return ;
	while (*s)
		*s++ = '\0';
}

void	remove_quotes(char *cmd)
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
