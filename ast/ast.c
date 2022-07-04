/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 01:19:23 by ajaidi            #+#    #+#             */
/*   Updated: 2022/07/03 22:02:17 by ajaidi           ###   ########.fr       */
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

t_tree	*get_block(t_token **head)
{
	t_tree	*ret;
	t_token	*tmp;
	t_tree	*left;
	t_tree	*right;

	ret = get_pipe(head);
	while (*head)
	{
		if ((*head)->type >= 12 && (*head)->type <= 13)
		{
			tmp = *head;
			*head = get_right(*head);
			left = (t_tree *)ret;
			right = (t_tree *)get_pipe(head);
			ret = (t_tree *)get_wp(get_type(tmp), left, right);
		}
		else
			break ;
	}
	return ((t_tree *)ret);
}

t_tree	*get_pipe(t_token **head)
{
	t_tree	*ret;
	t_token	*tmp;
	t_tree	*left;
	t_tree	*right;

	ret = get_command(head);
	while (*head)
	{
		if ((*head)->type == 14)
		{
			tmp = *head;
			*head = get_right(*head);
			left = ret;
			right = get_command(head);
			ret = get_wp(get_type(tmp), left, right);
		}
		else
			break ;
	}
	return ((t_tree *)ret);
}

t_tree	*get_cmdlist(t_token **head)
{
	t_cmd	*ret;

	ret = (t_cmd *)get_cmdnode(NULL);
	while (*head && ((*head)->type == VAR || (*head)->type == WORD || (*head)->type == TILD || (*head)->type == WILD))
	{
		append_in_cmdend(&ret->next, (*head)->str, (*head)->type);
		*head = get_right(*head);
	}
	return ((t_tree *)ret);
}

t_tree	*get_command(t_token **head)
{
	t_tree	*ret;
	t_tree	*next;
	t_redir	*redir;

	if ((*head)->type == 9)
	{
		*head = get_right(*head);
		ret = get_sub(get_block(head));
		*head = get_right(*head);
		ret = get_rdr(head, ret);
	}
	else
	{
		ret = get_rdr(head, NULL);
	}
	return (ret);
}
