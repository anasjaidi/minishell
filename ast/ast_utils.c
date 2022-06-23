/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 19:05:58 by ajaidi            #+#    #+#             */
/*   Updated: 2022/06/23 20:40:36 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*new_nodecommand(char *str, int flag)
{
	t_command	*new;

	new = (t_command *)ft_malloc(&g.adrs ,sizeof(t_command));
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

void display_tree(t_tree *tree, int in)
{
	if (!tree)
		return;
	for (size_t i = 0; i < in; i++)
		printf("├──");
	if (tree->type == CMD)
	{
		//display_tree((t_tree *)(((t_cmd *)tree)->next), in + 1);
		printf("%s ", types[tree->type - 16]);
		display_nodetree(((t_cmd*)tree)->next);
		printf("\n");
	}
	if (tree->type >= 19)
	{
		printf("%s\n", types[tree->type - 16]);
		display_tree((t_tree *)(((t_wp *)tree)->left), in + 1);
		display_tree((t_tree *)(((t_wp *)tree)->right), in + 1);
	}
	if (tree->type == 18)
	{
		printf("%s %s\n", types[tree->type - 16], ((t_redir*)tree)->filename);
		display_tree((t_tree *)(((t_redir *)tree)->next), in + 1);
	}
	if (tree->type == 16)
	{
		printf("%s \n", types[tree->type - 16]);
		display_tree((t_tree *)(((t_sub *)tree)->next), in + 1);
	}
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
int	ft_memcmp(void *s1,void *s2, int n)
{
	int	i;

	i = 0;
	if (!n)
		return (0);
	while (*(char *)(s1 + i) == *(char *)(s2 + i) && i < n - 1)
		i++;
	return (*(unsigned char *)(s1 + i) - *(unsigned char *)(s2 + i));
}