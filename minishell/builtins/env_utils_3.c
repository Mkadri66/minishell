/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momillio <momillio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 14:53:46 by mkadri            #+#    #+#             */
/*   Updated: 2024/09/29 18:02:08 by momillio         ###   ########.fr       */
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
	char		**split_shlvl;
	int			shlvl;
	char		*shlvl_char;

	current = *env_list;
	while (current != NULL)
	{
		if (ft_strncmp(current->env_name, "SHLVL=", 6) == 0)
		{
			split_shlvl = ft_split(current->env_name, '=');
			if (valid_num_content(split_shlvl[1]))
			{
				shlvl = ft_atoi(split_shlvl[1]) + 1;
				shlvl_char = ft_itoa(shlvl);
				current->env_name = ft_strjoin("SHLVL=", shlvl_char);
			}
			else
				current->env_name = "SHLVL=1";
			ft_free_split(split_shlvl);
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
