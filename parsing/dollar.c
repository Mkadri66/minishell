/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:01:10 by momillio          #+#    #+#             */
/*   Updated: 2024/09/16 14:08:04 by momillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*copy_env(t_data *data, t_dollar *dollar)
{
	int	i;

	i = 0;
	while (data->env[dollar->index][i] != '=')
		i++;
	while (data->env[dollar->index][++i])
		data->new_input = strjoin_char (data->new_input, data->env[dollar->index][i]);
//	printf ("$ = %s\n", str);
	return (data->new_input);
}

bool	search_env(t_dollar *dollar, t_data *data)
{
	int	i;

	i = -1;
	print_env (data);
	while (data->env[++i])
	{
		if (strncmp (dollar->name, data->env[i], dollar->len) == 0
			&& data->env[i][dollar->len] == '=')
			{
				dollar->index = i;
//				printf ("dollar index = %d\n", dollar->index);
				return (true);
			}
	}
	return (false);
}

char	*get_exit_status(char *str)
{
	int	i;
	char	*exit_status;

	i = -1;
	exit_status = ft_itoa (g_exit_status);
	if (!exit_status)
		return (NULL);
	while (exit_status[++i])
		str = strjoin_char (str, exit_status[i]);
	free (exit_status);
	return (str);
}

void	check_name(t_dollar *dollar, char **input)
{
	int	i;

	i = 0;
	if ((*input)[i] == '_' || ((*input)[i] >= 'A' && (*input)[i] <= 'Z')
						|| ((*input)[i] >= 'a' && (*input)[i] <= 'z'))
		i++;
	else
		return ;
	while ((*input)[i] && ((*input)[i] == '_' || ((*input)[i] >= '0' && (*input)[i] <= '9')
										|| ((*input)[i] >= 'A' && (*input)[i] <= 'Z')
										|| ((*input)[i] >= 'a' && (*input)[i] <= 'z')))
		i++;
//	printf ("dollar len = %d  str = %s\n", i, *input);
	dollar->len = i;
	dollar->name = malloc (sizeof(char) * (dollar->len + 1));
	if (!dollar->name)
		return ;
	i = -1;
	while (++i < dollar->len)
	{
		dollar->name[i] = **input;
		(*input)++;
	}
//	printf ("input = %s\n", *input);
	dollar->name[i] = '\0';
}

char	*replace_dollar(char **input, t_data *data)
{
	t_dollar	*dollar;
	
	(*input)++;
	if (**input == '?')
	{
		data->new_input = get_exit_status (data->new_input);
		(**input)++;
	}
	else
	{
		dollar = malloc (sizeof (t_dollar));
		if (!dollar)
			return (NULL);
		ft_memset (dollar, 0, sizeof(t_dollar));
		check_name (dollar, input);
		if (search_env (dollar, data))
			data->new_input = copy_env (data, dollar);
		free (dollar->name);
		free (dollar);
	}
	return (data->new_input);
}
