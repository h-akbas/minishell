/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:01:06 by hakbas            #+#    #+#             */
/*   Updated: 2024/07/10 14:02:25 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>

bool	is_empty(char *str)
{
	if (!str)
		return (true);
	while (*str)
	{
		if (*str != ' ')
			return (false);
		str++;
	}
	return (true);
}

bool	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

bool	has_pipe(char *str)
{
	bool	sq;
	bool	dq;

	sq = false;
	dq = false;
	while (*str)
	{
		if (*str == '\'' && !dq)
			sq = !sq;
		else if (*str == '"' && !sq)
			dq = !dq;
		else if (*str == '|' && !dq && !sq)
			return (true);
		str++;
	}
	return (false);
}

bool	is_name_delim(char c)
{
	return (c == ' ' || c == '>' || c == '<' || c == '|' || c == '\t');
}
