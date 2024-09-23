/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkadri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:36:07 by mkadri            #+#    #+#             */
/*   Updated: 2024/09/23 11:21:01 by mkadri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int is_env_builtin(t_ast *tree)
{
    t_cmd   *exec_node;
    
    if(tree->type == CMD)
    {
        exec_node = (t_cmd *) tree;
        if (ft_strcmp(exec_node->name, "cd") || ft_strcmp(exec_node->name, "export") || ft_strcmp(exec_node->name, "unset"))
            return (1);
        else
            return (0);
    }
    return (0);
}
void	run_tree(t_ast *tree, t_data *data, t_env_node **env_list)
{
    int return_status;

    if(tree->type == CMD)
        run_exec(tree, env_list);
    else if (tree->type == REDIR)
        run_redir(tree, data, env_list);
    else if (tree->type == PIPE)
		return_status = run_pipe(tree, data, env_list);
	exit (return_status);
}
void    fork_and_exec(t_ast *tree, t_data *data, t_env_node **env_list)
{
    pid_t   pid;
    int     status;

    pid = 0;
    pid = ft_fork();
	signal(SIGINT, signal_routine_child);
	if (pid == 0)
		run_tree(tree, data, env_list);
	else if (pid > 0)
	{
		while (waitpid(pid, &status, 0) == -1)
			;
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
	}
}

void    check_builtin_and_run(t_ast *tree, t_data *data, t_env_node **env_list)
{
    t_cmd   *exec_node;
    
    if (is_env_builtin(tree) == 1 && data->nb_cmd == 1)
    {
        exec_node = (t_cmd *) tree;
        run_builtins(exec_node->name, exec_node->args, env_list);
        g_exit_status = 0;
    } 
    else
        fork_and_exec(tree, data, env_list);
    return ;
}