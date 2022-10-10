/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 16:37:13 by ajaidi            #+#    #+#             */
/*   Updated: 2022/09/29 01:49:49 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exit_parse(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!(str[i] >= 48 && str[i] <= 57))
			the_exit(255);
	return (ft_atoi(str));
}

int	ft_exit(char **argv)
{
	if (!argv[1])
		the_exit(g_global.status);
	if (argv[2])
		return (ft_putstr_fd("exit: too many arguments\n", 2), \
		g_global.status = 1, 0);
	the_exit(exit_parse(argv[1]));
	return (0);
}

void	the_exit(int status)
{
	ft_collect(&g_global.adrs, g_global.adrs, 1);
	rl_clear_history();
	exit(status);
}
