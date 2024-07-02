/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:01:06 by hakbas            #+#    #+#             */
/*   Updated: 2024/07/02 14:09:33 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdbool.h>
#include <stdlib.h>

bool	input_error(char *input, int *exit_stat, t_env *ms_env)
{
	int	ret;

	ret = false;
	if (is_empty(input))
		ret = true;
	else if (quoting_error(input))
		ret = true;
	else if (syntax_error(input))
	{
		*exit_stat = 2;
		ret = true;
	}
	else if (!handle_heredoc(input, exit_stat, ms_env))
		ret = true;
	if (ret == true)
		free(input);
	return (ret);

}
