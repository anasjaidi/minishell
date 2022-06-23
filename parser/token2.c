/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 22:51:17 by ajaidi            #+#    #+#             */
/*   Updated: 2022/06/23 21:27:38 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	take_dquote(char *str, t_token **root)
{
	int	i;
	int	last;

	i = 0;
	last = 0;
	add_item(str, str + 1, DQUOTE, root);
	str++;
	while (str[i] != '\"' && str[i])
	{
		if (str[i] == '$')
		{
			if (i != 0)
			{
				add_item(str + last, str + i, WORD, root);
				i += take_qvar(str + i, root) - 1;
			}
			else
				i += take_qvar(str, root) - 1;
			last = i;
		}
		i++;
	}
	last = check_closed_dq(root, str, i, last);
	return (last);
}

int	check_closed_dq(t_token **root, char	*str, int i, int last)
{
	if (str [i] == '\"' && last == 0)
	{
		add_item(str, str + i, WORD, root);
		add_item(str + i, str + i + 1, DQUOTE, root);
	}
	else if (str [i] == '\"' && last != 0)
	{
		add_item(str + last + 1, str + i, WORD, root);
		add_item(str + i, str + i + 1, DQUOTE, root);
	}
	else if (!str[i])
		return (unclosed_quote(root), i + 1);
	return (i + 2);
}

int	take_qvar(char *str, t_token **root)
{
	char	*comp;
	int		i;
	int		j;

	comp = "!@#$*+-~./, \t\r\f\v\n\"()";
	while (str[++i])
	{
		j = -1;
		while (comp[++j])
			if (str[i] == comp[j])
				return (add_item(str, str + i, VAR, root), i);
	}
	return (i);
}

void	*add_item(char *start, char *end, int flag, t_token **root)
{
	char	*str;
	int		i;

	i = -1;
	str = (char *)ft_malloc(&g.adrs, calc_size(start, end));
	if (!str)
		return (NULL);
	while (start != end)
		str[++i] = *(start++);
	str[++i] = 0;
	append_in_end(root, str, flag);
	return (NULL);
}
