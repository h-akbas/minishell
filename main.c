/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:16:35 by hakbas            #+#    #+#             */
/*   Updated: 2024/06/25 17:38:48 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	
	(void) argv;
	

	if (argc == 1)
	{
		//TODO: set main signals
		//TODO: init_data
		init_data(&data, envp);
		//TODO: init_shell
		//TODO: clean_exit
	}	
	else
	{
		printf("Argc isn't 1\n"); //remove this before evo
		return (EXIT_FAILURE);
	}
}