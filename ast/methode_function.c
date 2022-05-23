/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methode_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi < ajaidi@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 03:37:19 by ajaidi            #+#    #+#             */
/*   Updated: 2022/05/23 21:01:17 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

t_tree  *get_wp(int type, t_tree *left, t_tree *right)
{
	t_wp	*node;
	
	node = malloc(sizeof(t_wp));
	node->type = type;
	node->left = left;
	node->right = right;
	return ((*t_tree)node);
}

t_tree  *get_redir(int type, t_tree *next, int fd, int mode, char *filename)
{
	t_redir	*node;
	
	node = malloc(sizeof(t_redir));
	node->type = REDIR;
	node->next = next;
	node->fd = fd;
	node->mode = mode;
	node->filename = filename;
	return ((*t_tree)node);
}

t_tree  *get_cmd(t_comand *next)
{
	t_cmd	*node;
	
	node = malloc(sizeof(t_cmd));
	node->type = CMD;
	node->next = next;
	return ((*t_tree)node);
}

t_tree  *get_sub(t_tree *next)
{
	t_sub	*node;
	
	node = malloc(sizeof(t_sub));
	node->type = SUB;
	node->next = next;
	return ((*t_tree)node);
}
