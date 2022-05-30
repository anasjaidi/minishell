/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 01:19:23 by ajaidi            #+#    #+#             */
/*   Updated: 2022/05/30 01:43:51 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// https://freecoursesite.com/the-web-developer-bootcamp-37/
/*

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

t_tree *get_full(t_token **head)
{
	t_tree *ret;
	t_token *tmp;

	tmp = *head;
	while (tmp)
	{
		if (tmp == *head && tmp->type != 6)
			;
		else
			tmp = get_right(tmp);
		ret = get_block(&tmp);
	}
	return ((t_tree *)ret);
}

t_tree *get_block(t_token **head)
{
	t_tree *ret;
	t_tree *left;
	t_tree *right;

	ret = get_pipe(head);
	while (*head)
	{
		if ((*head)->type >= 12 && (*head)->type <= 13)
		{
			*head = get_right(*head);
			left = (t_tree *)ret;
			right = (t_tree *)get_pipe(head);
			ret = (t_tree *)get_wp(get_type(get_left(*head)), left, right);
		}
		else
			break;
	}
	return ((t_tree *)ret);
}

t_tree *get_pipe(t_token **head)
{
	t_tree *ret;
	t_tree *left;
	t_tree *right;

	ret = get_command(head);
	while (*head)
	{
		if ((*head)->type == 14)
		{
			*head = get_right(*head);
			left = ret;
			right = get_command(head);
			ret = get_wp(get_type(get_left(*head)), left, right);
		}
	}
	return ((t_tree *)ret);
}


















t_command	*new_nodecommand(char *str, int flag)
{
	t_command	*new;

	new = (t_command *)malloc(sizeof(t_command));
	if (!new)
		return (NULL);
	new->content = str;
	new->type = flag;
	new->next = NULL;
	return (new);
}

void	append_in_cmdend(t_command **root, char *str)
{
	t_command	*tmp;
	t_command	*p;

	tmp = new_nodecommand(str, CMD);
	if (!*root)
		*root = tmp;
	else
	{
		p = *root;
		while (p->next)
			p = p->next;
		p->next = tmp;
	}
}

































t_tree *get_cmdlist(t_token **head)
{
	t_cmd *ret;
	t_command **root;

	ret = (t_cmd*)get_cmdnode(NULL);
	root = &ret->next;

	while ((*head)->type == VAR || (*head)->type == WORD)
	{
		append_in_cmdend(root, (*head)->str);
		*head = get_right(*head);
	}
	return ((t_tree*)ret);
}

t_tree *get_command(t_token **head)
{
	t_tree *ret;
	t_tree *next;
	t_redir *redir;

	if ((*head)->type == 9)
	{
		*head = get_right(*head);
		ret = get_sub(get_block(head));
		*head = get_right(*head);
	}
	else
	{
		ret = get_cmdlist(head);
	}

	// while ((*head)->type >= 1 &&  (*head)->type <= 4)
	// {
	// 	*head = get_right(*head);
	// 	redir = get_redir(REDIR, next, get_fd(get_left(*head)), get_mode(get_left(*head)) ,get_filename(head));
	// 	next = (t_tree *)redir;
	// }
	return (ret);
}

void display_tree(t_tree *tree, int in)
{
	if (!tree)
		return;
	for (size_t i = 0; i < in; i++)
		printf("	");
	if (tree->type == CMD)
	{
		display_tree((t_tree *)(((t_cmd *)tree)->next), in + 1);
		printf("%s", types[tree->type - 16]);
	}
	if (tree->type >= 19)
	{
		display_tree((t_tree *)(((t_wp *)tree)->left), in + 1);
		printf("%s", types[tree->type - 16]);
		display_tree((t_tree *)(((t_wp *)tree)->right), in + 1);
	}
	if (tree->type == 18)
	{
		display_tree((t_tree *)(((t_redir *)tree)->next), in + 1);
		printf("%s", types[tree->type - 16]);
		display_tree((t_tree *)(((t_redir *)tree)->filename), in + 1);
	}
	if (tree->type == 16)
	{
		display_tree((t_tree *)(((t_sub *)tree)->next), in + 1);
		printf("%s", types[tree->type - 16]);
	}
}