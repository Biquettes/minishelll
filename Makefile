# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lterrail <lterrail@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/16 13:56:16 by lterrail          #+#    #+#              #
#    Updated: 2018/11/23 20:23:36 by lterrail         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

SRC	=	main.c						\
		exit.c						\
		parse_cmd.c					\
		path_maker.c				\
		unset_set_env.c				\
		exec_cmd.c					\

OBJ		= $(addprefix ./obj/,$(SRC:.c=.o))

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g3

LIBFTA	= ./libft/libft.a
LIBINCL = -I./libft/includes
LIBLINK	= -L./libft -lft

all: obj $(LIBFTA) $(NAME)

obj:
	mkdir -p ./obj/

./obj/%.o:./srcs/%.c
	$(CC) $(CFLAGS) $(LIBINCL) -Iincludes -o $@ -c $<

$(LIBFTA):
	make -C ./libft

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LIBLINK)

clean:
	rm -rf ./obj/
	make -C ./libft clean

fclean: clean
	rm -rf $(NAME)
	make -C ./libft fclean

re: fclean all

.PHONY: all clean fclean re
