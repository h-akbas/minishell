/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:17:02 by hakbas            #+#    #+#             */
/*   Updated: 2024/07/19 17:25:56 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <stdbool.h>
#include <unistd.h>

bool	invalid_token(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

bool	put_syntax_error(char *token)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("synax error near unexpected token '", STDERR_FILENO);
	ft_putstr_fd(token, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
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
	bool	single_quote;
	bool	double_quote;

	single_quote = false;
	double_quote = false;
	while (*str)
	{
		if (*str == '\'' && !double_quote)
			single_quote = !single_quote;
		else if (*str == '"' && !double_quote)
			double_quote = !double_quote;
		else if (*str == '|' && !single_quote && !double_quote)
			return (str);
		str++;
	}
	return (NULL);
}
