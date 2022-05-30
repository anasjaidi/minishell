/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedlist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 13:06:12 by ajaidi            #+#    #+#             */
/*   Updated: 2022/05/30 20:01:01 by ajaidi           ###   ########.fr       */
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
	new->prev = NULL;
	new->next = NULL;
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
		p = *root;
		while (p->next)
			p = p->next;
		p->next = tmp;
		tmp->prev = p;
	}
}

void	display_node(t_token *root)
{
	t_token	*temp;

	temp = root;
	if (!root)
		printf("List is empty\n");
	else
	{
		temp = root;
		while (temp)
		{
			printf("[%d]=>[%s]\n", temp->type, temp->str);
			temp = temp->next;
		}
	}
}
void	display_nodetree(t_command *root)
{
	t_command	*temp;

	temp = root;
	if (!root)
		printf("List is empty");
	else
	{
		temp = root;
		while (temp)
		{
			printf("[%s] ", temp->content);
			temp = temp->next;
		}
	}
}

void	clr_lst(t_token **root, t_token *node)
{
	if (node == NULL)
		return ;
	clr_lst(root, node->next);
	free(node);
}
