/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 14:20:58 by hakbas            #+#    #+#             */
/*   Updated: 2024/07/05 14:43:14 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <readline/history.h>

void	print_error_msg(char *command, char *msg)
{
	ft_putstr_fd("minishell", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
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
	ft_putstr_fd("minishell", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
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
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(varname, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}