/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 22:48:58 by ajaidi            #+#    #+#             */
/*   Updated: 2022/07/04 16:29:21 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **ft_split_exp(char *line)
{
	char **argv, i = -1;

	argv = ft_split(line, '=');
	// if (argv[2])
	// 	return NULL;
	// else if (!(argv[0][0] >= '0' && argv[0][0] <= '9'))
	// 	return NULL;
	// while (*argv[++i])
	// {
	// 	if (*argv[i] == '+' && *argv[i + 1])
	// 		return NULL;
	// 	else if (!(*argv[i] >= 'a' && *argv[i] <= 'z') && !(*argv[i] >= 'A' && *argv[i] <= 'Z') && !(*argv[i] >= '0' && *argv[i] <= '9') && (*argv[i] != '_' && *argv[i] != '+'))
	// 		return NULL;
	// }
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
	if (!argv[1])
		return	(void)display_exports();
	while(argv[++i])
	{
		spl = ft_split(argv[i], '=');
		// spl = ft_split_exp(argv[i]);
		// if (!spl)
		// {
		// 	ft_putstr_fd("bash: export: ", 1);
		// 	ft_putstr_fd(argv[i], 1);
		// 	ft_putstr_fd(": not a valid identifier", 1);
		// 	break ;
		// }
		// if (spl[0][ft_strlen(spl[0])-2] == '+')
		// {
		// 	spl[0][ft_strlen(spl[0])-2] = 0;
		// 	t_env *node;
		// 	node = get_env_node(spl[0]);
		// 	node->value = ft_strjoin(node->value, spl[1]);
		// }
		append_in_end_env(&g.env, spl[0], spl[1]);
	}
}