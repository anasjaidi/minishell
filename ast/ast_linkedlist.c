/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_linkedlist.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 15:29:55 by ajaidi            #+#    #+#             */
/*   Updated: 2022/07/08 17:26:47 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_command	*new_nodecommand(char *str, int flag)
{
	t_command	*new;

	new = (t_command *)ft_malloc(&g_global.adrs, sizeof(t_command), 1);
	if (!new)
		return (NULL);
	new->content = str;
	new->type = flag;
	new->next = NULL;
	return (new);
}

void	append_in_cmdend(t_command **root, char *str, int type)
{
	t_command	*tmp;
	t_command	*p;

	tmp = new_nodecommand(str, type);
	if (!*root)
		*root = tmp;
	else
	{
		p = *root;
		while (p->next)
			p = p->next;
		p->next = tmp;
	}
}

int	cmdlstsize(t_command *root)
{
	int	i;

	i = 0;
	while (root)
	{
		i++;
		root = root->next;
	}
	return (i);
}

void	delete_node_commnd(t_command **root, t_command *deleted)
{
	t_command	*deletedprev;
	t_command	*last;

	if (deleted == *root)
		*root = deleted->next;
	else if (!deleted->next)
	{
		last = *root;
		while (last->next->next)
			last = last->next;
		last->next = NULL;
	}
	else
	{
		deletedprev = *root;
		while (deletedprev->next != deleted)
			deletedprev = deletedprev->next;
		deletedprev->next = deleted->next;
	}
}
