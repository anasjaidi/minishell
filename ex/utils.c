/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 16:44:59 by ajaidi            #+#    #+#             */
/*   Updated: 2022/07/06 17:20:43 by ajaidi           ###   ########.fr       */
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

int	ft_atoi(const char *str)
{
	int	i;
	int	s;
	int	r;

	i = 0;
	s = 1;
	r = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		r *= 10;
		r += str[i] - 48;
		i++;
	}
	return (r * s);
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