/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_label.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 18:26:57 by hakbas            #+#    #+#             */
/*   Updated: 2024/07/12 19:59:34 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_name_end(char *name)
{
	int	i;

	i = 0;
	while(name[i] && !is_name_delim(name[i]))
	{
		
	}
}
