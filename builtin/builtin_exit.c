/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 19:32:12 by hakbas            #+#    #+#             */
/*   Updated: 2024/09/01 23:35:07 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"
#include <stdlib.h>
#include <limits.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <unistd.h>

/* static bool	fits_in_long_long(char *str);
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
} */
/* void	exit_shell(int status, char **args, t_env *ms_env)
{
	rl_clear_history();
	free_env(&ms_env);
	free_array(args);
	exit(status);
}

long long	parse_exit_status(char *arg)
{
	char		*endptr;
	long long	num;

	while (*arg && ft_isspace((unsigned char)*arg))
		arg++;
	ft_atoll(&)
}
 */

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
	if ((num == LLONG_MAX || num == LLONG_MIN) && is_valid_num(arg))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd("exit: ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		exit_shell(args, 255, ms_env);
	}
	endptr = arg;
	while (*endptr && (ft_isdigit(*endptr) || ft_isspace(*endptr)))
		endptr++;
	if (*endptr)
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
	if (!args[1])
		exit_shell(args, 0, ms_env);
	if (!is_valid_num(args[1]))
		parse_exit_status(args, args[1], ms_env);
	else
	{
		if (args[2])
		{
			ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
		exit_status = parse_exit_status(args, args[1], ms_env);
		exit_shell(args, (int)(exit_status & 0xFF), ms_env);
	}
	return (EXIT_SUCCESS);
}
