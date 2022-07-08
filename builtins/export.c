/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 22:48:58 by ajaidi            #+#    #+#             */
/*   Updated: 2022/07/08 21:56:59 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// if (argv && argv[1] && argv[2])
// 	return NULL;

char	**ft_split_exp(char *line)
{
	char	**argv;
	int		i;

	i = -1;
	argv = ft_split(line, '=');
	if (argv && argv[0] && argv[1] && argv[2])
		return (NULL);
	if (!argv || !*argv)
		return (NULL);
	if ((argv[0][0] >= '0' && argv[0][0] <= '9'))
		return (NULL);
	while (argv[0][++i])
	{
		if ((argv[0][i] == '+' && argv[0][i + 1]))
			return (NULL);
		else if (!(argv[0][i] >= 'a' && argv[0][i] <= 'z') \
		&& !(argv[0][i] >= 'A' && argv[0][i] <= 'Z') && \
		!(argv[0][i] >= '0' && argv[0][i] <= '9') && \
		(argv[0][i] != '_' && argv[0][i] != '+'))
			return (NULL);
	}
	return (argv);
}

void	display_exports(void)
{
	t_env	*env;

	env = g_global.env;
	while (env)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env->key, 1);
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(env->value, 1);
		ft_putstr_fd("\"\n", 1);
		env = env->next;
	}
	g_global.status = 0;
}

int	ft_export_utils(char **argv, char **spl, int *status, int i)
{
	t_env	*node;

	if (!spl || (spl[0][0] == '+') || argv[i][0] == '=' || \
	(spl[0][ft_strlen(spl[0]) - 1] == '+' \
	&& argv[i][ft_strlen(argv[i]) - 1] == '='))
	{
		*status = 1;
		ft_putstr_fd("bash: export: ", 1);
		ft_putstr_fd(argv[i], 1);
		ft_putstr_fd(": not a valid identifier\n", 1);
		return (1);
	}
	if (spl[0][ft_strlen(spl[0]) - 1] == '+')
	{
		spl[0][ft_strlen(spl[0]) - 1] = 0;
		node = get_env_node(spl[0]);
		if (node)
			node->value = ft_strjoin(node->value, spl[1]);
		else
			append_in_end_env(&g_global.env, spl[0], spl[1]);
		return (1);
	}
	return (0);
}

void	ft_export(char **argv)
{
	int		i;
	int		status;
	char	**spl;
	t_env	*node;

	i = 0;
	status = 0;
	if (!argv[1])
		return ((void)display_exports());
	while (argv[++i])
	{
		spl = ft_split_exp(argv[i]);
		if (ft_export_utils(argv, spl, &status, i))
			break ;
		if (*spl && !spl[1] && argv[i][ft_strlen(argv[i]) - 1] == '=')
			return ((void)append_in_end_env(&g_global.env, spl[0], ""));
		node = get_env_node(spl[0]);
		if (!node)
			append_in_end_env(&g_global.env, spl[0], spl[1]);
		else
			node->value = spl[1];
	}
	g_global.status = status;
}
