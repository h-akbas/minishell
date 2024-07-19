/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ft_atoll.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 18:17:46 by hakbas            #+#    #+#             */
/*   Updated: 2024/07/19 17:25:56 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <stdbool.h>

static bool	ft_isspace(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

long long	ft_atoll(const char *str)
{
	long long	num;
	int			sign;

	num = 0;
	sign = 1;
	while (ft_isspace(*str) && !(*str == '-' || *str == '+'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = sign * -1;
		str++;
	}
	while (*str && ft_isdigit(*str))
	{
		num = (num * 10) + (*str - '0');
		str++;
	}
	return (num * sign);
}
