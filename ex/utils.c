/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 16:44:59 by ajaidi            #+#    #+#             */
/*   Updated: 2022/07/07 23:55:01 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
}

int	ft_atoi(const char *str)
{
	int	i;
	int	s;
	int	r;

	i = 0;
	s = 1;
	r = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		r *= 10;
		r += str[i] - 48;
		i++;
	}
	return (r * s);
}

int	cmdlstsize(t_command *root)
{
	int	i;

	i = 0;
	while (root)
	{
		i++;
		root = root->next;
	}
	return (i);
}

char	*ft_strdup(char *s1)
{
	int		i;
	char	*ptr;

	i = 0;
	while (s1[i])
		i++;
	ptr = (char *)ft_malloc(&g_global.adrs, i * sizeof(char) + 1, 1);
	if (!ptr)
		return (NULL);
	i = -1;
	while (s1[++i])
		ptr[i] = s1[i];
	ptr[i] = 0;
	return (ptr);
}

char	**transfer(t_command *root)
{
	int		i;
	int		n;
	char	**argv;

	i = -1;
	n = cmdlstsize(root);
	argv = ft_malloc(&g_global.adrs, (n + 1) * sizeof(char *), 1);
	while (root)
	{
		argv[++i] = root->content;
		root = root->next;
	}
	argv[n] = NULL;
	return (argv);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s2[i] && (s1[i] == s2[i]) && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}