/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi < ajaidi@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:47:03 by ajaidi            #+#    #+#             */
/*   Updated: 2022/04/20 15:10:43 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>

#define VAR 0
#define DGREAT 1
#define DLESS 2
#define LESS 3
#define GREAT 4
#define WORD 5
#define PIPE 6
#define TILD 7
#define WSPACE 8
#define SQUOTE 9
#define DQUOTE 10
#define AND 11
#define OR 12
#define WILD 13


typedef struct	s_token
{
    struct  s_token	*prev;
    char			*str;
    int				type;
    struct  s_token	*next;
}				t_token;
int	take_word(char *str, t_token **root);
t_token *new_node(char  *str, int flag);
void	append_in_end(t_token **root, char  *str, int flag);
void	display_node(t_token *root);
void	*add_item(char *start, char *end, int flag, t_token **root);
int		take_dquote(char *str, t_token **root);
int		take_colon(char *str, t_token **root);
int		check_flag(char *str, int q);
int 	take_wp(char *str, t_token **root);
int		take_less_more(char *str, t_token **root);
int 	take_var(char *str, t_token **root);
void	unclosed_quote(t_token **root);
int 	check_char(char *str, t_token **root);
void	token(char *str, t_token **root);
int	take_qvar(char *str, t_token **root);
void	clr_lst(t_token **root, t_token *node);
int	take_space(char *str, t_token **root);
#endif