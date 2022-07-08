/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excommand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 18:13:01 by ajaidi            #+#    #+#             */
/*   Updated: 2022/07/08 22:26:10 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_extern(char **argv)
{
	int	pid;
	int	status;

	g_global.runing = 1;
	find_path(argv);
	pid = fork();
	if (pid == 0)
	{
		sigreset();
		execve(*argv, argv, transfer_env(g_global.env));
		ft_putstr_fd("execve: ", 1);
		ft_putstr_fd(argv[0], 1);
		ft_putstr_fd(": command not found\n", 1);
		the_exit(127);
	}
	waitpid(pid, &status, 0);
	g_global.status = getst(status);
	g_global.runing = 0;
}

void	ex_cmd(t_cmd *cmd)
{
	char	**argv;

	expend_tokens(&cmd->next);
	argv = transfer(cmd->next);
	if (check_builtin(argv))
		return ;
	check_extern(argv);
}

int	find_path(char **argv)
{
	char	*path;
	char	**spl;

	path = get_env_value("PATH");
	if (!path)
		return (0);
	spl = ft_split(path, ':');
	if (*spl == NULL)
		return (0);
	while (*spl)
	{
		*spl = ft_strjoin(*spl, "/");
		if (!access(ft_strjoin(*spl, *argv), 0))
			return (*argv = ft_strjoin(*spl, *argv), 1);
		spl++;
	}
	return (0);
}

bool	check_builtin(char **argv)
{
	if (!ft_strcmp(*argv, "echo"))
		return (ft_echo(argv), true);
	else if (!ft_strcmp(*argv, "unset"))
		return (ft_unset(argv), true);
	else if (!ft_strcmp(*argv, "cd"))
		return (ft_cd(argv), true);
	else if (!ft_strcmp(*argv, "exit"))
		return (ft_exit(argv), true);
	else if (!ft_strcmp(*argv, "export"))
		return (ft_export(argv), true);
	else if (!ft_strcmp(*argv, "pwd"))
		return (ft_pwd(1), true);
	else if (!ft_strcmp(*argv, "env"))
		return (ft_env(), true);
	return (false);
}
