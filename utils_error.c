/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 14:20:58 by hakbas            #+#    #+#             */
/*   Updated: 2024/07/12 23:01:00 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <unistd.h>
#include "minishell.h"

void	print_error_msg(char *command, char *msg)
{
	ft_putstr_fd("minishell", STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

void	exit_error(char *cmd, char *msg, int err)
{
	print_error_msg(cmd, msg);
	close_all_fds();
	rl_clear_history();
	exit(err);
}

void	print_perror_msg(char *cmd, char *pmsg)
{
	ft_putstr_fd("minishell", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	perror(pmsg);
}

void	exit_perror(char *cmd, char *pmsg, int err)
{
	print_perror_msg(cmd, pmsg);
	close_all_fds();
	rl_clear_history();
	exit(err);
}

void	print_varname_error(char *cmd, char *varname)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": `", STDERR_FILENO);
	ft_putstr_fd(varname, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}
