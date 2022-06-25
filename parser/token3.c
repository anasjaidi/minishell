/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 22:54:31 by ajaidi            #+#    #+#             */
/*   Updated: 2022/06/22 23:40:44 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	take_less_more(char *str, t_token **root)
{
	if (*str == '<')
	{
		if (*(str + 1) == '<')
			return (add_item(str, str + 2, DLESS, root), 2);
		else
			return (add_item(str, str + 1, LESS, root), 1);
	}
	if (*str == '>')
	{
		if (*(str + 1) == '>')
			return (add_item(str, str + 2, DGREAT, root), 2);
		else
			return (add_item(str, str + 1, GREAT, root), 1);
	}
	return (0);
}

int	take_wp(char *str, t_token **root)
{
	if (*str == '&' && *str != *(str + 1))
		return (invalid_token(root, str));
	if (*str != *(str + 1) || *str == '*')
		return (add_item(str, str + 1, check_flag(str, 1, root), root), 1);
	else if (*str == *(str + 1))
		return (add_item(str, str + 2, check_flag(str, 2, root), root), 2);
	return (0);
}

int	take_colon(char *str, t_token **root)
{
	int	i;

	i = 0;
	if (*str == '\"')
		return (take_dquote(str, root));
	add_item(str, str + 1, SQUOTE, root);
	str++;
	while (str[i] != '\'' && str[i])
		i++;
	if (str[i] == '\'')
	{
		add_item(str, str + i, WORD, root);
		add_item(str + i, str + i + 1, SQUOTE, root);
	}
	else if (!str[i])
		return (unclosed_quote(root), (i + 1));
	return (i + 2);
}

int	take_par(char *str, t_token **root)
{
	if (*str == '(')
		add_item(str, str + 1, OPAR, root);
	else
		add_item(str, str + 1, CPAR, root);
	return (1);
}
