/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 23:54:26 by ajaidi            #+#    #+#             */
/*   Updated: 2022/07/08 16:21:48 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(char **argv)
{
	int	i;

	i = 0;
	while (argv[++i])
		delete_env(&g_global.env, get_env_node(argv[i]));
	g_global.status = 0;
}
