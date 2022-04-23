/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi < ajaidi@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 21:00:17 by ajaidi            #+#    #+#             */
/*   Updated: 2022/04/23 18:25:43 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_syntax(t_token **root)
{
	t_token	*temp;

	if (!check_begin(get_right(root, (*root)->prev)))
		return ((void)(syntax_error(root)));
	temp = get_right(root, (*root)->prev);
	while (temp != (*root)->prev)
	{
		temp = get_right(root, temp);
		if (!check_list(root, temp))
			return ((void)(syntax_error(root)));
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
	t_token	*t;

	t = get_right(head, root);
	if (!(t->type >= 0 && t->type <= 11) || t->type == 16)
		return (0);
	return (1);
}

int	check_cpar(t_token **head, t_token *root)
{
	t_token	*t;

	t = get_right(head, root);
	if (!(t->type >= 12 && t->type <= 15) && (t->type != 6))
		return (0);
	return (1);
}

int	check_red(t_token **head, t_token *root)
{
	t_token	*t;

	t = get_right(head, root);
	if ((!(t->type >= 5 && t->type <= 8) && (t->type != 0) && (t->type != 15) \
		&& (t->type != 10) && (t->type != 11)) || t->type == 16)
		return (0);
	return (1);
}

t_token	*get_right(t_token **head, t_token *root)
{
	if (root->next->type == 6)
	{
		if (root->next->next != *head)
			return (root->next->next);
		else
			return (NULL);
	}
	else
	{
		if (root->next != *head)
			return (root->next);
		else
			return (NULL);
	}
}
