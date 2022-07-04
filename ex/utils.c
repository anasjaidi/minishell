/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 16:44:59 by ajaidi            #+#    #+#             */
/*   Updated: 2022/07/04 16:52:09 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_putstr_fd(char *str, int fd)
{
	int	i;
	
	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
}

int	cmdlstsize(t_command *root)
{
	int i = 0;
	while (root)
	{
		i++;
		root = root->next;
	}
	return (i);
}

char	**transfer(t_command *root)
{
	int i = -1;
	int n = cmdlstsize(root);
	char **argv = ft_malloc(&g.adrs, (n + 1) * sizeof(char *), 1);
	while (root)
	{
		argv[++i] =	root->content;
		root = root->next;
	}
	argv[n] = NULL;
	return (argv);
}