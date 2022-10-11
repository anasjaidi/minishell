/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 23:54:26 by ajaidi            #+#    #+#             */
/*   Updated: 2022/10/11 00:42:18 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(char **argv) // ["unset", "PWD", "OLDPWD", "NOT", "PATH"]
{
	int	i;

	i = 0;
	while (argv[++i])
		delete_env(&g_global.env, get_env_node(argv[i]));
	g_global.status = 0;
}
