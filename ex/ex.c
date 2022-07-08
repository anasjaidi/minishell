/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 21:26:50 by ajaidi            #+#    #+#             */
/*   Updated: 2022/07/08 01:27:47 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <string.h>


void	ex_pipe(t_wp *root)
{
	int pid;
	int status;
	int pids[2];
	int	fd[0];
	if (pipe(fd) < 0)
		return ;
	pids[0] = fork();
	if (!pids[0])
	{
		close(1);
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		cast_node(root->left);
		the_exit(g_global.status);
	}
	pids[1] = fork();
	if (!pids[1])
	{
		close(0);
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
		cast_node(root->right);
		the_exit(g_global.status);
	}
	close(fd[0]);
	close(fd[1]);
	pid = wait(&status);
	pid = wait(&status);
}

void	ex_redir(t_redir *root)
{
	int fd = open(root->filename, root->mode, S_IRUSR | S_IWUSR);
	int pid = fork();
	int status;
	if (!pid)
	{
		if (root->redtype == GREAT || root->redtype == DGREAT)
			dup2(fd, 1);
		else if (root->redtype == LESS)
			dup2(fd, 0);
		else
			dup2(root->dst , 0);
		cast_node(root->next);
		exit(g_global.status);
	}
	waitpid(pid, &status, 0);
	g_global.status = getst(status);
	
}

void	cast_node(t_tree *root)
{
	if (root->type == SUB)
		cast_node(((t_sub *)root)->next);
	else if (root->type == CMD)
		ex_cmd((t_cmd *)root);
	if (root->type == REDIR)
		ex_redir((t_redir *)root);
	else if (root->type == T_AND)
	{
		cast_node(((t_wp*)root)->left);
		if (!g_global.status)
			cast_node(((t_wp*)root)->right);
	}
	else if (root->type == T_OR)
	{
		cast_node(((t_wp*)root)->left);
		if (g_global.status)
			cast_node(((t_wp*)root)->right);
	}
	else if (root->type >= T_PIPE)	
		ex_pipe(((t_wp*)root));
}

void	delete_node_commnd(t_command **root, t_command *deleted)
{
	t_command	*tmp;

	if (deleted == *root)
		*root = deleted->next;
	else if (!deleted->next)
	{
		t_command *last;
		last = *root;
		while (last->next->next)
			last = last->next;
		last->next = NULL;
	}
	else
	{
		t_command *deletedprev;
		deletedprev = *root;
		while (deletedprev->next != deleted)
			deletedprev = deletedprev->next;
		deletedprev->next = deleted->next;
	}
}

void	get_wild_value(t_command **root, t_command *node)
{
	DIR *dir = opendir(".");
	struct dirent	*item;
	t_command *head = NULL;
	
	item = readdir(dir);
	while (item)
	{
		if (item->d_name[0] != '.')
			append_in_cmdend(&head, item->d_name , 5);
		item = readdir(dir);
	}
	if (node == *root)
	{
		t_command *last;
		last = head;
		while (last->next)
			last = last->next;
		last->next = *root;
		*root = head;
	}
	else
	{
		t_command *next;
		next = node->next;
		t_command *last;
		last = head;
		while (last->next)
			last = last->next;
		last->next = next;
		node->next = head;
	}
}

void 	check_token_type(t_command **root, t_command *node)
{
	if (node->type == WILD)
	{
		get_wild_value(root, node);
		delete_node_commnd(root, node);
	}
	else  if (node->type == TILD)
		node->content = get_env_value("HOME");
	else if (node->type == VAR && !ft_strcmp(node->content, "$?"))
		node->content = ft_itoa(g_global.status);
	else if (node->type == VAR && !ft_strcmp(node->content, "$$"))
		node->content = ft_itoa(getpid());
	else if (node->type == VAR)
		node->content = get_env_value(node->content + 1);
}

void	expend_tokens(t_command **root)
{
	if (!*root)
		return;
	t_command	*tmp;

	tmp = *root;
	while (tmp)
	{
		check_token_type(root, tmp);
		tmp = tmp->next;
	}
}

bool	check_builtin(char **argv)
{
	if (!ft_strcmp(*argv , "echo"))
		return (ft_echo(argv), true);
	else if (!ft_strcmp(*argv , "unset"))
		return (ft_unset(argv), true);
	else if (!ft_strcmp(*argv , "cd"))
		return (ft_cd(argv), true);
	else if (!ft_strcmp(*argv , "exit"))
		return (ft_exit(argv), true);
	else if (!ft_strcmp(*argv , "export"))
		return (ft_export(argv), true);
	else if (!ft_strcmp(*argv , "pwd"))
		return (ft_pwd(1), true);
	else if (!ft_strcmp(*argv , "env"))
		return (ft_env(1), true);
	return (false);
}

int find_path(char **argv)
{
	char	*path;
	char	**spl;
	char	*rtn = NULL;

	path = get_env_value("PATH");
	if (!path)
		return 0;
	spl = ft_split(path, ':');
	if (*spl == NULL)
		return 0;
	while (*spl)
	{
		*spl = ft_strjoin(*spl, "/");
		if (!access(ft_strjoin(*spl, *argv), 0))
			return (*argv = ft_strjoin(*spl, *argv), 1);
		spl++;
	}
	return (0);
}

int	envlstsize(t_env *root)
{
	int i;

	i = 0;
	while (root)
	{
		i++;
		root = root->next;
	}
	return (i);
}

char	**transfer_env(t_env *env)
{
	int i = -1;
	int n = envlstsize(env);
	char	*key;
	char **argv = ft_malloc(&g_global.adrs, (n + 1) * sizeof(char *), 1);
	while (env)
	{
		key = ft_strjoin(env->key, "=");
		argv[++i] =	ft_strjoin(key, env->value);
		env = env->next;
	}
	argv[n] = NULL;
	return (argv);
}

int getst(int status) {
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

void	check_extern(char **argv)
{
	int status;
	find_path(argv);
	int pid = fork();
	g_global.runing = 1;
	if (pid == 0)
	{
		sigreset();
		execve(*argv, argv, transfer_env(g_global.env));
		ft_putstr_fd("execve: ", 1);
		ft_putstr_fd(argv[0], 1);
		ft_putstr_fd(": command not found\n", 1);
		the_exit(127);
	}
	g_global.runing = 0;
	waitpid(pid, &status, 0);
	g_global.status = getst(status);
}

void	ex_cmd(t_cmd *cmd)
{
	expend_tokens(&cmd->next);
	char **argv = transfer(cmd->next);
	if (check_builtin(argv))
		return ;
	check_extern(argv);
}