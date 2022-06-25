/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 17:34:49 by ajaidi            #+#    #+#             */
/*   Updated: 2022/06/25 17:36:01 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*link_nodes(t_token **root, t_token *deleted)
{
	t_token	*tmp;

	if (!deleted->prev)
	{
		*root = deleted->next;
		(*root)->prev = NULL;
		return (*root);
	}
	else if (!deleted->next)
	{
		tmp = deleted->prev;
		deleted->prev->next = NULL;
		return (tmp);
	}
	tmp = deleted->prev;
	deleted->next->prev = tmp;
	tmp->next = deleted->next;
	return (tmp);
}

void	delete_quotes(t_token **root)
{
	t_token	*tmp;

	tmp = *root;
	while (tmp)
	{
		if (tmp->type == 7 || tmp->type == 8)
			tmp = link_nodes(root, tmp);
		tmp = tmp->next;
	}
}
