/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methode_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasjaidi <anasjaidi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 03:37:19 by ajaidi            #+#    #+#             */
/*   Updated: 2022/05/25 17:24:50 by anasjaidi        ###   ########.fr       */
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
	return ((t_tree*)node);
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
	return ((t_tree*)node);
}

t_tree  *get_cmd(t_command *next)
{
	t_cmd	*node;
	
	node = malloc(sizeof(t_cmd));
	node->type = CMD;
	node->next = next;
	return ((t_tree*)node);
}

t_tree  *get_sub(t_tree *next)
{
	t_sub	*node;
	
	node = malloc(sizeof(t_sub));
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
}