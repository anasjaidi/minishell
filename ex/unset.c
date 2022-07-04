/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 23:54:26 by ajaidi            #+#    #+#             */
/*   Updated: 2022/07/03 21:17:51 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_env(t_env **root, t_env *deleted)
{
	t_env	*tmp;
	
	if (!deleted)
		return ;
	if (deleted == *root)
		*root = deleted->next;
	else if (!deleted->next)
	{
		t_env *last;
		last = *root;
		while (last->next->next)
			last = last->next;
		last->next = NULL;
	}
	else
	{
		t_env *deletedprev;
		deletedprev = *root;
		while (deletedprev->next != deleted)
			deletedprev = deletedprev->next;
		deletedprev->next = deleted->next;
	}
}

void	ft_unset(char **argv)
{
	int i = 0;
	while (argv[++i])
		delete_env(&g.env, get_env_node(argv[i]));
		
}