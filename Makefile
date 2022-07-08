# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ajaidi <ajaidi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/13 16:07:16 by ajaidi            #+#    #+#              #
#    Updated: 2022/07/08 18:19:35 by ajaidi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc
FLAGS = -Wall -Wextra -Werror
# -I
RL_INCLUDE = $(addprefix $(shell brew --prefix readline), /include)
# -L
RL_LIB = $(addprefix $(shell brew --prefix readline), /lib)
LIB = minishell.h

SRCS = minishell.c collector_linkedlist.c ast/ast_command.c ast/ast_conecters.c ast/ast.c ast/redir.c 	ast/display.c ast/ast_linkedlist.c ast/ast_structures_geters.c parser/token_conecters.c parser/token.c parser/token_string.c parser/token_quotes.c parser/parser_linkedlist.c parser/delete_quotes.c parser/token_utils.c syntax/syntax.c syntax/syntax_utils.c env/env.c env/env_geters.c history.c libft/ft_atoi.c libft/ft_itoa.c libft/ft_strlen.c 	libft/ft_strjoin.c libft/ft_split.c libft/ft_putstr_fd.c libft/ft_strcmp.c libft/ft_strncmp.c libft/ft_strdup.c builtins/echo.c builtins/cd.c builtins/env.c builtins/exit.c builtins/pwd.c builtins/export.c builtins/unset.c ex/ex.c ex/excommand.c ex/expander.c ex/transfer.c ex/signal.c

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