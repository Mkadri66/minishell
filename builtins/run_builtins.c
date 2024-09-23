/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkadri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:36:07 by mkadri            #+#    #+#             */
/*   Updated: 2024/09/23 12:36:01 by mkadri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	run_builtins(char *cmd, char **args, t_env_node **env_list)
{
	if (ft_strcmp(cmd, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(cmd, "env") == 0)
		ft_env(*env_list);
	else if (ft_strcmp(cmd, "export") == 0)
		ft_export(args, env_list);
	else if (ft_strcmp(cmd, "unset") == 0)
		ft_unset(args, env_list);
	else if (ft_strcmp(cmd, "cd") == 0)
		ft_cd(args, env_list);
	else if (ft_strcmp(cmd, "echo") == 0)
		ft_echo(args, env_list);
	else if (ft_strcmp(cmd, "exit") == 0)
		ft_exit(args, env_list);
	else
		ft_strcmp(cmd, "");
}
