/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:16:35 by hakbas            #+#    #+#             */
/*   Updated: 2024/06/26 17:37:37 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "minishell.h"

static void	check_tty_fds(void);
static void	check_argc(int argc);

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;

	(void) argv;
	(void) envp;
	check_tty_fds();
	check_argc(argc);
	env = (t_env *)malloc(sizeof(t_env));
	if (!env)
		return (EXIT_FAILURE);
/* 	set_signal_handlers();
	init_data(env, envp);
	minishell_loop(env);
	clean_exit(env, EXIT_SUCCESS); */
}

static void	check_tty_fds(void)
{
	if (!isatty(0) && !isatty(1))
	{
		ft_putendl_fd("minishell: error: invalid file descriptor", 2);
		exit(EXIT_FAILURE);
	}
}

static void	check_argc(int argc)
{
	if (argc > 1)
	{
		ft_putendl_fd("minishell: error: too many arguments", 2);
		exit(EXIT_FAILURE);
	}
}
