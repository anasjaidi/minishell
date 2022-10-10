/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 18:13:40 by ajaidi            #+#    #+#             */
/*   Updated: 2022/08/25 23:27:09 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expend_tokens(t_command **root)
{
	t_command	*tmp;

	if (!*root)
		return ;
	tmp = *root;
	while (tmp)
	{
		check_token_type(root, tmp);
		tmp = tmp->next;
	}
}

void	check_token_type(t_command **root, t_command *node)
{
	if (node->type == WILD)
	{
		get_wild_value(root, node);
		delete_node_commnd(root, node);
	}
	else if (node->type == TILD)
		node->content = get_env_value("HOME");
	else if (node->type == VAR && !ft_strcmp(node->content, "$?"))
		node->content = ft_itoa(g_global.status);
	else if (node->type == VAR && !ft_strcmp(node->content, "$$"))
		node->content = ft_itoa(getpid());
	else if (node->type == VAR)
		node->content = get_env_value(node->content + 1);
}

t_command	*get_wild_value_utils(void)
{
	t_command		*head;
	DIR				*dir;
	struct dirent	*item;

	dir = opendir(".");
	head = NULL;
	item = readdir(dir);
	while (item)
	{
		if (item->d_name[0] != '.')
			append_in_cmdend(&head, item->d_name, 5);
		item = readdir(dir);
	}
	return (head);
}

void	get_wild_value(t_command **root, t_command *node)
{
	t_command		*last;
	t_command		*next;
	t_command		*head;

	head = get_wild_value_utils();
	if (node == *root)
	{
		last = head;
		while (last->next)
			last = last->next;
		last->next = *root;
		*root = head;
	}
	else
	{
		next = node->next;
		last = head;
		while (last->next)
			last = last->next;
		last->next = next;
		node->next = head;
	}
}
