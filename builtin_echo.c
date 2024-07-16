/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 19:28:22 by hakbas            #+#    #+#             */
/*   Updated: 2024/07/16 22:34:55 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

static void	print_echo(char **str, int *index, bool new_line);

int	echo(char **args)
{
	int		i;
	int		j;
	bool	new_line;

	new_line = true;
	i = 1;
	while (args[i] && args[i][0] == '-')
	{
		if (args[i][1] == 'n')
		{
			j = 1;
			while (args[i][j] == 'n')
				j++;
			if (args[i][j] == '\0')
			{
				new_line = false;
				i++;
				continue ;
			}
		}
		break ;
	}
	print_echo(args, &i, new_line);
	return (EXIT_SUCCESS);
}

static void	print_echo(char **str, int *index, bool new_line)
{
	int	i;

	i = *index;
	while (str[i])
	{
		ft_putstr_fd(str[i], STDOUT_FILENO);
		if (str[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (new_line)
		ft_putstr_fd("\n", STDOUT_FILENO);
}
