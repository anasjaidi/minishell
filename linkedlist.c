/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedlist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi < ajaidi@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 13:06:12 by ajaidi            #+#    #+#             */
/*   Updated: 2022/04/20 22:59:03 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_node(char *str, int flag)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->str = str;
	new->type = flag;
	new->prev = new;
	new->next = new;
	return (new);
}

void	append_in_end(t_token **root, char *str, int flag)
{
	t_token	*tmp;
	t_token	*p;

	tmp = new_node(str, flag);
	if (!*root)
		*root = tmp;
	else
	{
		p = (*root)->prev;
		tmp->next = *root;
		(*root)->prev = tmp;
		p->next = tmp;
		tmp->prev = p;
	}
}

void	display_node(t_token *root)
{
	t_token	*temp;

	temp = root;
	if (!root)
		return ;
	else
	{
		temp = temp->prev;
		while (root != temp)
		{
			printf("[%d]=>[%s]\n", root->type, root->str);
			root = root->next;
		}
		printf("[%d]=>[%s]\n", root->type, root->str);
	}
}

void	clr_lst(t_token **root, t_token *node)
{
	if (!node)
		return ;
	if (node == (*root)->prev)
		return ((void)free(node));
	clr_lst(root, node->next);
	free(node);
}
