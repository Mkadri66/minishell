/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkadri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:45:54 by mkadri            #+#    #+#             */
/*   Updated: 2024/09/27 15:59:33 by mkadri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_empty_quotes(char *str)
{
	char	quote;

	if (is_quotes(*str))
	{
		quote = *str;
		str++;
		if (*str == quote)
			return (true);
	}
	return (false);
}

int	count_args(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

void	ft_free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int	is_in_list(char *var, t_env_node **env_list)
{
	char		**var_name_input;
	char		**var_name_env;
	t_env_node	*current;

	var_name_input = ft_split(var, '=');
	current = *env_list;
	while (current != NULL)
	{
		var_name_env = ft_split(current->env_name, '=');
		if (ft_strcmp(var_name_input[0], var_name_env[0]) == 0)
			return (0);
		ft_free_split(var_name_env);
		current = current->next;
	}
	ft_free_split(var_name_input);
	return (1);
}
