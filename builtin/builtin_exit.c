/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 19:32:12 by hakbas            #+#    #+#             */
/*   Updated: 2024/08/29 01:26:50 by hakbas           ###   ########.fr       */
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
static void	handle_empty_string(char **args, char *trimmed_exit_stat);
static char	*trim_and_remove_quotes(char *arg);

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
	if (!ft_strncmp(str, "-9223372036854775808", 21))
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

static void	handle_empty_string(char **args, char *trimmed_exit_stat)
{
	if (ft_strlen(trimmed_exit_stat) == 0)
	{
		free(trimmed_exit_stat);
		free_array(args);
		exit_with_error("exit", "numeric argument required", 255);
	}
}

static char	*trim_and_remove_quotes(char *arg)
{
	char	*trimmed;
	char	*temp;

	trimmed = ft_strtrim(arg, " \t\n\r");
	if (trimmed[0] == '"' && trimmed[ft_strlen(trimmed) - 1] == '"')
	{
		temp = trimmed;
		trimmed = ft_strtrim(trimmed, "\"");
		free(temp);
	}
	return (trimmed);
}

static void	check_args_error(char **args)
{
	char	*trimmed_exit_stat;

	if (!args || !args[1])
	{
		if (args)
			free_array(args);
		close_all_fds();
		exit(EXIT_SUCCESS);
	}
	trimmed_exit_stat = trim_and_remove_quotes(args[1]);
	handle_empty_string(args, trimmed_exit_stat);
	free(args[1]);
	args[1] = trimmed_exit_stat;
	if (!fits_in_long_long(args[1]))
	{
		free_array(args);
		exit_with_error("exit", "numeric argument required", 255);
	}
	if (args[2] != NULL)
	{
		free_array(args);
		exit_with_error("exit", "too many arguments", EXIT_FAILURE);
	}
}
