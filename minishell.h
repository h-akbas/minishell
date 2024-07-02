/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:23:16 by hakbas            #+#    #+#             */
/*   Updated: 2024/07/02 12:30:15 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//includes only if necessary

//defines

//typedefs
typedef struct s_env
{
	char			*key_pair;
	struct s_env	*next;
}				t_env;
//function prototypes


#endif
