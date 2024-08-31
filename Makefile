# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/26 15:51:42 by hakbas            #+#    #+#              #
#    Updated: 2024/08/31 19:35:21 by hakbas           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				= gcc
CFLAGS			= -Wall -Wextra -Werror -g #-fsanitize=address
LDFLAGS			= -lreadline -L$(LIBFT_DIR) -lft
RM				= rm -rf
NAME			= minishell

OBJ_DIR			= obj
OBJS			= $(SRCS:%.c=$(OBJ_DIR)/%.o)
SRCS			= builtin_cd.c builtin_echo.c builtin_env.c builtin_exit.c \
				builtin_export.c builtin_pwd.c builtin_unset.c \
				builtin_utils.c env_free.c env_init.c env_str_utils.c \
				env_utils.c exec_builtin.c exec_external.c exec_get_path.c \
				exec_mult_cmd_utils.c exec_multiple_cmd.c exec_pipe.c \
				exec_single_cmd.c exec_single_cmd_utils.c exec_split_args.c \
				exec_wait.c expand_exit_stat.c expand_vars.c \
				expand_vars_utils.c expansion_handler.c heredoc_handler.c \
				input_error.c main.c parse_prompt.c split_cmds.c \
				redirect_heredoc.c redirect_io.c redirect_utils.c \
				syntax_check.c syntax_check_utils.c utils_arr_len.c \
				utils_error.c utils_fd.c utils_free_array.c utils_ft_atoll.c \
				utils_label.c utils_quoting.c utils_signals.c \
				utils_str_check.c utils_str_utils.c init_minishell.c shlvl.c \
				exec_split_args_utils.c exec_split_args_utils2.c \
				heredoc_handler_utils.c utils_merge_sort.c

LIBFT_DIR		= ./libft
LIBFT			= $(LIBFT_DIR)/libft.a
VPATH			= builtin env exec expansion main redir utils

all: $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

clean:
	$(RM) $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

leak: all
	valgrind -s --suppressions=./readline.supp --leak-check=full \
	--show-leak-kinds=all --track-fds=all --trace-children=yes ./$(NAME)

sanitize: CFLAGS += -fsanitize=address
sanitize: re
