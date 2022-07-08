/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 15:25:23 by ajaidi            #+#    #+#             */
/*   Updated: 2022/07/08 17:26:19 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tree	*get_cmdlist(t_token **head)
{
	t_cmd	*ret;
	char	*join;

	ret = (t_cmd *)get_cmdnode(NULL);
	while (*head && ((*head)->type == VAR \
	|| (*head)->type == WORD || (*head)->type == TILD || (*head)->type == WILD))
	{
		join = "";
		if (get_cmdlist_utils(head, &ret->next, &join))
			continue ;
		if (*join && (*head))
			(*head)->str = join;
		else if (*join && !*head)
			return (append_in_cmdend(&ret->next, join, WORD), (t_tree *)ret);
		append_in_cmdend(&ret->next, (*head)->str, (*head)->type);
		if (!(*head && ((*head)->type == VAR \
	|| (*head)->type == TILD || (*head)->type == WILD \
	|| (*head)->type == WSPACE)))
			break ;
		else
			*head = get_right(*head);
	}
	return ((t_tree *)ret);
}

t_tree	*get_command(t_token **head)
{
	t_tree	*ret;

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

int	get_cmdlist_utils(t_token **head, t_command **root, char **join)
{
	if (!(*head)->str[0])
	{
		append_in_cmdend(root, "", WORD);
		*head = get_right(*head);
		return (1);
	}
	while (*head && (*head)->type == WORD)
	{
		*join = ft_strjoin(*join, (*head)->str);
		*head = (*head)->next;
	}
	return (0);
}
