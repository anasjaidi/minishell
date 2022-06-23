/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 23:26:11 by ajaidi            #+#    #+#             */
/*   Updated: 2022/06/23 23:38:43 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_node_env(char *key, char *value)
{
	t_env	*new;

	new = (t_env *)ft_malloc(&g.adrs, sizeof(t_env));
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
		printf("List is empty");
	else
	{
		temp = root;
		while (temp)
		{
			printf("[%s] = %s\n", temp->key, temp->value);
			temp = temp->next;
		}
	}
}

void	get_env(char **env)
{
	char **spl;
	while (*env)
	{
		spl = ft_split(*env, '=');
		append_in_end_env(&g.env, spl[0], spl[1]);
		env++;
	}
	
}