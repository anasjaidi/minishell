/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi < ajaidi@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 01:19:23 by ajaidi            #+#    #+#             */
/*   Updated: 2022/05/21 01:21:57 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


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

void	get_ast(t_list **head, t_tree **root)
{
	
}