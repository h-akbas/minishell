/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:23:16 by hakbas            #+#    #+#             */
/*   Updated: 2024/07/03 11:42:21 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//includes only if necessary
# include <stdbool.h>
//defines
# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif
//typedefs
typedef struct s_env
{
	char			*key_pair;
	struct s_env	*next;
}				t_env;
//function prototypes

t_env	*get_env_node(char *name, t_env *ms_env);
char	*get_env_value(char *name, t_env *ms_env);
char	*get_name_only(char *key_pair);
char	*get_value_only(char *key_pair);
char	*create_keypair(char *name, char *value);
t_env	*init_env(char	**envp);
void	append_list(char *key_pair, t_env **lst);
void	init_main_signals(void);
char	*parse_prompt(t_env *ms_env);
bool	input_error(char *input, int *exit_stat, t_env *ms_env);


void	handle_expansions(char **input, t_env *ms_env, int exit_stat);
void	expand_vars(char **input, t_env *ms_env);
void	expand_exit_stat(char **input, int exit_stat);
bool	is_empty(char *str);
bool	is_quote(char c);
bool	has_pipe(char *str);
bool	is_name_delim(char c);

#endif
