/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 14:53:46 by mkadri            #+#    #+#             */
/*   Updated: 2024/09/27 11:29:15 by momillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	**split_and_validate(char *env_var)
{
	char	**split_var;

	split_var = ft_split(env_var, '=');
	if (!split_var || !split_var[0] || !split_var[1])
	{
		ft_free_split(split_var);
		return (NULL);
	}
	return (split_var);
}

int	replace_env_var(t_env_node *current, char **split_var)
{
	char	**existing_var;

	existing_var = ft_split(current->env_name, '=');
	if (ft_strcmp(existing_var[0], split_var[0]) == 0)
	{
		free(current->env_name);
		current->env_name = ft_strjoin(split_var[0], "=");
		current->env_name = ft_strjoin(current->env_name, split_var[1]);
		ft_free_split(existing_var);
		return (1);
	}
	ft_free_split(existing_var);
	return (0);
}

void	update_env_list(char *env_var, t_env_node **env_list)
{
	t_env_node	*current;
	char		**split_var;

	split_var = split_and_validate(env_var);
	if (!env_var || !(split_var))
		return ;
	current = *env_list;
	while (current != NULL)
	{
		if (replace_env_var(current, split_var))
		{
			ft_free_split(split_var);
			return ;
		}
		current = current->next;
	}
	ft_free_split(split_var);
}
