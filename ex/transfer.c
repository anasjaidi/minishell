/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transfer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 18:12:08 by ajaidi            #+#    #+#             */
/*   Updated: 2022/07/08 18:49:18 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**transfer(t_command *root)
{
	int		i;
	int		n;
	char	**argv;

	i = -1;
	n = cmdlstsize(root);
	argv = ft_malloc(&g_global.adrs, (n + 1) * sizeof(char *), 1);
	while (root)
	{
		argv[++i] = root->content;
		root = root->next;
	}
	argv[n] = NULL;
	return (argv);
}
