/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:23:16 by hakbas            #+#    #+#             */
/*   Updated: 2024/06/25 18:47:39 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//includes only if necessary
# include <stdbool.h>
# include "libft/libft.h"
//defines

//typedef
typedef enum	e_alloc
{
	CHECK,
	SHELL,
	PROMPT,
	MAX_ALLOC
}				t_alloc;

typedef struct	s_data
{
	t_list		*env;
	bool		in_main_process;
	t_list		*allocated_ptrs[MAX_ALLOC];
	char		*home;
	int			last_status;
	t_list		*temp_files;
	char		*parsing_error;
}				t_data;

//function prototypes
void		init_data(t_data *data, char **envp);

#endif