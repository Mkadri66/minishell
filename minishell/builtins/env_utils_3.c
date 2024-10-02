/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momillio <momillio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 14:53:46 by mkadri            #+#    #+#             */
/*   Updated: 2024/10/02 12:35:40 by momillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

int	is_shlvl_present(t_env_node **env_list)
{
	t_env_node	*current;

	current = *env_list;
	while (current != NULL)
	{
		if (ft_strncmp(current->env_name, "SHLVL=", 6) == 0)
			return (0);
		current = current->next;
	}
	return (1);
}

bool	valid_num_content(char *str)
{
	while (*str)
	{
		if (ft_isalpha(*str))
			return (false);
		str++;
	}
	return (true);
}

int	increase_lvl(t_env_node **env_list)
{
	t_env_node	*current;
	int			shlvl;
	char		*shlvl_char;

	current = *env_list;
	while (current != NULL)
	{
		if (ft_strncmp(current->env_name, "SHLVL=", 6) == 0)
		{
			if (valid_num_content (current->env_name + 6))
			{
				shlvl = ft_atoi (&current->env_name[6]) + 1;
				shlvl_char = ft_itoa (shlvl);
				current->env_name[6] = shlvl_char[0];
			}
			else
				current->env_name = ft_strdup ("SHLVL=1");
		}
		current = current->next;
	}
	free (shlvl_char);
	return (1);
}

void	increase_shell_lvl(t_env_node **env_list)
{
	if (is_shlvl_present(env_list) == 0)
		increase_lvl(env_list);
	else
		add_env_node(env_list, "SHLVL=0");
}
