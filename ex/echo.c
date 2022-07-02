/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 18:12:56 by ajaidi            #+#    #+#             */
/*   Updated: 2022/07/02 16:33:32 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	new_line(char *str)
{
	int	i;

	i = 0;
	while (str[++i])
		if (str[i] != 'n')
			return (0);
	return (1);
}

int	check_echo_flag(char **argv)
{
	int i = 0;
	int	flag = 1;
	while (argv[++i])
	{
		if (argv[i][0] && argv[i][0] == '-')
		{
			if (new_line(argv[i]))
			{
				flag = 0;
				continue;
			}
		}
		ft_putstr_fd(argv[i], 1);
		if (argv[i + 1])
			ft_putstr_fd(" ", 1);
	}
	if (flag)
		ft_putstr_fd(" ", 1);
}

void ft_echo(char **argv)
{
	int n;

	n = check_echo_flag(argv);
}