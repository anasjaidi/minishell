/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:44:50 by ajaidi            #+#    #+#             */
/*   Updated: 2022/06/23 21:55:52 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const char *types[] = {"subshell", "Command", "redirection", "pipe", "and", "or"};

int	main(void)
{
	char	*str;
	t_token	*root;
	t_tree	*head;

	root = NULL;
	g.adrs = null;
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
