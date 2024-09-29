/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:10:08 by momillio          #+#    #+#             */
/*   Updated: 2024/09/27 15:48:55 by momillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*static int	copy_env(t_data *data, char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	data->env = malloc (sizeof (char *) * (i +1));
	if (!data->env)
	{
		free (data);
		return (0);
	}
	i = -1;
	while (env[++i])
	{
		data->env[i] = ft_strdup (env[i]);
		if (!data->env[i])
		{
			while (i >= 0)
				free (data->env[i--]);
			free (data->env);
			free (data);
			return (0);
		}
	}
	data->env[i] = '\0';
	return (1);
}*/

/*void	increase_shell_lvl(t_data *data)
{
	int		i;
	int		current_lvl;
	char	new_level;

	i = -1;
	while (data->env[++i])
	{
		if (ft_strncmp (data->env[i], "SHLVL=", 6) == 0)
		{
			current_lvl = ft_atoi (&data->env[i][6]) + 1;
			new_level = *ft_itoa (current_lvl);
			data->env[i][6] = new_level;
		}
	}
}*/

int	init_data(t_data **data, t_env_node **env_list, char **env, int argc)
{
	if (argc > 1)
	{
		printf ("The program doesn't require argument\n");
		return (0);
	}
	*data = malloc (sizeof (t_data));
	if (!data)
		return (0);
	copy_env_to_list (env_list, env);
//	if (!copy_env (*data, env))
//		return (0);
//	increase_shell_lvl (*data);
//	print_env (data);
	(*data)->env_list = env_list;
	(*data)->new_input = NULL;
	(*data)->nb_cmd = 0;
	(*data)->stdin_cpy = dup (STDIN_FILENO);
	(*data)->stdout_cpy = dup (STDOUT_FILENO);
	(*data)->d_quote = false;
	(*data)->s_quote = false;
	return (1);
}
