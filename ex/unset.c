/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 23:54:26 by ajaidi            #+#    #+#             */
/*   Updated: 2022/07/06 18:26:42 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_env(t_env **root, t_env *deleted)
{
	t_env	*tmp;
	t_env	*last;
	t_env	*deletedprev;

	if (!deleted)
		return ;
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

void	ft_unset(char **argv)
{
	int	i;

	i = 0;
	while (argv[++i])
		delete_env(&g_global.env, get_env_node(argv[i]));
	g_global.status = 0;
}
