/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_quoting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 21:00:57 by hakbas            #+#    #+#             */
/*   Updated: 2024/08/29 01:55:38 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <stdbool.h>
#include <unistd.h>

bool	quoting_error(char *str)
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
		str++;
	}
	if (dq || sq)
	{
		ft_putendl_fd("Syntax error: unexpected end of file", STDERR_FILENO);
		return (true);
	}
	return (false);
}
