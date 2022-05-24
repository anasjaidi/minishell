/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 01:19:23 by ajaidi            #+#    #+#             */
/*   Updated: 2022/05/24 02:22:12 by ajaidi           ###   ########.fr       */
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


t_tree	*get_block(t_token **head)
{
	t_wp	*ret;
	t_tree	*left;
	t_tree	*right;
	t_token	*tmp;

	left = get_pipe(head);
	tmp = *head;
	while (tmp)
	{
		if (tmp->type >= 12 && tmp->type <= 13)
		{
			right = get_pipe(&(tmp->next));
			ret = get_wp(get_type(tmp), left, right);
			left = ret;
		}
		tmp = tmp->next;
	}
	return (ret);
}

t_tree	*get_block(t_token **head)
{
	t_wp	*ret;
	t_tree	*left;
	t_tree	*right;
	t_token	*tmp;

	left = get_command(head);
	tmp = *head;
	while (tmp)
	{
		if (tmp->type == 14)
		{
			right = get_command(&(tmp->next));
			ret = get_wp(get_type(tmp), left, right);
			left = ret;
		}
		tmp = tmp->next;
	}
	return (ret);
}
