/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:44:50 by ajaidi            #+#    #+#             */
/*   Updated: 2022/07/04 17:00:50 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const char *types[] = {"subshell", "Command", "redirection", "pipe", "and", "or"};
const char *types_token[] = {"VAR", "DGREAT", "DLESS", "LESS", "GREAT", "WORD", "WSPACE", "SQUOTE", "DQUOTE",  "OPAR", "WILD", "TILD", "AND", "OR", "PIPE", "CPAR"};

int	main(int ac, char **av, char **env)
{
	char	*str;
	t_token	*root;
	t_tree	*head;

	root = NULL;
	g.adrs = NULL;
	get_env(env);

	while (1)
	{
		str = readline("Minishell@robin:");
		if (str)
			head = token(str, &root);
		free(str);
		if (head)
			cast_node(head);
		if (g.adrs)
			ft_collect(&g.adrs, g.adrs, 0);
		root = NULL;
		head = NULL;
	}

}
