# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ajaidi <ajaidi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/13 16:07:16 by ajaidi            #+#    #+#              #
#    Updated: 2022/04/13 16:30:22 by ajaidi           ###   ########.fr        #
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

SRCS = minishell.c

OBJ = $(SRCS:.c=.o)
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -L $(RL_LIB) -lreadline -o $(NAME)

%.o:%.c minishell.h
	$(CC) $(FLAGS) -c $< -o $@ -I $(RL_INCLUDE)
	

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -f $(NAME)

re:	fclean all