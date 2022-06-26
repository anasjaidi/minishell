/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 16:37:13 by ajaidi            #+#    #+#             */
/*   Updated: 2022/06/26 16:54:30 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exit(int status)
{
	ft_collect(&g.adrs, g.adrs);
	exit(status);
}

int	ft_pwd(int fd)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		ft_putstr_fd(pwd, fd);
		ft_putchar_fd('\n', fd);
		free(pwd);
		exit(0);
	}
	else
		exit (-1);
}