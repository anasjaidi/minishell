/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 23:33:51 by ajaidi            #+#    #+#             */
/*   Updated: 2022/07/07 20:16:32 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_dir(char **argv, int s, char *cur)
{
	char	buf[255];
	t_env	*node;

	getcwd(buf, 255);
	cur = ft_strdup(buf);
	if (s < 0)
	{
		ft_putstr_fd("bash: cd: ", 1);
		ft_putstr_fd(argv[1], 1);
		ft_putstr_fd(": No such file or directory\n", 1);
		g_global.status = 1;
	}
	else
	{
		node = get_env_node("OLDPWD");
		if (node)
			node->value = cur;
		node = get_env_node("PWD");
		getcwd(buf, 255);
		cur = ft_strdup(buf);
		if (node)
			node->value = cur;
		g_global.status = 0;
	}
}

void	ft_cd(char **argv)
{
	char	*home;
	char	buf[4096];
	char	*cur;

	getcwd(buf, 4096);
	cur = ft_strdup(buf);
	if (!argv[1])
	{
		home = get_env_value("HOME");
		if (!home)
		{
			ft_putstr_fd("bash: cd: HOME not set", 1);
			g_global.status = 1;
			return ;
		}
		argv[1] = home;
	}
	check_dir(argv, chdir((const char *)argv[1]), cur);
}

t_env	*get_env_node(char *str)
{
	t_env	*tmp;

	tmp = g_global.env;
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
	int	i;

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

	tmp = g_global.env;
	while (tmp)
	{
		if (!ft_strcmp(str, tmp->key))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}
