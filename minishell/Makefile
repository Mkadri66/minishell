# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: momillio <momillio@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/20 15:34:09 by momillio          #+#    #+#              #
#    Updated: 2024/09/29 16:05:19 by momillio         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRCS = main.c $(wildcard builtins/*.c) $(wildcard parsing/*.c) $(wildcard run/*.c)
OBJS = $(SRCS:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -Iincludes
LDFLAGS = -lreadline
LIBFT_PATH = ./libft/libft.a

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: _libft $(NAME)

$(NAME): $(OBJS) $(LIBFT_PATH)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_PATH) -o $(NAME) $(LDFLAGS)
	@echo "\033[1;32mCompilation succesfull !\033[0m"

clean:
	@make clean -s -C ./libft
	@rm -f $(OBJS)
	@echo "\033[1;31mClean succesfull ! \033[0m"

fclean: clean
	@make fclean -s -C ./libft
	@rm -f $(NAME)
	@echo "\033[1;31mFclean succesfull ! \033[0m"

re: fclean all

_libft:
	@make -s -C ./libft
	@echo "\033[1;32mLibft compiled !\033[0m"

.PHONY: all clean fclean re