/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:23:16 by hakbas            #+#    #+#             */
/*   Updated: 2024/07/14 15:15:39 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//includes only if necessary
# include <stdbool.h>
# include <stddef.h>
//defines
# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

# define IN 0
# define OUT 1
# define NO_REDIR -1
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
void	update_env_var(char *name, char *value, t_env *ms_env);
void	free_env(t_env	**ms_env);

void	set_main_signals(void);
void	set_exec_signals(int cpid);
void	set_heredoc_signals(int cpid);
char	*parse_prompt(t_env *ms_env);

bool	quoting_error(char *str);
bool	input_error(char *input, int *exit_stat, t_env *ms_env);
bool	invalid_syntax(char *str);
bool	invalid_token(char c);
bool	unexpected_token(char *str);
bool	put_syntax_error(char *token);
char	*get_next_pipe(char *str);

void	handle_expansions(char **input, t_env *ms_env, int exit_stat);
void	expand_vars(char **input, t_env *ms_env);
void	expand_exit_stat(char **input, int exit_stat);
bool	valid_varname(char *str);
bool	is_varname(char c);

bool	invalid_syntax(char *str);
bool	is_empty(char *str);
bool	is_quote(char c);
bool	has_pipe(char *str);
bool	is_name_delim(char c);

bool	str_equal(const char *str1, const char *str2);
void	move_one_forward(char *str);
size_t	arr_len(char **arr);

void	print_error_msg(char *command, char *msg);
void	exit_error(char *cmd, char *msg, int err);
void	print_perror_msg(char *cmd, char *pmsg);
void	exit_perror(char *cmd, char *pmsg, int err);
void	print_varname_error(char *cmd, char *varname);


char	*get_redir_pos(char *str, char redir_c);
char	get_next_redir(char *str);
void	redirect_fd(int fd1, int fd2);

int		handle_heredoc(char *input, int *exit_stat, t_env *ms_env);
char	*get_label_name(char *redir_str);
void	move_one_forward(char *str);

void	close_all_fds(void);

char	**split_cmds(char *input);

#endif
