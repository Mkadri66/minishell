/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkadri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:29:59 by mkadri            #+#    #+#             */
/*   Updated: 2024/09/23 11:41:43 by mkadri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	run_next_node_left(t_pipe *pipe_node, int *fd, t_data *data, t_env_node **env_list)
{
	t_redir *rnode;

	if (pipe_node->left->type == REDIR)
	{
		rnode = (t_redir *) pipe_node->left;
		if (rnode->r_type == HEREDOC)
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
	exit(g_exit_status);
}
void	run_next_node_right(t_pipe *pipe_node, int *fd, t_data *data, t_env_node **env_list)
{
	t_redir	*rnode;

	if (pipe_node->right->type == REDIR)
	{
		rnode = (t_redir *) pipe_node->right;
		if (rnode->r_type == HEREDOC)
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
	run_tree(pipe_node->left, data, env_list);
	exit(g_exit_status);
}
int	wait_for_process(pid_t pid1)
{
	int	status;
	int	return_status;

	status = 0;
	return_status = 0;
	waitpid(pid1, &status, 0);
	if (WIFEXITED(status))
		return_status = WEXITSTATUS(status);
	return (return_status);
}

int	is_there_heredoc(t_ast *tree)
{
	t_redir *redir_node;

	if (tree->type == CMD)
		return (1);
	else
	{
		redir_node = (t_redir *)tree;
		while (redir_node->r_type == HEREDOC)
		{
			if (redir_node->cmd->type == CMD)
				return (1);
			redir_node = (t_redir *) redir_node->cmd;
		}
		if (redir_node->r_type == HEREDOC)
			return (0);
	}
	return (1);
}

int    run_pipe(t_ast *tree, t_data *data, t_env_node **env_list)
{
    t_pipe  *pipe_node;
    int     fd[2];
    pid_t   pid1;
    pid_t   pid2;
    int     return_status;

    return_status = 0;
    pipe_node = &tree->content.pipe_node;
    if (pipe(fd) == -1)
        ft_error("pipe");
    pid1 = ft_fork();
    if (pid1 == 0)
        run_next_node_left(pipe_node, fd, data, env_list);
    if (is_there_heredoc(pipe_node->left) == 0 || pipe_node->type == REDIR)
        return_status = wait_for_process(pid1);
    pid2 = ft_fork();
    if (pid2 == 0)
        run_next_node_right(pipe_node, fd, data, env_list);
    close(fd[0]);
    close(fd[1]);
    return_status = wait_for_process(pid1);
    return_status = wait_for_process(pid2);
    return(return_status);
}