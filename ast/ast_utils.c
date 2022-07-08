/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 19:05:58 by ajaidi            #+#    #+#             */
/*   Updated: 2022/07/07 20:59:44 by ajaidi           ###   ########.fr       */
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

int	ft_strlen(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}


void	display_tree(t_tree *tree, int in)
{
	int	i;

	i = -1;
	if (!tree)
		return ;
	while (++i < in)
		printf("├──");
	if (tree->type == CMD)
		return (printf("%s ", types[tree->type - 16]), \
			display_nodetree(((t_cmd *)tree)->next), (void)printf("\n"));
	else if (tree->type >= 19)
		return (printf("%s\n", types[tree->type - 16]), \
			display_tree((t_tree *)(((t_wp *)tree)->left), in + 1), \
				(void)display_tree((t_tree *)(((t_wp *)tree)->right), in + 1));
	else if (tree->type == 18)
		return (printf("%s %s\n", types[tree->type - 16], \
			((t_redir *)tree)->filename), \
				(void)display_tree((t_tree *)(((t_redir *)tree)->next), \
					in + 1));
	else if (tree->type == 16)
		return (printf("%s \n", types[tree->type - 16]), \
			display_tree((t_tree *)(((t_sub *)tree)->next), in + 1));
}
