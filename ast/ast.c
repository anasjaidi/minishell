/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasjaidi <anasjaidi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 01:19:23 by ajaidi            #+#    #+#             */
/*   Updated: 2022/05/25 17:36:45 by anasjaidi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// https://freecoursesite.com/the-web-developer-bootcamp-37/
/*
	<cmdline>	::= <block>
		| <block> (";" | "&") <cmdline>

	<block>		::= <pipeline> {("&&" | "||") <pipeline>}

	<pipeline>	::= <command> {"|" <command>}

	<command>	::= <cmdlist>
		| "(" <cmdline> ")" <redir>	(* subshell *)

	<cmdlist>	::= <redir>+			(* at least one redirect - without WORDs *)
		| <redir> {<arg> <redir>}+	(* at least one WORD - zero or more <redir> in any place *)

	<redir>		::= {("<" | "<<" | ">" | ">>") <filename>}	(* a delimiter in case of heredoc *)

	<arg>		::= token WORD | token VAR | token GROUP

	<filename>	::= token WORD | token VAR | token GROUP
*/

t_tree	*get_full(t_token **head)
{
	t_wp	*ret;
	t_token	*tmp;

	tmp = *head;
	while (tmp)
	{
		if (tmp == *head && tmp->type != 6)
			;
		else
			tmp = get_right(tmp);
		get_block(&tmp);
	}
}

t_tree	*get_block(t_token **head)
{
	t_wp	*ret;
	t_tree	*left;
	t_tree	*right;

	left = get_pipe(head);
	while (*head)
	{
		if ((*head)->type >= 12 && (*head)->type <= 13)
		{
			*head = get_right(*head);
			left = (t_tree*)ret;
			right = get_pipe(head);
			ret = get_wp(get_type(get_left(*head)), left, right);
		}
	}
	return ((t_tree*)ret);
}

t_tree	*get_pipe(t_token **head)
{
	t_wp	*ret;
	t_tree	*left;
	t_tree	*right;

	left = get_command(head);
	while (*head)
	{
		if ((*head)->type == 14)
		{
			*head = get_right(*head);
			right = get_command(head);
			ret = get_wp(get_type(get_left(*head)), left, right);
			left = (t_tree*)ret;
		}
	}
	return ((t_tree*)ret);
}

t_tree	*get_command(t_token **head)
{
	t_sub	*ret;
	t_tree	*next;
	t_redir	*redir;	

	if ((*head)->type == 9)
	{
		*head = get_right(*head);
		ret->next = get_block(head);
		next = (t_tree *)ret;
	}
	while (get_right(*head)->type >= 1 &&  get_right(*head)->type <= 4)
	{
		*head = get_right(*head);
		redir = get_redir(REDIR, next, get_fd(*head), get_mode(*head) ,get_filename(head));
		next = (t_tree *)redir;
	}
}

