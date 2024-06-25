/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:16:35 by hakbas            #+#    #+#             */
/*   Updated: 2024/06/25 17:23:05 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void) argv;
	(void) envp;

	if (argc == 1)
	{
		//TODO
		printf("Argc is 1.\n");
	}	
	else
	{
		printf("Argc isn't 1\n");
		return (EXIT_FAILURE);
	}
}