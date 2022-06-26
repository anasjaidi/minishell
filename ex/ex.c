/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 21:26:50 by ajaidi            #+#    #+#             */
/*   Updated: 2022/06/25 21:32:08 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cast_node(t_tree *root)
{
	if (root->type == SUB)
		ex_sub((t_sub *)root);
	if (root->type == CMD)
		ex_cmd((t_cmd *)root);
	if (root->type == REDIR)
		ex_redir((t_sub *)root);
	if (root->type == T_PIPE)
		ex_pipe((t_wp *)root);
	if (root->type == T_AND)
		ex_and((t_wp *)root);
	if (root->type == T_OR)
		ex_or((t_wp *)root);
}