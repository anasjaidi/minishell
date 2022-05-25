/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi < ajaidi@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 22:55:07 by ajaidi            #+#    #+#             */
/*   Updated: 2022/04/21 16:56:08 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unclosed_quote(t_token **root)
{
	clr_lst(root, *root);
	printf("unclosed quote\n");
	*root = NULL;
}

int	invalid_token(t_token **root, char *str)
{
	clr_lst(root, *root);
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
