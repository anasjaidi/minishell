/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 22:55:07 by ajaidi            #+#    #+#             */
/*   Updated: 2022/06/25 17:35:23 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unclosed_quote(t_token **root)
{
	printf("unclosed quote\n");
	*root = NULL;
}

int	invalid_token(t_token **root, char *str)
{
	*root = NULL;
	printf("unexpected token\n");
	return (get_last(str));
}

int	get_last(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		;
	return (i);
}

int	calc_size(char *start, char *end)
{
	int	i;

	i = 1;
	while (start++ != end)
		i++;
	return (i);
}

int	check_flag(char *str, int q, t_token **root)
{
	if (*str == '|')
	{
		if (q == 1)
			return (PIPE);
		else
			return (OR);
	}
	else if (*str == '&')
		return (AND);
	else if (*str == '*')
		return (WILD);
	return (0);
}
