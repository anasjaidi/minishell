/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 16:37:13 by ajaidi            #+#    #+#             */
/*   Updated: 2022/07/06 17:19:48 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int exit_parse(char *str)
{
	int i = -1;
	while (str[++i])
		if (!(str[i] >= 48 && str[i] <= 57))
			the_exit(255);
	return (ft_atoi(str));
}

int	ft_exit(char **argv)
{
	if (!argv[1])
		the_exit(g.status);
	if (argv[2])
		return (ft_putstr_fd("exit: too many arguments\n", 1), g.status = -7, 0);
	the_exit(exit_parse(argv[1]));
	return 0;
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
		g.status = 0;
	}
	else
		g.status = 1;
	return 0;
}

void the_exit(int status)
{
	ft_collect(&g.adrs,g.adrs,  1);
	exit(status);
}