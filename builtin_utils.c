/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 16:00:29 by hakbas            #+#    #+#             */
/*   Updated: 2024/07/14 16:06:19 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdbool.h>

bool	is_builtin(char *cmd)
{
	if (!cmd)
		return (false);
	return (
		str_equal(cmd, "echo")
		|| str_equal(cmd, "cd")
		|| str_equal(cmd, "pwd")
		|| str_equal(cmd, "export")
		|| str_equal(cmd, "unset")
		|| str_equal(cmd, "env")
		|| str_equal(cmd, "exit")
	);
}
