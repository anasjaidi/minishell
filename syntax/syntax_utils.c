/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi < ajaidi@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 02:33:19 by ajaidi            #+#    #+#             */
/*   Updated: 2022/04/24 05:49:29 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	if ((!(t->type >= 5 && t->type <= 8) && (t->type != 0) && (t->type != 15) \
		&& (t->type != 10) && (t->type != 11)))
		return (0);
	return (1);
}

t_token	*get_right(t_token *root)
{
	if (root->next && root->next->type == 6)
	{
		if (root->next->next)
			return (root->next->next);
		else
			return (NULL);
	}
	else
		return (root->next);
}

t_token	*get_left(t_token *root)
{
	if (root->prev && root->prev->type == 6)
	{
		if (root->prev->prev)
			return (root->prev->prev);
		else
			return (NULL);
	}
	else
		return (root->prev);
}
