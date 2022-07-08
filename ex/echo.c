/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 18:12:56 by ajaidi            #+#    #+#             */
/*   Updated: 2022/07/06 21:27:03 by ajaidi           ###   ########.fr       */
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

int	get_echo_flag(int flag)
{
	if (flag == 0 || flag == -2)
		return (-2);
	else
		return (-1);
}

int	ft_echo(char **argv)
{
	int	i;
	int	flag;

	i = 0;
	flag = 1;
	while (argv[++i])
	{
		if (flag >= 0 && argv[i][0] && argv[i][0] == '-' && argv[i][1])
		{
			if (new_line(argv[i]))
			{
				flag = 0;
				continue ;
			}
		}
		else
			flag = get_echo_flag(flag);
		ft_putstr_fd(argv[i], 1);
		if (argv[i + 1])
			ft_putstr_fd(" ", 1);
	}
	if (flag != -2)
		ft_putstr_fd("\n", 1);
	g_global.status = 0;
	return (0);
}
