/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi < ajaidi@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 21:00:17 by ajaidi            #+#    #+#             */
/*   Updated: 2022/04/23 03:22:18 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_syntax(t_token **root)
{
	t_token	*temp;

	if (!check_begin(*root))
		return ((void)(syntax_error(root)));
	temp = (*root);
	while (temp != (*root)->prev)
	{
		if (!check_list(root, temp))
			return ((void)(syntax_error(root)));
		temp = temp->next;
	}
	if (!check_list(root, temp))
		return ((void)(syntax_error(root)));
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

int	check_wp(t_token **head, t_token *root)
{
	int	t;

	t = get_right(head, root);
	if (!(t >= 0 && t <= 11) || t == 16)
		return (0);
	return (1);
}

int	check_cpar(t_token **head, t_token *root)
{
	int	t;

	t = get_right(head, root);
	if (!(t >= 12 && t <= 15) && (t != 6))
		return (0);
	return (1);
}

int	check_red(t_token **head, t_token *root)
{
	int	t;

	t = get_right(head, root);
	if ((!(t >= 5 && t <= 8) && (t != 0) && (t != 15)\
		&& (t != 10) && (t != 11)) || t == 16)
		return (0);
	return (1);
}

int	get_right(t_token **head, t_token *root)
{
	if (root->next->type == 6)
	{
		if (root->next->next != *head)
			return (root->next->next->type);
		else
			return (16);
	}
	else
	{
		if (root->next != *head)
			return (root->next->type);
		else
			return (16);
	}
}
