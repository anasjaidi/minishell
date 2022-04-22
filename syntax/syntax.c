/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi < ajaidi@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 21:00:17 by ajaidi            #+#    #+#             */
/*   Updated: 2022/04/22 23:12:13 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_syntax(t_token **root)
{
	t_token	*temp;

	if (!check_begin(*root))
		return ((void)(syntax_error(root)));
	temp = (*root)->next;
	while (temp != (*root)->prev)
	{
		if (!check_list(temp))
			return ((void)(syntax_error(root)));
		temp = temp->next;
	}
}

int	check_begin(t_token *root)
{
	if (!(root->type <= 15 && root->type >= 12))
		return (1);
	else
		return (0);
}

void	syntax_error(t_token **root)
{
	clr_lst(root, *root);
	*root = NULL;
	printf("syntax Eroor\n");
}

int	check_list(t_token *root)
{
	if (root->type >= 12 && root->type <= 14)
		return (chech_wp(root));
	else if (root->type == 9)
		return (check_opar(root));
	else if (root->type == 15)
		return (check_cpar(root));
	else if (root->type >= 1 && root->type <= 4)
		return (check_red(root));
	return (1);
}

int	check_wp(t_token *root)
{
	
}