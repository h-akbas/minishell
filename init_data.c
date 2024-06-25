/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:40:59 by hakbas            #+#    #+#             */
/*   Updated: 2024/06/25 18:53:35 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "minishell.h"
#include <stdbool.h>
#include "debug.h"

void	init_data(t_data *data, char **envp)
{
	int	i;

	errno = 0;
	data->in_main_process = true;
	data->last_status = EXIT_SUCCESS;
	data->temp_files = NULL;
	data->parsing_error = NULL;
	i = 0;
	while (i < MAX_ALLOC)
		data->allocated_ptrs[i++] = NULL;
	print_table(envp);
	//data->env = init_env(envp, data); //TODO
	//increment_shell_level(data); //TODO
}