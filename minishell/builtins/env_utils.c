/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:20:09 by mkadri            #+#    #+#             */
/*   Updated: 2024/10/01 20:38:19 by momillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

void	print_env_list(t_env_node *head)
{
	t_env_node	*current;

	current = head;
	while (current != NULL)
	{
		printf("%s\n", current->env_name);
		current = current->next;
	}
}

void	copy_env_to_list(t_env_node **head, char **envp)
{
	if (!head || !envp)
		return ;
	while (*envp != NULL)
	{
		if (add_env_node(head, *envp) == NULL)
		{
			free_env_list(head);
			exit(1);
		}
		envp++;
	}
	increase_shell_lvl(head);
}

t_env_node	*add_env_node(t_env_node **head, const char *env_name)
{
	t_env_node	*new_node;

	new_node = (t_env_node *) malloc(sizeof(t_env_node));
	if (!new_node)
	{
		perror("Failed to allocate memory");
		return (NULL);
	}
	new_node->env_name = ft_strdup(env_name);
	if (!new_node->env_name)
	{
		free(new_node);
		perror("Failed to copy environment variable");
		return (NULL);
	}
	new_node->next = *head;
	new_node->prev = NULL;
	if (*head != NULL)
		(*head)->prev = new_node;
	*head = new_node;
	return (new_node);
}

void	remove_env_node(const char *var_name, t_env_node **env_list)
{
	t_env_node	*current;
	char		**split_var;

	if (!env_list || !*env_list || !var_name)
		return ;
	current = *env_list;
	while (current != NULL)
	{
		split_var = ft_split(current->env_name, '=');
		if (ft_strcmp(split_var[0], var_name) == 0)
		{
			if (current->prev == NULL)
				*env_list = current->next;
			else
				current->prev->next = current->next;
			if (current->next != NULL)
				current->next->prev = current->prev;
			free(current->env_name);
			free(current);
			ft_free_split(split_var);
			return ;
		}
		ft_free_split(split_var);
		current = current->next;
	}
}

void	free_env_list(t_env_node **head)
{
	t_env_node	*current;
	t_env_node	*next_node;

	current = *head;
	while (current != NULL)
	{
		next_node = current->next;
		free(current->env_name);
		free(current);
		current = next_node;
	}
}
