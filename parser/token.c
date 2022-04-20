/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi < ajaidi@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 16:33:39 by ajaidi            #+#    #+#             */
/*   Updated: 2022/04/20 16:05:15 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	token(char *str, t_token **root)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i += check_char(str + i, root);
	}
	
}

int check_char(char *str, t_token **root)
{
	if (*str == '$')
		return (take_var(str, root));
	else if (*str == 60 || *str == 62)
		return (take_less_more(str, root));
	else if (*str == '|' || *str == '*' || *str == '&')
		return (take_wp(str, root));
	else if (*str == '~')
		return (add_item(str, str + 1, TILD, root), 1);
	else if (*str == '\'' || *str == '\"')
		return (take_colon(str, root));
	else if (*str >= 9 && *str <= 13 || (*str == 32))
		return (take_space(str, root));
	else
		return (take_word(str, root));
	return (0);
}
int	take_word(char *str, t_token **root)
{
	int i = -1;
	int j = -1;
	char	*comp = "&|\'\"$*<>~ \t\r\f\v\n";
	while (str[++i])
	{
		j = -1;
		while (comp[++j])
			if (str[i] == comp[j])
				return (add_item(str, str + i, WORD, root),i);
	}
	return (add_item(str, str + i, WORD, root),i);
}

int	take_space(char *str, t_token **root)
{
	int i = 0;
	while (str[i] >= 9 && str[i] <= 13 || str[i] == 32)
		i++;
	add_item(str, str + i, WSPACE, root);
	return (i);
}

int take_var(char *str, t_token **root)
{
	int i = 0;
	int j = -1;
	char	*comp = "&|\'\"$*<>~ \t\r\f\v\n";
	while (str[++i])
	{
		j = -1;
		while (comp[++j])
			if (str[i] == comp[j])
				return (add_item(str, str + i, VAR, root),i);
	}
	return (add_item(str, str + i, VAR, root),i);
}

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

int take_wp(char *str, t_token **root)
{
	if (*str != *(str + 1) || *str == '*')
		return (add_item(str, str + 1, check_flag(str, 1), root), 1);
	else if (*str == *(str + 1))
		return (add_item(str, str + 2, check_flag(str, 2), root), 2);
	return (0);
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
	return (0);
}

int	take_colon(char *str, t_token **root)
{
	int	i = 0;
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
	 	return (unclosed_quote(root), i + 1);
	return (i + 2);
}

int	take_dquote(char *str, t_token **root)
{
	int i = 0;
	int last = 0;
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

void	unclosed_quote(t_token **root)
{
	clr_lst(root, *root);
	printf("unclosed quote\n");
	*root = NULL;	
}

int	take_qvar(char *str, t_token **root)
{
	char *comp = "!@#$*+-~./, \t\r\f\v\n\"";
	int i = 0, j = -1;
	while (str[++i])
	{
		j = -1;
		while (comp[++j])
			if (str[i] == comp[j])
				return (add_item(str, str + i, VAR, root),i);
	}
	return (i);
}
int calc_size(char *start, char *end)
{
	int i = 1;
	while (start++ != end)
		i++;
	return (i);
}

void	*add_item(char *start, char *end, int flag, t_token **root)
{
	
	char	*str;
	int		i;
	
	i = -1;
	if (!(str = (char *)malloc(calc_size(start, end))))
		return (NULL);
	while (start != end)
	{
		str[++i] = *(start++);	
	}
	str[++i] = 0;
	append_in_end(root, str, flag);
	return (NULL);
}