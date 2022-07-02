/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:44:50 by ajaidi            #+#    #+#             */
/*   Updated: 2022/07/02 20:23:51 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const char *types[] = {"subshell", "Command", "redirection", "pipe", "and", "or"};

int	main(int ac, char **av, char **env)
{
	char	*str;
	t_token	*root;
	t_tree	*head;

	root = NULL;
	g.adrs = NULL;
	get_env(env);
	display_env(g.env);
	while (1)
	{
		str = readline("Minishell@robin:");
		if (str)
			head = token(str, &root);
		free(str);
		if (head)
			display_tree(head, 0);
		ft_collect(&g.adrs, g.adrs);
		g.adrs = NULL;
		root = NULL;
	}
}
