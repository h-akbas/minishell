/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 19:32:12 by hakbas            #+#    #+#             */
/*   Updated: 2024/09/02 01:47:42 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"
#include <stdlib.h>
#include <limits.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <unistd.h>

long long	ft_atoll(const char *str)
{
	long long	result;
	int			sign;
	long long	prev_result;

	result = 0;
	sign = 1;
	while (*str && ft_isspace((unsigned char)*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str && ft_isdigit((unsigned char)*str))
	{
		prev_result = result;
		result = result * 10 + (*str++ - '0');
		if (sign == 1 && result < prev_result)
			return (LLONG_MAX);
		if (sign == -1 && (-result) > (-prev_result))
			return (LLONG_MIN);
	}
	return (result * sign);
}

int	is_valid_num(const char *str)
{
	int	has_digit;

	has_digit = 0;
	while (*str && ft_isspace((unsigned char)*str))
		str++;
	if (*str == '-' || *str == '+')
		str++;
	while (*str && ft_isdigit((unsigned char)*str))
	{
		has_digit = 1;
		str++;
	}
	while (*str && ft_isspace((unsigned char)*str))
		str++;
	if (has_digit && *str == '\0')
		return (1);
	return (0);
}

void	exit_shell(char **args, int status, t_env **ms_env)
{
	free_array(args);
	rl_clear_history();
	close_all_fds();
	free_env(ms_env);
	exit(status);
}

long long	parse_exit_status(char **args, char *arg, t_env **ms_env)
{
	long long	num;
	char		*endptr;

	num = ft_atoll(arg);
	endptr = arg;
	while (*endptr && ft_isspace((unsigned char)*endptr))
		endptr++;
	if (*endptr == '-' || *endptr == '+')
		endptr++;
	while (*endptr && ft_isdigit((unsigned char)*endptr))
		endptr++;
	if (*endptr || ((num == LLONG_MAX || num == LLONG_MIN)
			&& is_valid_num(arg)))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd("exit: ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		exit_shell(args, 255, ms_env);
	}
	return (num);
}

int	builtin_exit(char **args, t_env **ms_env)
{
	long long	exit_status;

	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (!args[1] || (!args[2] && (str_equal(args[1], "-9223372036854775808")
				|| str_equal(args[1], "9223372036854775807"))))
		exit_shell(args, 0, ms_env);
	exit_status = parse_exit_status(args, args[1], ms_env);
	if (args[2])
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	exit_shell(args, (int)(exit_status & 0xFF), ms_env);
	return (EXIT_SUCCESS);
}
