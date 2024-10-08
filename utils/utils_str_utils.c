/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 14:15:37 by hakbas            #+#    #+#             */
/*   Updated: 2024/09/03 16:40:10 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <stdbool.h>

bool	str_equal(const char *str1, const char *str2)
{
	if (!str1 || !str2)
		return (false);
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (false);
		str1++;
		str2++;
	}
	return (*str1 == '\0' && *str2 == '\0');
}

void	move_one_forward(char *str)
{
	if (str == NULL || *str == '\0')
		return ;
	ft_memmove(str, str + 1, ft_strlen(str + 1) + 1);
}

bool	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}
