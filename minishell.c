/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:44:50 by ajaidi            #+#    #+#             */
/*   Updated: 2022/07/08 21:28:16 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*str;
	t_token	*root;
	t_tree	*head;

	if (ac > 1)
		printf("%s accept no params\n", ((*av) + 2));
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
		if (head)
			cast_node(head);
		root = NULL;
		head = NULL;
	}
}
