/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 17:38:05 by ajaidi            #+#    #+#             */
/*   Updated: 2022/06/25 19:11:25 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	herdoc(char *del)
{
	int		fd[2];
	char	*line;

	pipe(fd);
	while (1)
	{
		line = readline("herdoc >");
		if (!ft_memcmp(del, line, ft_strlen(del)))
			break ;
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
	}
	close(fd[1]);
	return (fd[0]);
}

t_tree	*get_redir(t_tree *next, char *filename, int redtype)
{
	t_redir	*node;

	node = ft_malloc(&g.adrs, sizeof(t_redir));
	node->type = REDIR;
	node->next = next;
	node->src = STDIN_FILENO;
	node->mode = O_RDONLY;
	if (redtype == GREAT || redtype == DGREAT)
	{
		node->src = STDOUT_FILENO;
		if (redtype == GREAT)
			node->mode = O_CREAT | O_WRONLY | O_TRUNC;
		else
			node->mode = O_CREAT | O_WRONLY | O_APPEND;
	}
	if (redtype == DLESS)
		node->dst = herdoc(filename);
	node->filename = filename;
	return ((t_tree *)node);
}

t_tree	*get_rdr(t_token **head, t_tree *n)
{
	t_tree		*next;
	t_command	**root;
	t_cmd		*next2;
	t_tree		*ret;

	ret = NULL;
	if (!n)
	{
		next = get_cmdlist(head);
		next2 = (t_cmd *)next;
	}
	else
		next = n;
	while (*head && (*head)->type >= 1 && (*head)->type <= 4)
	{
		*head = get_right(*head);
		ret = get_redir(next, (*head)->str, get_left(*head)->type);
		next = ret;
		*head = get_right(*head);
		while (*head && ((*head)->type == VAR || (*head)->type == WORD))
		{
			append_in_cmdend(&next2->next, (*head)->str, (*head)->type);
			*head = get_right(*head);
		}
	}
	if (ret)
		return (ret);
	else
		return (next);
}
