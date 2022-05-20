/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi < ajaidi@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:47:03 by ajaidi            #+#    #+#             */
/*   Updated: 2022/05/20 22:18:13 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <unistd.h>

# define VAR 0 //
# define DGREAT 1
# define DLESS 2
# define LESS 3
# define GREAT 4
# define WORD 5 //
# define WSPACE 6 // 
# define SQUOTE 7 //
# define DQUOTE 8 //
# define OPAR 9
# define WILD 10 // 
# define TILD 11 //
# define AND 12
# define OR 13
# define PIPE 14
# define CPAR 15 //

typedef struct s_token
{
	struct s_token	*prev;
	char			*str;
	int				type;
	struct s_token	*next;
}	t_token;

typedef struct s_tree
{
	char			*str;
	int				type;
	struct s_tree	**childs;
}	t_tree;

int		calc_size(char *start, char *end);
int		take_par(char *str, t_token **root);
int		take_word(char *str, t_token **root);
t_token	*new_node(char *str, int flag);
void	display_node(t_token *root);
void	append_in_end(t_token **root, char *str, int flag);
void	*add_item(char *start, char *end, int flag, t_token **root);
int		take_dquote(char *str, t_token **root);
int		take_colon(char *str, t_token **root);
int		check_flag(char *str, int q, t_token **root);
int		take_wp(char *str, t_token **root);
int		take_less_more(char *str, t_token **root);
int		take_var(char *str, t_token **root);
void	unclosed_quote(t_token **root);
int		check_char(char *str, t_token **root);
void	token(char *str, t_token **root);
int		take_qvar(char *str, t_token **root);
void	clr_lst(t_token **root, t_token *node);
int		take_space(char *str, t_token **root);
int		get_last(char *str);
int		invalid_token(t_token **root, char *str);
int		check_closed_dq(t_token **root, char	*str, int i, int last);
void	check_syntax(t_token **root);
int		check_begin(t_token *root);
void	syntax_error(t_token **root);
int		check_list(t_token *root);
int		check_red(t_token *root);
int		check_cpar(t_token *root);
int		check_wp(t_token *root);
t_token	*get_right(t_token *root);
t_token	*get_left(t_token *root);
void	check_bal_par(t_token **root);
#endif