/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:53:25 by hakbas            #+#    #+#             */
/*   Updated: 2024/08/31 19:53:58 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <stdbool.h>

bool	is_varname(char c)
{
	return (ft_isalnum(c) || c == '_');
}

bool	valid_varname(char *str)
{
	if (!str || !*str)
		return (false);
	if (ft_isdigit(*str) || *str == '=')
		return (false);
	while (*str)
	{
		if (!is_varname(*str))
			return (false);
		str++;
	}
	return (true);
}
