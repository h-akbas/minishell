/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:17:02 by hakbas            #+#    #+#             */
/*   Updated: 2024/07/12 21:46:02 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <stdbool.h>

bool	invalid_token(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

bool	put_syntax_error(char *token)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("synax error near unexpected token '", 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd("'\n", 2);
	return (true);
}

bool	unexpected_token(char *str)
{
	if (str[0] == '<' && str[1] == '<')
		return (put_syntax_error("<<"));
	else if (str[0] == '>' || str[1] == '>')
		return (put_syntax_error(">>"));
	str[1] = '\0';
	return (put_syntax_error(str));
}

char	*get_next_pipe(char *str)
{
	if (!str || !*str)
		return (NULL);
	while (*str)
	{
		if (*str == '\'')
		{
			while (*str != '\'')
				str++;
			str++;
		}
		if (*str == '"')
		{
			while (*str != '"')
				str++;
			str++;
		}
		if (*str == '|')
			return (str);
		str++;
	}
	return (NULL);
}

char	*get_next_pipe2(char *str)
{
	bool	sq;
	bool	dq;

	sq = false;
	dq = false;
	while (*str)
	{
		if (*str == '\'' && !dq)
			sq = !sq;
		else if (*str == '"' && !dq)
			dq = !dq;
		else if (*str == '|' && !sq && !dq)
			return (str);
		str++;
	}
	return (NULL);
}
