/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momillio <momillio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:51:07 by mkadri            #+#    #+#             */
/*   Updated: 2024/10/02 11:50:44 by momillio         ###   ########.fr       */
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

t_env_node	*add_env_node_cd(t_env_node **head, char *env_name)
{
	t_env_node	*new_node;

	new_node = (t_env_node *) malloc(sizeof(t_env_node));
	if (!new_node)
	{
		free (env_name);
		perror("Failed to allocate memory");
		return (NULL);
	}
	new_node->env_name = ft_strdup(env_name);
	if (!new_node->env_name)
	{
		free (env_name);
		free(new_node);
		perror("Failed to copy environment variable");
		return (NULL);
	}
	new_node->next = *head;
	new_node->prev = NULL;
	if (*head != NULL)
		(*head)->prev = new_node;
	*head = new_node;
	free (env_name);
	return (new_node);
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
			add_env_node_cd(env_list, ft_strjoin("OLDPWD=", old_dir));
	}
	else
		printf("Path not found\n");
	getcwd(current_dir, sizeof(current_dir));
	update_env_list(ft_strjoin("PWD=", current_dir), env_list);
}
