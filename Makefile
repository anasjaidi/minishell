# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ajaidi <ajaidi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/13 16:07:16 by ajaidi            #+#    #+#              #
#    Updated: 2022/06/25 18:26:40 by ajaidi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc
#FLAGS = -Wall -Wextra -Werror

# -I
RL_INCLUDE = $(addprefix $(shell brew --prefix readline), /include)
# -L
RL_LIB = $(addprefix $(shell brew --prefix readline), /lib)
LIB = minishell.h

SRCS = minishell.c linkedlist.c parser/token.c parser/token2.c parser/token3.c parser/token_utils.c syntax/syntax.c syntax/syntax_utils.c ast/ast.c ast/methode_function.c ast/ast_utils.c collector_linkedlist.c env.c ft_split.c ast/redir.c parser/delete_quotes.c

OBJ = $(SRCS:%.c=%.o)
all: $(NAME) clean

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -L $(RL_LIB) -lreadline -o $(NAME)

%.o: %.c minishell.h
	$(CC) $(FLAGS) -c $< -o $@ -I $(RL_INCLUDE) -I.
	

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -f $(NAME)

re:	fclean all