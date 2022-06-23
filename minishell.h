/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:47:03 by ajaidi            #+#    #+#             */
/*   Updated: 2022/06/23 21:26:56 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <unistd.h>
#include <fcntl.h>
#include <string.h>

# define VAR 0 // ...................
# define DGREAT 1
# define DLESS 2
# define LESS 3
# define GREAT 4
# define WORD 5 // .....................
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
// node_tree
# define SUB 16 //
# define CMD 17 //
# define REDIR 18 //
# define T_PIPE 19 //
# define T_AND 20 //
# define T_OR 21 //
extern const char *types[];
#define null NULL



typedef struct s_token
{
	struct s_token	*prev;
	char			*str;
	int				type;
	struct s_token	*next;
}	t_token;

typedef struct	s_command {
	int				type;
	char			*content;
	struct s_command *next;
}	t_command;

typedef	struct s_tree
{
	int				type;
}	t_tree;

typedef struct s_cmd {
	int type;
	struct s_command	*next;
}	t_cmd;

typedef struct s_sub {
	int type;
	struct s_tree	*next;
}	t_sub;


typedef	struct	s_wp
{
	int				type;
	struct s_tree	*left;	
	struct s_tree	*right;	
}	t_wp;

typedef	struct	s_redir
{
	int				type;
	char			*filename;
	int				fd;
	int				mode;
	struct s_tree	*next;	
}	t_redir;

typedef struct s_collector
{
	void				*adr;
	struct s_collector	*next;
}	t_collector;
typedef	struct s_global
{
	t_collector	*adrs;
}	t_global;
t_global	g;

t_collector	*new_node_adr(void *adr);
t_collector	**append_adr(t_collector **root, void *adr);
void		*ft_malloc(t_collector **root, size_t size);
void		ft_collect(t_collector **root, t_collector *node);

t_tree  *get_wp(int type, t_tree *left, t_tree *right);
t_tree  *get_redir(int type, t_tree *next, int fd, int mode, char *filename, int redtype);
int		calc_size(char *start, char *end);
int		take_par(char *str, t_token **root);
t_tree  *get_cmd(t_command *next);
t_tree  *get_sub(t_tree *next);
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
int 	get_type(t_token *head);
void	unclosed_quote(t_token **root);
void	delete_quotes(t_token **root);
int		check_char(char *str, t_token **root);
t_tree *get_command(t_token **head);
void	display_nodetree(t_command *root);
t_tree *get_block(t_token **head);
t_tree	*token(char *str, t_token **root);
t_tree *get_cmdlist(t_token **head);
t_tree *get_full(t_token **head);
int		take_qvar(char *str, t_token **root);
void	clr_lst(t_token **root, t_token *node);
int		take_space(char *str, t_token **root);
int		get_last(char *str);
t_tree	*get_pipe(t_token **head);
int		invalid_token(t_token **root, char *str);
int		check_closed_dq(t_token **root, char	*str, int i, int last);
void	check_syntax(t_token **root);
int		check_begin(t_token *root);
void	syntax_error(t_token **root);
int		check_list(t_token *root);
int		check_red(t_token *root);
void display_tree(t_tree *tree, int in);
int		check_cpar(t_token *root);
int		check_wp(t_token *root);
t_token	*get_right(t_token *root);
t_token	*get_left(t_token *root);
void	check_bal_par(t_token **root);
t_tree  *get_cmdnode(t_cmd *next);
t_command	*new_nodecommand(char *str, int flag);
void	append_in_cmdend(t_command **root, char *str, int type);
void display_tree(t_tree *tree, int in);
int	ft_strlen(char *s);
int	ft_memcmp(void *s1,void *s2, int n);
int herdoc(char *del);
#endif