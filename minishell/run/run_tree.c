/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momillio <momillio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:36:07 by mkadri            #+#    #+#             */
/*   Updated: 2024/10/02 11:02:30 by momillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/run.h"
#include "../includes/builtins.h"
#include "../includes/parsing.h"

int	ft_fork(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	return (pid);
}

int	is_env_builtin(t_ast *tree)
{
	t_cmd	*exec_node;

	if (tree->type == CMD)
	{
		exec_node = &tree->content.cmd_node;
		if (ft_strcmp(exec_node->args[0], "cd") == 0
			|| ft_strcmp(exec_node->args[0], "export") == 0
			|| ft_strcmp(exec_node->args[0], "unset") == 0)
			return (1);
		else
			return (0);
	}
	return (0);
}

void	run_tree(t_ast *tree, t_data *data, t_env_node **env_list)
{
	int	return_status;

	return_status = 0;
	if (tree->type == CMD)
		run_exec(tree, env_list);
	else if (tree->type == REDIR)
		run_redir(tree, data, env_list);
	else if (tree->type == PIPE)
		return_status = run_pipe(tree, data, env_list);
//	free_all (&data, tree, NULL);
//	exit (return_status);
}

void	fork_and_exec(t_ast *tree, t_data *data, t_env_node **env_list)
{
	pid_t	pid;
	int		status;

	pid = 0;
	pid = ft_fork();
	if (pid == 0)
	{
		run_tree(tree, data, env_list);
		free_all (&data, tree, NULL);
	}
	else if (pid > 0)
	{
		while (waitpid(pid, &status, 0) == -1)
			;
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
	}
}

void	check_builtin_and_run(t_ast *tree, t_data *data, t_env_node **env_list)
{
	t_cmd	*exec_node;

	if (is_env_builtin(tree) == 1 && data->nb_cmd == 1)
	{
		exec_node = &tree->content.cmd_node;
		run_builtins(exec_node->args[0], exec_node->args + 1, env_list);
		g_exit_status = 0;
	}
	else
	{
		fork_and_exec(tree, data, env_list);
	}
	return ;
}
