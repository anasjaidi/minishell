/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 23:33:51 by ajaidi            #+#    #+#             */
/*   Updated: 2022/07/02 23:53:53 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_cd(char **argv)
{
	char buf[255];
	getcwd(buf, 255);
	char *cur = strdup(buf);
	int s;
	if (!argv[1])
	{
		char *home = get_env_value("HOME");
		if (!home)
		{
			ft_putstr_fd("bash: cd: HOME not set", 1);
			return ;
		}
		s = chdir(home);
	}
	s = chdir((const char *)argv[1]);
	if (s < 0)
	{
		ft_putstr_fd("bash: cd: ", 1);
		ft_putstr_fd(argv[1] , 1);
		ft_putstr_fd(": No such file or directory\n", 1);
	}
	else
	{
		t_env *node;
		node = get_env_node("OLDPDW");
		node->value = cur;
		node = get_env_node("PWD");
		getcwd(buf, 255);
		cur = strdup(buf);
		node->value = cur;
	}
	
}