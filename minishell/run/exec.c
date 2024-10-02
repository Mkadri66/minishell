/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momillio <momillio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:36:07 by mkadri            #+#    #+#             */
/*   Updated: 2024/10/02 12:19:35 by momillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/run.h"
#include "../includes/builtins.h"
#include "../includes/parsing.h"

char	*get_env_path(t_env_node *env_list)
{
	t_env_node	*current;

	current = env_list;
	while (current)
	{
		if (ft_strncmp(current->env_name, "PATH=", 5) == 0)
			return (current->env_name + 5);
		current = current->next;
	}
	return (NULL);
}

char	*get_path(t_cmd *cmd_node, t_env_node **env_list)
{
	char	**allpaths;
	char	*goodpath;
	char	*subpath;
	char	*paths;
	int		i;

	paths = get_env_path(*env_list);
	if (!paths)
		return (NULL);
	allpaths = ft_split(paths, ':');
	i = -1;
	while (allpaths[++i])
	{
		subpath = ft_strjoin(allpaths[i], "/");
		goodpath = ft_strjoin(subpath, cmd_node->args[0]);
		free(subpath);
		if (access(goodpath, F_OK | X_OK) == 0)
		{
			ft_free_split(allpaths);
			return (goodpath);
		}
		free(goodpath);
	}
	ft_free_split(allpaths);
	return (NULL);
}

int	run_exec(t_ast *tree, t_env_node **env_list, t_data *data)
{
	t_cmd	*cmd_node;
	char	*path;
	char	**env_copy;

	cmd_node = &tree->content.cmd_node;
	if (cmd_node->is_builtin == true)
		run_builtins(cmd_node->args[0], cmd_node->args + 1, env_list);
	else
	{
		path = get_path(cmd_node, env_list);
		if (path == NULL)
			return (free_all (&data, tree, NULL), 127);
		env_copy = copy_env_list_to_array(*env_list);
		if (execve(cmd_node->args[0], cmd_node->args, env_copy) == -1)
		{
			if (execve(path, cmd_node->args, env_copy) == -1)
			{
				free(path);
				ft_free_split(env_copy);
				ft_error(cmd_node->args[0]);
				return (1);
			}
		}
	}
	return (0);
}
