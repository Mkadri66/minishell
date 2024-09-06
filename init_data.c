/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:10:08 by momillio          #+#    #+#             */
/*   Updated: 2024/09/05 17:04:21 by momillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_env(t_data *data, char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	data->env = malloc (sizeof (char *) * (i +1));
	if (!data->env)
		return ; // free data
	i = -1;
	while (env[++i])
	{
		data->env[i] = ft_strdup (env[i]);
		if (!data->env[i])
			return ; // free data.env, data et data.env[i] déjà fait
	}
	data->env[i] = '\0';
}
void	increase_shell_lvl(t_data *data)
{
	int	i;
	int	current_lvl;
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
}

int	init_data(t_data *data, char **env)
{
	data = malloc (sizeof (t_data));
	if (!data)
		return (0);
	copy_env (data, env);
	increase_shell_lvl (data);
	//copy STDIN
	//copy STDOUT
	data->token = NULL;
	data->tree = NULL;
	return (1);
}