/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:44:50 by ajaidi            #+#    #+#             */
/*   Updated: 2022/07/08 00:36:22 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const char *types[] = {"subshell", "Command", "redirection", "pipe", "and", "or"};
const char *types_token[] = {"VAR", "DGREAT", "DLESS", "LESS", "GREAT", "WORD", "WSPACE", "SQUOTE", "DQUOTE",  "OPAR", "WILD", "TILD", "AND", "OR", "PIPE", "CPAR"};

int check_history(char *str)
{
	while (*str)
	{
		if (*str != ' ' && *str != '\t')
			return (1);
		str++;
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	char	*str;
	t_token	*root;
	t_tree	*head;

	root = NULL;
	g_global.adrs = NULL;
	get_env(env);
	listen();
	while (1)
	{
		str = readline("Minishell@robin:");
		if (!str)
			the_exit(g_global.status);
		head = token(str, &root);
		if (check_history(str))
			add_history(str);
		free(str);
		// display_node(root);
		// display_tree(head, 0);
		if (head)
			cast_node(head);
		root = NULL;
		head = NULL;
	}
}
