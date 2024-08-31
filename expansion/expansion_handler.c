/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:11:30 by hakbas            #+#    #+#             */
/*   Updated: 2024/08/31 18:29:53 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_expansions(char **input, t_env *ms_env, int exit_stat)
{
	expand_exit_stat(input, exit_stat);
	expand_vars(input, ms_env);
}
