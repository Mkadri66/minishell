/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkadri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:51:07 by mkadri            #+#    #+#             */
/*   Updated: 2024/10/01 20:52:20 by mkadri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

char	*find_home_path(t_env_node *env_list)
{
	t_env_node	*current;
	char		*home_prefix;
	size_t		prefix_len;

	current = env_list;
	home_prefix = "HOME=";
	prefix_len = strlen(home_prefix);
	while (current != NULL)
	{
		if (ft_strncmp(current->env_name, home_prefix, prefix_len) == 0)
			return (current->env_name + prefix_len);
		current = current->next;
	}
	return (NULL);
}

void	ft_cd(char **args, t_env_node **env_list)
{
	char	old_dir[1024];
	char	current_dir[1024];

	getcwd(old_dir, sizeof(old_dir));
	if (!args[0])
	{
		if (find_home_path(*env_list) != NULL)
			chdir(find_home_path(*env_list));
		else
			printf("Home path is not defined\n");
		return ;
	}
	if (chdir(args[0]) == 0)
	{
		if (is_in_list(ft_strjoin("OLDPWD=", old_dir), env_list) == 0)
			update_env_list(ft_strjoin("OLDPWD=", old_dir), env_list);
		else
			add_env_node(env_list, ft_strjoin("OLDPWD=", old_dir));
	}
	else
		printf("Path not found\n");
	getcwd(current_dir, sizeof(current_dir));
	update_env_list(ft_strjoin("PWD=", current_dir), env_list);
}
