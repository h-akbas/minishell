/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:16:35 by hakbas            #+#    #+#             */
/*   Updated: 2024/07/31 22:02:33 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "../libft/libft.h"
#include "../minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	*ms_env;

	(void)argv;
	if (argc > 1 || !isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
	{
		ft_putendl_fd("Usage: ./minishell", STDERR_FILENO);
		close_all_fds();
		return (EXIT_FAILURE);
	}
	ms_env = init_env(envp);
	if (!ms_env)
	{
		ft_putendl_fd("Error: Failed to create environment variables!", \
			STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	increment_shlvl(ms_env);
	return (init_minishell(ms_env));
}
