/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 23:26:11 by ajaidi            #+#    #+#             */
/*   Updated: 2022/07/06 21:13:39 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_node_env(char *key, char *value)
{
	t_env	*new;

	new = (t_env *)ft_malloc(&g_global.adrs, sizeof(t_env), 0);
	if (!new)
		return (NULL);
	new->value = value;
	new->key = key;
	new->next = NULL;
	return (new);
}

void	append_in_end_env(t_env **root, char *key, char *value)
{
	t_env	*tmp;
	t_env	*p;

	tmp = new_node_env(key, value);
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

void	display_env(t_env *root)
{
	t_env	*temp;

	temp = root;
	if (!root)
		return ;
	else
	{
		temp = root;
		while (temp)
		{
			if (temp->value)
			{
				ft_putstr_fd(temp->key, 1);
				ft_putstr_fd("=", 1);
				ft_putstr_fd(temp->value, 1);
				ft_putstr_fd("\n", 1);
			}
			temp = temp->next;
		}
	}
}

void	get_env(char **env)
{
	char	**spl;

	while (*env)
	{
		spl = ft_split(*env, '=');
		append_in_end_env(&g_global.env, spl[0], spl[1]);
		env++;
	}
}
