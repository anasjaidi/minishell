/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 21:00:17 by ajaidi            #+#    #+#             */
/*   Updated: 2022/07/08 17:30:21 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_syntax(t_token **root)
{
	t_token	*temp;

	if ((*root)->type == 6 && (*root)->next)
		temp = (*root)->next;
	else if ((*root)->type != 6)
		temp = *root;
	else
		return (0);
	if (!check_begin(temp))
		return ((void)(syntax_error()), 0);
	while (temp)
	{
		if (!check_list(temp))
			return ((void)(syntax_error()), 0);
		temp = get_right(temp);
	}
	return (check_bal_par(root));
}

int	check_list(t_token *root)
{
	if ((root->type >= 12 && root->type <= 14) || root->type == 9)
		return (check_wp(root));
	else if (root->type == 15)
		return (check_cpar(root));
	else if (root->type >= 1 && root->type <= 4)
		return (check_red(root));
	return (1);
}

int	check_wp(t_token *root)
{
	t_token	*t;

	t = get_left(root);
	if (root->type == 9 && t && \
		!(t->type >= 12 && t->type <= 14) && t->type != 9)
		return (0);
	t = get_right(root);
	if (!t)
		return (0);
	if (!(t->type >= 0 && t->type <= 11))
		return (0);
	return (1);
}

int	check_cpar(t_token *root)
{
	t_token	*t;

	t = get_right(root);
	if (!t)
		return (1);
	if (!(t->type >= 12 && t->type <= 15) && !(t->type >= 1 && t->type <= 4))
		return (0);
	return (1);
}

int	check_red(t_token *root)
{
	t_token	*t;

	t = get_right(root);
	if (!t)
		return (0);
	if ((!(t->type >= 5 && t->type <= 8) && (t->type != 0) \
		&& (t->type != 10) && (t->type != 11)))
		return (0);
	return (1);
}
