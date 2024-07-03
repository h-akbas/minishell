/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_quoting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 21:00:57 by hakbas            #+#    #+#             */
/*   Updated: 2024/07/02 21:07:39 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <stdbool.h>

bool	quoting_error(char *str)
{
	char	open_quote;

	open_quote = 0;
	while (*str && !open_quote)
	{
		if (*str == '\'' || *str == '"')
			open_quote = *str;
		str++;
	}
	while (*str && open_quote)
	{
		if (*str && *str == open_quote)
			open_quote = 0;
		str++;
	}
	if (*str)
		return (quoting_error(str));
	else if (!open_quote)
		return (false);
	else
	{
		ft_putendl_fd("Unclosed quote!", 2);
		return (true);
	}
}
