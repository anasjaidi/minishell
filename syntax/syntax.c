/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi < ajaidi@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 21:00:17 by ajaidi            #+#    #+#             */
/*   Updated: 2022/04/24 02:34:31 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_syntax(t_token **root)
{
	t_token	*temp;

	if ((*root)->type == 6 && (*root)->next)
		temp = (*root)->next;
	else if ((*root)->type != 6)
		temp = *root;
	else
		return ;
	if (!check_begin(temp))
		return ((void)(syntax_error(root)));
	while (temp)
	{
		if (!check_list(root, temp))
			return ((void)(syntax_error(root)));
		temp = get_right(root, temp);
	}
	check_bal_par(root);
}

void	check_bal_par(t_token **root)
{
	int		l;
	t_token	*temp;

	l = 0;
	temp = *root;
	while (temp)
	{
		if (temp->type == 9)
			l++;
		else if (temp->type == 15)
			l--;
		if (l < 0)
			return ((void)(syntax_error(root)));
		temp = temp->next;
	}
	if (l)
		syntax_error(root);
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

int	check_list(t_token **head, t_token *root)
{
	if ((root->type >= 12 && root->type <= 14) || root->type == 9)
		return (check_wp(head, root));
	else if (root->type == 15)
		return (check_cpar(head, root));
	else if (root->type >= 1 && root->type <= 4)
		return (check_red(head, root));
	return (1);
}
