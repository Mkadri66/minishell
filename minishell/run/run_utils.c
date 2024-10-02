/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momillio <momillio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:36:07 by mkadri            #+#    #+#             */
/*   Updated: 2024/10/02 10:27:10 by momillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/run.h"
#include "../includes/builtins.h"

int	get_env_list_size(t_env_node *env_list)
{
	int			size;
	t_env_node	*current;

	size = 0;
	current = env_list;
	while (current != NULL)
	{
		size++;
		current = current->next;
	}
	return (size);
}

char	*get_env_value(t_env_node *env_list, const char *var_name)
{
	t_env_node	*current;

	current = env_list;
	while (current != NULL)
	{
		if (ft_strncmp(current->env_name, var_name, ft_strlen(var_name)) == 0
			&& current->env_name[strlen(var_name)] == '=')
			return (current->env_name + ft_strlen(var_name) + 1);
		current = current->next;
	}
	return (NULL);
}

int	fill_env_copy(t_env_node *env_list, char **env_copy)
{
	int			i;
	t_env_node	*current;

	i = 0;
	current = env_list;
	while (current)
	{
		env_copy[i] = ft_strdup(current->env_name);
		if (!env_copy[i])
		{
			perror("Failed to duplicate environment variable");
			return (0);
		}
		current = current->next;
		i++;
	}
	env_copy[i] = NULL;
	return (1);
}

char	**allocate_env_copy(int size)
{
	char	**env_copy;

	env_copy = malloc((size + 1) * sizeof(char *));
	if (!env_copy)
	{
		perror("Failed to allocate memory for env_copy");
		return (NULL);
	}
	return (env_copy);
}

char	**copy_env_list_to_array(t_env_node *env_list)
{
	int		size;
	char	**env_copy;

	size = get_env_list_size(env_list);
	env_copy = allocate_env_copy(size);
	if (env_copy == NULL)
		return (NULL);
	if (!fill_env_copy(env_list, env_copy))
	{
		ft_free_split(env_copy);
		return (NULL);
	}
	return (env_copy);
}
