/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 23:33:51 by ajaidi            #+#    #+#             */
/*   Updated: 2022/07/04 19:37:43 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		argv[1] = home;
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
		node = get_env_node("OLDPWD");
		if (node)
			node->value = cur;
		node = get_env_node("PWD");
		getcwd(buf, 255);
		cur = strdup(buf);
		if (node)
			node->value = cur;
	}
	
}


t_env	*get_env_node(char *str)
{
	t_env	*tmp;

	tmp = g.env;
	while (tmp)
	{
		if (!ft_strcmp(str, tmp->key))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

char	*get_env_value(char *str)
{
	t_env	*tmp;

	tmp = g.env;
	while (tmp)
	{
		if (!ft_strcmp(str, tmp->key))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}