/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi < ajaidi@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 21:00:17 by ajaidi            #+#    #+#             */
/*   Updated: 2022/04/21 21:29:31 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_syntax(t_token **root)
{
	if (!check_begin(*root))
		syntax_error(root);
}

int	check_begin(t_token *root)
{
	if (root->type <= 9 && root->type >= 1)
		check_
}

void	syntax_error(t_token **root)
{
	clr_lst(root, *root);
	*root == NULL;
	printf("syntax Eroor\n");
}
