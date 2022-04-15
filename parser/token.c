/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 16:33:39 by ajaidi            #+#    #+#             */
/*   Updated: 2022/04/13 16:41:14 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	token(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i =+ check_char(str + i);
	}
	
}

int check_char(char *str)
{
	if (*str == '$')
		return (take_var(str));
	else if (*str == 60 || *str == 62)
		return (take_less_more(str));
	else if (*str == '|' || *str == '*' || *str == '&')
		return (take_wp(str));
	else if (*str == '~')
		return (add_item(str, str + 1, TILD), 1);
	else if (*str == '\'' || *str == '\"')
		return (take_colon(str));
	else if (*str >= 9 && *str <= 13 || (*str == 32))
		return (take_space(str));
	else
		return (take_word(str));
}

int take_var(char *str)
{
	int i = -1;
	int j = -1;
	char	*comp = "&|\'\"$*<>~ \t\r\f\v\n";
	while (str[i])
	{
		while (comp[++j])
			if (str[i] == comp[j])
				return (add_item(str, str + i, VAR),i + 1);
	}
	return (add_item(str, str + i, VAR),i + 1);
}

int	take_less_more(char *str)
{
	if (*str == '<')
	{
		if (*(str + 1) == '<')
			return (add_item(str, str + 2, DLESS), 2);
		else
			return (add_item(str, str + 1, LESS), 1);
	}
	if (*str == '>')
	{
		if (*(str + 1) == '>')
			return (add_item(str, str + 2, DGREAT), 2);
		else
			return (add_item(str, str + 1, GREAT), 1);
	}
}

int take_wp(char *str)
{
	if (*str != *(str + 1) || *str == '*')
		return (add_item(str, str + 1, check_flag(str, 1)), 1);
	else if (*str = *(str + 1))
		return (add_item(str, str + 2, check_flag(str, 2)), 2);
}

int	check_flag(char *str, int q)
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
}

int	take_colon(char *str)
{
	int	i = 0;
	if (*str == '\"')
		return (take_dquote(str));
	add_item(str, str + 1, SQUOTE);
	str++;
	while (str[i] != '\'' && str[i])
		i++;
	if (str [i] == '\'')
	{
		add_item(str, str + i, WORD);
		add_item(str + i, str + i + 1, SQUOTE);
	}
	else if (!str[i])
		unclosed_quote();
	return (i + 1);
}

int	take_dquote(char *str)
{
	int i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (i != 0)
			{
				add_item(str, str + i, WORD);
				take_qvar(str);
			}
			else
				take_qvar(str);
		}
	}
}

int	take_qvar(char *str)
{
	char *comp = "!@#$*+-";
	int i = 0, j = 0;
	while (str[i])
	{
		while (comp[++j])
			if (str[i] == comp[j])
				return (add_item(str, str + i, VAR),i + 1);
	}

} 