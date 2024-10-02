/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momillio <momillio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:29:59 by mkadri            #+#    #+#             */
/*   Updated: 2024/10/02 12:32:52 by momillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/run.h"
#include "../includes/parsing.h"

void	run_next_node_left(t_pipe *pipe_node, int *fd,
		t_data *data, t_env_node **env_list)
{
	t_redir	*rnode;

	if (pipe_node->left->type == REDIR)
	{
		rnode = (t_redir *) pipe_node->left;
		if (rnode->type == HEREDOC)
		{
			dup2(data->stdin_cpy, STDIN_FILENO);
			ft_heredoc(rnode);
			pipe_node->left = rnode->cmd;
		}
	}
	close(fd[0]);
	dup2(fd[1], 1);
	close(fd[1]);
	run_tree(pipe_node->left, data, env_list);
}

void	run_next_node_right(t_pipe *pipe_node,
		int *fd, t_data *data, t_env_node **env_list)
{
	t_redir	*rnode;

	if (pipe_node->right->type == REDIR)
	{
		rnode = (t_redir *) pipe_node->right;
		if (rnode->type == HEREDOC)
		{
			dup2(data->stdin_cpy, STDIN_FILENO);
			ft_heredoc(rnode);
			pipe_node->right = rnode->cmd;
		}
		else
			dup_right(fd);
	}
	else
		dup_right(fd);
	run_tree(pipe_node->right, data, env_list);
}

int	is_there_heredoc(t_ast *tree)
{
	t_redir	*redir_node;

	if (tree->type == CMD)
		return (1);
	else
	{
		redir_node = (t_redir *)tree;
		while (redir_node->type == HEREDOC)
		{
			if (redir_node->cmd->type == CMD)
				return (1);
			redir_node = (t_redir *) redir_node->cmd;
		}
		if (redir_node->type == HEREDOC)
			return (0);
	}
	return (1);
}

void	run_pipe_2(t_ast *tree, t_data *data, int *return_status, int *fd)
{
	t_pipe	*pipe_node;
	pid_t	pid2;

	pipe_node = &tree->content.pipe_node;
	pid2 = ft_fork();
	if (pid2 == 0)
	{
		run_next_node_right(pipe_node, fd, data, data->env_list);
		free_all (&data, tree, NULL);
	}
	close(fd[0]);
	close(fd[1]);
	*return_status = wait_for_process(pid2);
}

int	run_pipe(t_ast *tree, t_data *data, t_env_node **env_list)
{
	t_pipe	*pipe_node;
	int		fd[2];
	pid_t	pid1;
	int		return_status;

	return_status = 0;
	pipe_node = &tree->content.pipe_node;
	if (pipe(fd) == -1)
		ft_error("pipe");
	pid1 = ft_fork();
	if (pid1 == 0)
	{
		run_next_node_left(pipe_node, fd, data, env_list);
		free_all (&data, tree, NULL);
	}
	if (is_there_heredoc(pipe_node->left) == 0 || pipe_node->type == REDIR)
		return_status = wait_for_process(pid1);
	run_pipe_2 (tree, data, &return_status, fd);
	return (return_status);
}
