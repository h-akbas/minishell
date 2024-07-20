/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 19:32:12 by hakbas            #+#    #+#             */
/*   Updated: 2024/07/20 13:34:26 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

static bool	fits_in_long_long(char *str);
static void	check_args_error(char **args);

int	builtin_exit(char **args, t_env **ms_env)
{
	int	exit_stat;

	exit_stat = EXIT_SUCCESS;
	rl_clear_history();
	free_env(ms_env);
	ft_putendl_fd("exit", STDOUT_FILENO);
	check_args_error(args);
	close_all_fds();
	if (args[1])
		exit_stat = ft_atoll(args[1]);
	free_array(args);
	exit(exit_stat);
}

static bool	fits_in_long_long(char *str)
{
	long long	res;
	int			c;

	if (ft_strlen(str) > 20)
		return (false);
	if (ft_strncmp(str, "-9223372036854775808", 21))
		return (true);
	res = 0;
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (false);
		c = *str - '0';
		if (res > (LLONG_MAX - c) / 10)
			return (false);
		res = res * 10 + c;
		str++;
	}
	return (true);
}

static void	check_args_error(char **args)
{
	char	*exit_stat;

	if (!args || !args[1])
	{
		if (args)
			free_array(args);
		close_all_fds();
		exit(EXIT_SUCCESS);
	}
	exit_stat = args[1];
	if (!fits_in_long_long(exit_stat))
	{
		free_array(args);
		exit_with_error("exit", "numeric argument required", BUILTIN_MISUSE);
	}
	if (args[2] != NULL)
	{
		free_array(args);
		exit_with_error("exit", "too many arguments", EXIT_FAILURE);
	}
}
