/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:44:50 by ajaidi            #+#    #+#             */
/*   Updated: 2022/06/23 23:41:35 by ajaidi           ###   ########.fr       */
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
	g.adrs = null;
	get_env(env);
	display_env(g.env);
	while (1)
	{
		str = readline("Minishell@robin:");
		if (str)
			head = token(str, &root);
		free(str);
		//display_tree(head, 0);
		ft_collect(&g.adrs, g.adrs);
		g.adrs = null;
		root = NULL;
		printf("%d\n", getpid());
	}
}
