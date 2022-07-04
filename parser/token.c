/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 16:33:39 by ajaidi            #+#    #+#             */
/*   Updated: 2022/07/03 21:06:51 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree	*token(char *str, t_token **root)
{
	int		i;
	t_tree	*head = NULL;

	i = 0;
	while (str[i])
	{
		i += check_char(str + i, root);
	}
	if (*root)
	{
		if (!check_syntax(root))
			return (NULL);
		delete_quotes(root);
		head = get_full(root);
	}
	return (head);
}

int	check_char(char *str, t_token **root)
{
	if (*str == ')' || *str == '(')
		return (take_par(str, root));
	else if (*str == '$')
		return (take_var(str, root));
	else if (*str == 60 || *str == 62)
		return (take_less_more(str, root));
	else if (*str == '|' || *str == '*' || *str == '&')
		return (take_wp(str, root));
	else if (*str == '~')
		return (add_item(str, str + 1, TILD, root), 1);
	else if (*str == '\'' || *str == '\"')
		return (take_colon(str, root));
	else if ((*str >= 9 && *str <= 13) || (*str == 32))
		return (take_space(str, root));
	else
		return (take_word(str, root));
	return (0);
}

int	take_word(char *str, t_token **root)
{
	int		j;
	char	*comp;
	int		i;

	i = -1;
	comp = "&|\'\"$*<>~ \t\r\f\v\n()";
	while (str[++i])
	{
		j = -1;
		while (comp[++j])
			if (str[i] == comp[j])
				return (add_item(str, str + i, WORD, root), i);
	}
	return (add_item(str, str + i, WORD, root), i);
}

int	take_space(char *str, t_token **root)
{
	int	i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	add_item(str, str + i, WSPACE, root);
	return (i);
}

int	take_var(char *str, t_token **root)
{
	char	*comp;
	int		i;
	int		j;

	i = 0;
	comp = "&|\'\"$*<>~ \t\r\f\v\n()";
	while (str[++i])
	{
		j = -1;
		while (comp[++j])
			if (str[i] == comp[j])
				return (add_item(str, str + i, VAR, root), i);
	}
	return (add_item(str, str + i, VAR, root), i);
}
