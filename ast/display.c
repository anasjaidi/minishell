/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 15:17:35 by ajaidi            #+#    #+#             */
/*   Updated: 2022/07/08 18:31:16 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	display_nodetree(t_command *root)
{
	t_command	*temp;

	temp = root;
	if (!root)
		printf("List is empty");
	else
	{
		temp = root;
		while (temp)
		{
			printf("[%s] ", temp->content);
			temp = temp->next;
		}
	}
}
