/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 21:10:53 by hakbas            #+#    #+#             */
/*   Updated: 2024/08/31 18:33:43 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"
#include <stdbool.h>

static bool	redir_with_no_label(char *str);
static bool	empty_pipe(char *str);

bool	invalid_syntax(char *str)
{
	if (!str)
		return (true);
	if (str[0] == '|')
		return (put_syntax_error("|"));
	if (redir_with_no_label(str))
		return (true);
	if (empty_pipe(str))
		return (true);
	if (pipe_at_end(str))
		return (true);
	return (false);
}

static bool	redir_with_no_label(char *str)
{
	char	*redir_pos;
	char	next_redir;

	next_redir = get_next_redir(str);
	redir_pos = get_redir_pos(str, next_redir);
	if (!redir_pos)
		return (false);
	if (redir_pos[0] == '<' && redir_pos[1] == '<')
		redir_pos++;
	else if (redir_pos[0] == '>' && redir_pos[1] == '>')
		redir_pos++;
	redir_pos++;
	while (*redir_pos == ' ' || *redir_pos == '\t')
		redir_pos++;
	if (*redir_pos == '\0')
		return (put_syntax_error("newline"));
	if (invalid_token(*redir_pos))
		return (unexpected_token(redir_pos));
	return (redir_with_no_label(redir_pos));
}

static bool	empty_pipe(char *str)
{
	char	*next_pipe;

	next_pipe = get_next_pipe(str);
	if (!next_pipe)
		return (false);
	next_pipe++;
	while (*next_pipe == ' ' || *next_pipe == '\t')
		next_pipe++;
	if (*next_pipe == '|')
		return (put_syntax_error("|"));
	return (empty_pipe(next_pipe));
}

bool	pipe_at_end(char *str)
{
	char	*last_non_space;

	last_non_space = str + ft_strlen(str) - 1;
	while (last_non_space > str && ft_isspace(*last_non_space))
		last_non_space--;
	if (*last_non_space == '|')
	{
		put_syntax_error("|");
		return (true);
	}
	return (false);
}
