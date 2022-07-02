/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 21:26:50 by ajaidi            #+#    #+#             */
/*   Updated: 2022/07/02 22:34:25 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cast_node(t_tree *root)
{
	if (root->type == SUB)
		ex_sub((t_sub *)root);
	if (root->type == CMD)
		ex_cmd((t_cmd *)root);
	if (root->type == REDIR)
		ex_redir((t_sub *)root);
	if (root->type == T_PIPE)
		ex_pipe((t_wp *)root);
	if (root->type == T_AND)
		ex_and_or((t_wp *)root);
}

void	delete_node_commnd(t_command **root, t_command *deleted)
{
	t_command	*tmp;

	if (deleted == *root)
		*root = deleted->next;
	else if (!deleted->next)
	{
		t_command *last;
		last = *root;
		while (last->next->next)
			last = last->next;
		last->next = NULL;
	}
	else
	{
		t_command *deletedprev;
		deletedprev = *root;
		while (deletedprev->next != deleted)
			deletedprev = deletedprev->next;
		deletedprev->next = deleted->next;
	}
}

void	get_wild_value(t_command **root, t_command *node)
{
	DIR *dir = opendir(".");
	struct dirent	*item;
	t_command *head = NULL;
	
	item = raeddir(dir);
	while (item)
	{
		append_in_cmdend(&head, item->d_name , 5);
		item = raeddir(dir);
	}
	if (node == *root)
	{
		t_command *last;
		last = head;
		while (last->next)
			last = last->next;
		last->next = *root;
		*root = head;
	}
	else
	{
		t_command *next;
		next = node->next;
		t_command *last;
		last = head;
		while (last->next)
			last = last->next;
		last->next = next;
		node->next = next;
	}
}

void 	check_token_type(t_command **root, t_command *node)
{
	if (node->type == WILD)
		get_wild_value(root, node);
	else if (node->type == TILD)
		node->content = get_env_value("HOME");
	else if (node->type == VAR)
		node->content = get_env_value(node->content + 1);
	delete_node_commnd(root, node);
}

void	expend_tokens(t_command **root)
{
	t_command	*tmp;

	tmp = *root;
	while (tmp)
	{
		check_token_type(root, tmp);
		tmp = tmp->next;
	}
}

void	ex_cmd(t_cmd *cmd)
{
	expend_tokens(&cmd->next);
}