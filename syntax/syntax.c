/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 21:00:17 by ajaidi            #+#    #+#             */
/*   Updated: 2022/07/03 22:14:04 by ajaidi           ###   ########.fr       */
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
		return 0;
	if (!check_begin(temp))
		return ((void)(syntax_error(root)), 0);
	while (temp)
	{
		if (!check_list(temp))
			return ((void)(syntax_error(root)), 0);
		temp = get_right(temp);
	}
	return (check_bal_par(root));
}

int	check_bal_par(t_token **root)
{
	int		l;
	t_token	*temp;

	if (!*root)
		return 0;
	l = 0;
	temp = *root;
	while (temp)
	{
		if (temp->type == 9)
			l++;
		else if (temp->type == 15)
			l--;
		if (l < 0)
			return ((void)(syntax_error(root)), 0);
		temp = temp->next;
	}
	if (l)
		return (syntax_error(root), 0);
	return (1);
}

int	check_begin(t_token *root)
{
	if (root->type >= VAR && root->type <= 11)
		return (1);
	else
		return (0);
}

void	syntax_error(t_token **root)
{
	printf("syntax Eroor\n");
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
