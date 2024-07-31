/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 22:00:38 by hakbas            #+#    #+#             */
/*   Updated: 2024/07/31 22:01:52 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"
#include <unistd.h>

static void	put_shlvl_error(t_env *ms_env);

void	increment_shlvl(t_env *ms_env)
{
	int		shlvl;
	char	*current_value;
	char	*new_value;

	current_value = get_env_value("SHLVL", ms_env);
	if (!current_value)
		return ;
	else
	{
		shlvl = ft_atoi(current_value) + 1;
		if (shlvl > 999)
		{
			put_shlvl_error(ms_env);
			shlvl = 1;
		}
		else if (shlvl < 0)
			shlvl = 0;
	}
	new_value = ft_itoa(shlvl);
	if (!new_value)
		return ;
	update_env_var("SHLVL", new_value, ms_env);
	free(new_value);
}

static void	put_shlvl_error(t_env *ms_env)
{
	ft_putstr_fd("minishell: warning: shell level (", STDERR_FILENO);
	ft_putnbr_fd(ft_atoi(get_env_value("SHLVL", ms_env)) + 1, STDERR_FILENO);
	ft_putendl_fd(") too high, resetting to 1", STDERR_FILENO);
}
