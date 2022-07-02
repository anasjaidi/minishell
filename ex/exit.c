/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 16:37:13 by ajaidi            #+#    #+#             */
/*   Updated: 2022/06/30 18:11:02 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int exit_parse(char *str)
{
	int i = -1;
	while (str[++i])
		if (!(str[i] >= 48 && str[i] <= 57))
			exit(255);
	return (atoi(str));
}

int	ex_ps(t_command *cmd)
{
	
	if (cmd->type == VAR)
		return (exit_parse(get_env_value(cmd->content + 1)));
	else if (cmd->type == TILD)
		return (255);
}

int	ft_exit(t_command *cmd)
{
	if (!cmd->next)
		exit(g.status);
	if (cmd->next->next)
		return (ft_putstr_fd("exit: too many arguments\n", 1), g.status = -7, 0);
	else if (cmd->type == WILD)
		if (get_wild_value()[1])
			return (ft_putstr_fd("exit: too many arguments\n", 1), g.status = -7, 0);
	else if (cmd->type == WILD)
		exit(exit_parse(get_wild_value()[0]));
	exit(ex_ps(cmd->next));
}

int	ft_pwd(int fd)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		ft_putstr_fd(pwd, fd);
		ft_putchar_fd('\n', fd);
		free(pwd);
		g.status = 0;
	}
	else
		g.status = -1;
}

