/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 16:37:13 by ajaidi            #+#    #+#             */
/*   Updated: 2022/07/08 00:11:31 by ajaidi           ###   ########.fr       */
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
		return (ft_putstr_fd("exit: too many arguments\n", 1), \
		g_global.status = 1, 0);
	the_exit(exit_parse(argv[1]));
	return (0);
}

int	ft_pwd(int fd)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		ft_putstr_fd(pwd, fd);
		ft_putstr_fd("\n", fd);
		free(pwd);
		g_global.status = 0;
	}
	else
		g_global.status = 1;
	return (0);
}

void	the_exit(int status)
{
	ft_collect(&g_global.adrs, g_global.adrs, 1);
	rl_clear_history();
	exit(status);
}
