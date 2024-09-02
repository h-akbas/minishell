/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:23:16 by hakbas            #+#    #+#             */
/*   Updated: 2024/09/02 20:29:26 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <stddef.h>

# define PATH_MAX 4096

# define IN 0
# define OUT 1
# define NO_REDIR -1
# define INTERRUPT 128
# define CMD_NOT_FOUND 127
# define NOT_EXECUTABLE 126
# define CMD_NOT_FOUND_MSG	"command not found"
# define NOT_EXECUTABLE_MSG "is a directory"
# define DEFAULT_PATH "/usr/bin:/bin:/usr/local/bin"

//typedefs
typedef struct s_env
{
	char			*key_pair;
	struct s_env	*next;
	int				last_cmd;
}				t_env;

typedef struct s_cd_params
{
	char	*path;
	bool	home_subdir;
	bool	is_dir_flag;
}				t_cd_params;
//function prototypes

int			init_minishell(t_env *ms_env);
void		increment_shlvl(t_env *ms_env);
t_env		*get_env_node(char *name, t_env *ms_env);
char		*get_env_value(char *name, t_env *ms_env);
char		*get_name_only(char *key_pair);
char		*get_value_only(char *key_pair);
char		*create_keypair(char *name, char *value);
t_env		*init_env(char **envp);
void		append_list(char *key_pair, t_env **lst);
void		update_env_var(char *name, char *value, t_env *ms_env);
char		**ms_env_to_envp(t_env *ms_env);
void		free_env(t_env **ms_env);
void		free_array(char **arr);
void		close_extra_fds(void);
void		close_all_fds(void);

void		set_main_signals(void);
void		set_exec_signals(int cpid);
void		set_heredoc_signals(int cpid);
char		*parse_prompt(t_env *ms_env);

bool		quoting_error(char *str);
bool		input_error(char *input, int *exit_stat, t_env *ms_env);
bool		invalid_syntax(char *str);
bool		invalid_token(char c);
bool		unexpected_token(char *str);
bool		put_syntax_error(char *token);
char		*get_next_pipe(char *str);

void		handle_expansions(char **input, t_env *ms_env, int exit_stat);
void		expand_vars(char **input, t_env *ms_env);
void		expand_exit_stat(char **input, int exit_stat);
bool		valid_varname(char *str);
bool		is_varname(char c);
bool		ft_isspace(char c);
bool		pipe_at_end(char *str);

bool		invalid_syntax(char *str);
bool		is_empty(char *str);
bool		has_pipe(char *str);
bool		is_name_delim(char c);

bool		str_equal(const char *str1, const char *str2);
size_t		arr_len(char **arr);

int			print_error_msg(char *command, char *msg);
void		exit_with_error(char *cmd, char *msg, int err);
void		print_perror_msg(char *cmd, char *pmsg);
void		exit_perror(char *cmd, char *pmsg, int err);
void		print_varname_error(char *cmd, char *varname);

char		*get_redir_pos(char *str, char redir_c);
char		get_next_redir(char *str);
int			redirect_fd(int fd1, int fd2);
int			redirect_input(char *cmd);
int			redirect_output(char *cmd);
void		redirect_heredoc(char *cmd, int hd_no);
char		*tmp_filename(int hd_no);

int			handle_heredoc(char *input, int *exit_stat, t_env *ms_env);
char		*get_label_name(char *redir_str);
void		move_one_forward(char *str);

void		close_all_fds(void);

char		**split_cmds(char *input);

char		**split_args(char *cmd);

bool		is_builtin(char *cmd);

int			single_cmd(char *cmd, t_env **ms_env);
int			multiple_cmd(char **cmds, t_env **ms_env);
int			handle_input_redir(char *cmd, int org_fds[2]);
int			handle_output_redir(char *cmd, int org_fds[2]);
void		save_org_fd_in(int org_fds[2]);
void		save_org_fd_out(int org_fds[2]);
int			exec_forked_builtin(char **args, t_env **ms_env);
int			exec_builtin(char **args, t_env **ms_env);
int			exec_external(char **args, t_env *ms_env);
char		*get_path(char *cmd, t_env *ms_env);
int			*init_children_pid(char **cmds);
void		clean_after_exec(int *children_pid);
void		quit_child(char **cmds, t_env **ms_env);
int			wait_for_child(int cpid, bool is_last_child);
int			wait_for_children(int children_pid[1024]);
void		handle_pipe(int fd_out, char *cur_cmd, char **cmds);

void		update_wd(t_env *ms_env);
void		declare_statement(t_env *env);
int			cd(char **args, t_env *ms_env);
int			echo(char **args);
int			env(t_env *ms_env);
int			builtin_exit(char **args, t_env **ms_env);
int			builtin_export(char **args, t_env **ms_env);
int			pwd(void);
int			unset(char **args, t_env **ms_env);
char		**ft_split_preserve_quotes(char *cmd, char delimiter);
void		toggle_quotes(char c, bool *in_quotes, char *quote_char);
void		ft_strclr(char *s);
void		remove_quotes(char *cmd);
void		process_heredoc_line(char **line_read, int *tmp_fd,
				t_env *ms_env, int *exit_stat);
int			open_temp_file(char *filename, char *delim, t_env **ms_env);
void		merge_sort(t_env **head_ref);
int			is_valid_fd(int fd);

#endif
