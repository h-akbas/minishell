# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/26 15:51:42 by hakbas            #+#    #+#              #
#    Updated: 2024/06/26 16:54:31 by hakbas           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror
RM				=	rm -rf
NAME			=	minishell

LIBFT_DIR		=	./libft
LIBFT			=	$(LIBFT_DIR)/libft.a
