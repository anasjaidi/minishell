/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 22:48:58 by ajaidi            #+#    #+#             */
/*   Updated: 2022/07/04 19:39:40 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **ft_split_exp(char *line)
{
	char **argv, i = -1;

	argv = ft_split(line, '=');
	// if (argv && argv[1] && argv[2])
	// 	return NULL;
	if ((argv[0][0] >= '0' && argv[0][0] <= '9'))
		return NULL;
	while (argv[0][++i])
	{
		if (argv[0][i] == '+' && argv[0][i] && !argv[1])
			return NULL;
		else if (!(argv[0][i] >= 'a' && argv[0][i] <= 'z') && !(argv[0][i] >= 'A' && argv[0][i] <= 'Z') && !(argv[0][i] >= '0' && argv[0][i] <= '9') && (argv[0][i] != '_' && argv[0][i] != '+'))
			return NULL;
	}
	return argv;
}

void	display_exports()
{
	t_env *env;
	env = g.env;
	while (env)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env->key, 1);
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(env->value, 1);
		ft_putstr_fd("\"\n", 1);
		env = env->next;
	}
}

void	ft_export(char **argv)
{
	int i = 0;
	char	**spl;
	t_env *node;
	if (!argv[1])
		return	(void)display_exports();
	while(argv[++i])
	{
		spl = ft_split_exp(argv[i]);
		if (!spl)
		{
			ft_putstr_fd("bash: export: ", 1);
			ft_putstr_fd(argv[i], 1);
			ft_putstr_fd(": not a valid identifier\n", 1);
			break ;
		}
		if (spl[0][ft_strlen(spl[0])-1] == '+')
		{
			spl[0][ft_strlen(spl[0])-1] = 0;
			node = get_env_node(spl[0]);
			if (node)
				node->value = ft_strjoin(node->value, spl[1]);
			else
				append_in_end_env(&g.env, spl[0], spl[1]);
			break ;
		}
		node = get_env_node(spl[0]);
		if (!node)
			append_in_end_env(&g.env, spl[0], spl[1]);
		else
			node->value = spl[1];
	}
}

void	ft_env(int fd)
{
	(void)fd;
	display_env(g.env);
}