/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi < ajaidi@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 01:19:23 by ajaidi            #+#    #+#             */
/*   Updated: 2022/05/22 02:48:42 by ajaidi           ###   ########.fr       */
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

t_tree	*get_ast(t_list **head)
{
	t_tree	*root;

	root = get_block(head);
	return (root);
}

t_tree	*get_block(t_list **head)
{
	t_tree	*root;
	t_list	*tmp;	

	tree = get_command(head);
	tmp = *head;
	while (tmp)
	{
		if (tmp->type >= 12 && tmp->type <= 13)
			root = get_block(&tmp);
	} 

	
	return (root);
}