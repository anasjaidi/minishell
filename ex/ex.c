/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 21:26:50 by ajaidi            #+#    #+#             */
/*   Updated: 2022/07/04 15:21:08 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cast_node(t_tree *root)
{
	// if (root->type == SUB)
	// 	ex_sub((t_sub *)root);
	if (root->type == CMD)
		ex_cmd((t_cmd *)root);
	// if (root->type == REDIR)
	// 	ex_redir((t_sub *)root);
	// if (root->type == T_PIPE)
	// 	ex_pipe((t_wp *)root);
	// if (root->type == T_AND)
	// 	ex_and_or((t_wp *)root);
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
	
	item = readdir(dir);
	while (item)
	{
		// printf("%s\n", item->d_name);
		if (item->d_name[0] != '.')
			append_in_cmdend(&head, item->d_name , 5);
		item = readdir(dir);
		// return ;
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
		node->next = head;
	}
		// display_nodetree(head);
}

void 	check_token_type(t_command **root, t_command *node)
{
	if (node->type == WILD)
	{
		get_wild_value(root, node);
		delete_node_commnd(root, node);
	}
	else  if (node->type == TILD)
	{
		printf("hpme is %s\n", get_env_value("HOME"));
		node->content = get_env_value("HOME");
	}
	else if (node->type == VAR)
		node->content = get_env_value(node->content + 1);
}

void	expend_tokens(t_command **root)
{
	if (!*root)
		return;
	t_command	*tmp;

	tmp = *root;
	while (tmp)
	{
		check_token_type(root, tmp);
		// printf("%s ", types_token[tmp->type]);
		tmp = tmp->next;
	}
}

void	check_builtin(char **argv)
{
	if (!ft_strcmp(*argv , "echo"))
		ft_echo(argv);
	else if (!ft_strcmp(*argv , "unset"))
		ft_unset(argv);
	else if (!ft_strcmp(*argv , "cd"))
		ft_cd(argv);
	else if (!ft_strcmp(*argv , "exit"))
		ft_exit(argv);
	else if (!ft_strcmp(*argv , "export"))
		ft_export(argv);
	else if (!ft_strcmp(*argv , "pwd"))
		ft_pwd(1);
}

void	ex_cmd(t_cmd *cmd)
{
	expend_tokens(&cmd->next);
	char **argv = transfer(cmd->next);
	// ft_echo(argv);
	check_builtin(argv);
}