/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 14:15:37 by hakbas            #+#    #+#             */
/*   Updated: 2024/07/05 14:18:45 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <stdbool.h>

bool	str_equal(const char *str1, const char *str2)
{
	size_t	size;

	if(!str1 || !str2)
		return (false);
	size = ft_strlen(str1);
	if (size != ft_strlen(str2))
		return (false);
	return (ft_strncmp(str1, str2, size) == 0);
}

void	move_one_forward(char *str)
{
	ft_memmove(str, str + 1, ft_strlen(str + 1) + 1);
}