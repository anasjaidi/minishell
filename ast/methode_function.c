/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methode_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 03:37:19 by ajaidi            #+#    #+#             */
/*   Updated: 2022/06/23 20:43:37 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree  *get_wp(int type, t_tree *left, t_tree *right)
{
	t_wp	*node;
	
	node = ft_malloc(&g.adrs, sizeof(t_wp));
	node->type = type;
	node->left = left;
	node->right = right;
	return ((t_tree*)node);
}

t_tree  *get_redir(int type, t_tree *next, int fd, int mode, char *filename, int redtype)
{
	t_redir	*node;
	
	node = ft_malloc(&g.adrs, sizeof(t_redir));
	node->type = REDIR;
	node->next = next;
	if (redtype == DLESS)
		node->fd = herdoc(filename);
	else
		node->fd = STDIN_FILENO;
	node->mode = O_CREAT;
	node->filename = filename;
	return ((t_tree*)node);
}

t_tree  *get_cmdnode(t_cmd *next)
{
	t_cmd	*node;
	
	node = ft_malloc(&g.adrs, sizeof(t_cmd));
	node->type = CMD;
	node->next = NULL;
	return ((t_tree*)node);
}

t_tree  *get_sub(t_tree *next)
{
	t_sub	*node;
	
	node = ft_malloc(&g.adrs,sizeof(t_sub));
	node->type = SUB;
	node->next = next;
	return ((t_tree*)node);
}


int get_type(t_token *head)
{
	if (head->type == PIPE)
		return (T_PIPE);
	if (head->type == AND)
		return (T_AND);
	if (head->type == OR)
		return (T_OR);
	return (-1);
}

t_command  *get_nodelist(char *content)
{
	t_command	*node;
	
	node = ft_malloc(&g.adrs, sizeof(t_command));
	node->type = CMD;
	node->next = NULL;
	node->content = content;
	return (node);
}

int herdoc(char *del)
{
	int fd[2];
	char *line;
	
	pipe(fd);
	while (1)
	{
		line = readline("herdoc >");
		if (!ft_memcmp(del, line, ft_strlen(del)))
			break;
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
	}
	close(fd[1]);
	return fd[0];
}