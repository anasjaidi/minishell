/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:47:03 by ajaidi            #+#    #+#             */
/*   Updated: 2022/07/06 17:20:50 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
extern const char *types[];
extern const char *types_token[];
# include <stdio.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <dirent.h>
# include <limits.h>
# include <stdbool.h>
# include <errno.h>

# define VAR 0
# define DGREAT 1
# define DLESS 2
# define LESS 3
# define GREAT 4
# define WORD 5
# define WSPACE 6
# define SQUOTE 7
# define DQUOTE 8
# define OPAR 9
# define WILD 10
# define TILD 11
# define AND 12
# define OR 13
# define PIPE 14
# define CPAR 15
// node_tree
# define SUB 16
# define CMD 17
# define REDIR 18
# define T_PIPE 19
# define T_AND 20
# define T_OR 21

typedef	struct s_token
{
	struct s_token	*prev;
	char			*str;
	int				type;
	struct s_token	*next;
}	t_token;

typedef	struct	s_command {
	int				type;
	char			*content;
	struct s_command *next;
}	t_command;

typedef	struct s_tree
{
	int				type;
}	t_tree;

typedef	struct s_cmd {
	int					type;
	struct s_command	*next;
}	t_cmd;

typedef	struct s_sub {
	int				type;
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
	int				src;
	int				dst;
	int				mode;
	struct s_tree	*next;	
}	t_redir;

typedef struct s_collector
{
	void				*adr;
	int					key;
	struct s_collector	*next;
}	t_collector;

typedef	struct s_env
{
	char			*key;
	char			*value;
	struct	s_env	*next;
}	t_env;

typedef	struct s_global
{
	t_collector	*adrs;
	t_env		*env;
	int			status;
}	t_global;

t_global	g;
void	ft_putstr_fd(char *str, int fd);
t_collector	*new_node_adr(void *adr, int key);
t_tree		*get_rdr(t_token **head , t_tree *n);
void		display_env(t_env *root);
t_collector	**append_adr(t_collector **root, void *adr, int key);
void		*ft_malloc(t_collector **root, size_t size, int key);
void		ft_collect(t_collector **root, t_collector *node, int key);
void the_exit(int status);
t_tree		*get_wp(int type, t_tree *left, t_tree *right);
t_tree		*get_redir(t_tree *next, char *filename, int redtype);
int			calc_size(char *start, char *end);
int			take_par(char *str, t_token **root);
t_tree		*get_cmd(t_command *next);
void	ft_env(int fd);
t_tree		*get_sub(t_tree *next);
int	ft_atoi(const char *str);
int			take_word(char *str, t_token **root);
t_token		*new_node(char *str, int flag);
void		display_node(t_token *root);
void		append_in_end(t_token **root, char *str, int flag);
void		*add_item(char *start, char *end, int flag, t_token **root);
int			take_dquote(char *str, t_token **root);
int			take_colon(char *str, t_token **root);
int			check_flag(char *str, int q, t_token **root);
int			take_wp(char *str, t_token **root);
int			take_less_more(char *str, t_token **root);
int			take_var(char *str, t_token **root);
int			get_type(t_token *head);
void		unclosed_quote(t_token **root);
void		delete_quotes(t_token **root);
int			check_char(char *str, t_token **root);
t_tree		*get_command(t_token **head);
void		display_nodetree(t_command *root);
t_tree		*get_block(t_token **head);
t_tree		*token(char *str, t_token **root);
t_tree		*get_cmdlist(t_token **head);
t_tree		*get_full(t_token **head);
int			take_qvar(char *str, t_token **root);
void		clr_lst(t_token **root, t_token *node);
int			take_space(char *str, t_token **root);
int			get_last(char *str);
t_tree		*get_pipe(t_token **head);
int			invalid_token(t_token **root, char *str);
int			check_closed_dq(t_token **root, char	*str, int i, int last);
int			check_syntax(t_token **root);
int			check_begin(t_token *root);
void		syntax_error(t_token **root);
int			check_list(t_token *root);
int			check_red(t_token *root);
void		display_tree(t_tree *tree, int in);
int			check_cpar(t_token *root);
int			check_wp(t_token *root);
t_token		*get_right(t_token *root);
t_token		*get_left(t_token *root);
int			check_bal_par(t_token **root);
t_tree		*get_cmdnode(t_cmd *next);
t_command	*new_nodecommand(char *str, int flag);
void		append_in_cmdend(t_command **root, char *str, int type);
void		display_tree(t_tree *tree, int in);
int			ft_strlen(char *s);
int			herdoc(char *del);
char		**ft_split(char const *s, char c);
void		get_env(char **env);
char	*get_env_value(char *str);
t_env	*get_env_node(char *str);
void	append_in_end_env(t_env **root, char *key, char *value);
char	*ft_strjoin(char  *s1, char  *s2);
char	**transfer(t_command *root);
void ft_cd(char **argv);
int	new_line(char *str);
int	ft_echo(char **argv);
void	cast_node(t_tree *root);
void	delete_node_commnd(t_command **root, t_command *deleted);
void	get_wild_value(t_command **root, t_command *node);
void 	check_token_type(t_command **root, t_command *node);
void	expend_tokens(t_command **root);
void	ex_cmd(t_cmd *cmd);
int	ft_exit(char **argv);
int	ft_pwd(int fd);
int exit_parse(char *str);
char **ft_split_exp(char *line);
void	display_exports();
void	ft_export(char **argv);
void	delete_env(t_env **root, t_env *deleted);
void	ft_unset(char **argv);
int	cmdlstsize(t_command *root);
void	ft_putstr_fd(char *str, int fd);
int	ft_strcmp(char *s1, char *s2);
#endif