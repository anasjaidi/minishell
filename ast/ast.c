/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 01:19:23 by ajaidi            #+#    #+#             */
/*   Updated: 2022/07/08 15:28:33 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tree	*get_full(t_token **head)
{
	t_tree	*ret;
	t_token	*tmp;

	tmp = *head;
	if (tmp == *head && tmp->type != 6)
		;
	else
		tmp = get_right(tmp);
	ret = get_block(&tmp);
	return ((t_tree *)ret);
}
