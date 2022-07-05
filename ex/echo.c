/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 18:12:56 by ajaidi            #+#    #+#             */
/*   Updated: 2022/07/05 19:08:28 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	new_line(char *str)
{
	int	i;

	i = 0;
	while (str[++i])
		if (str[i] != 'n')
			return (0);
	return (1);
}

int	ft_echo(char **argv)
{
	int i = 0;
	int	flag = 1;
	while (argv[++i])
	{
		if (flag >= 0 && argv[i][0] && argv[i][0] == '-' &&argv[i][1])
		{
			if (new_line(argv[i]))
			{
				flag = 0;
				continue;
			}
		}
		else
			flag = flag == 0 || flag == -2? -2 : -1;
		ft_putstr_fd(argv[i], 1);
		if (argv[i + 1])
			ft_putstr_fd(" ", 1);
	}
	if (flag != -2)
		ft_putstr_fd("\n", 1);
	return 0;
}

