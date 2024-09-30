/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momillio <momillio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:01:10 by momillio          #+#    #+#             */
/*   Updated: 2024/09/30 15:49:34 by momillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"
# include "../includes/builtins.h"

/*
	Copy the value of the environnement variable after the =.
*/

char	*copy_env(t_data *data, t_dollar *dollar)
{
	int	i;
	t_env_node	*current;

	i = -1;
	current = (*data->env_list);
	while (++i < dollar->index)
		current = current->next;
	i = 0;
	while (current->env_name[i] != '=')
		i++;
	while (current->env_name[++i])
		data->new_input = strjoin_char (data->new_input, \
			current->env_name[i]);
//	printf ("$ = %s\n", data->new_input);
	return (data->new_input);
}

/*
	Search in the copied environnement that the variable exist and store in
	which line it is.
*/

bool	search_env(t_dollar *dollar, t_data *data)
{
	int	i;
	t_env_node	*current;

	i = 0;
	current = (*data->env_list);
//	print_env_list ((*data->env_list));
//	printf ("name = %s len = %d\n", dollar->name, dollar->len);
	while (current != NULL)
	{
//		printf ("current = %s\n", current->env_name);
		if (ft_strncmp (dollar->name, current->env_name, dollar->len) == 0
			&& current->env_name[dollar->len] == '=')
		{
			dollar->index = i;
//				printf ("dollar index = %d\n", dollar->index);
			return (true);
		}
		current = current->next;
		i++;
	}
	return (false);
}
/* 
	Get the exit status stored in the global variable exit_status.
	Change it into char with ft_itoa and store it in a string.
*/

char	*get_exit_status(char *str)
{
	int		i;
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

/* 
	Check if the name of the env variable is correct : only letters lowercase
	or uppercase, numbers or '_'.
	If its good, it will store the name in the dollar structure.
*/

void	check_name(t_dollar *dollar, char **input)
{
	int	i;

	i = 0;
	if ((*input)[i] == '_' || ((*input)[i] >= 'A' && (*input)[i] <= 'Z')
						|| ((*input)[i] >= 'a' && (*input)[i] <= 'z'))
		i++;
	else
		return ;
	while ((*input)[i] && ((*input)[i] == '_'
								|| ((*input)[i] >= '0' && (*input)[i] <= '9')
								|| ((*input)[i] >= 'A' && (*input)[i] <= 'Z')
								|| ((*input)[i] >= 'a' && (*input)[i] <= 'z')))
		i++;
	printf ("dollar len = %d  str = %s\n", i, *input);
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

/*
	Replace the $ in the input.
	If its a $? , it will get the exit status of the last cmd and store it.
	Else it will check that the name of the env variable is correct.
	It will search the env to see if the variable is in it.
	If its in it, a copy is made in the new input.
*/

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
		if (dollar->name && search_env (dollar, data))
			data->new_input = copy_env (data, dollar);
		free (dollar->name);
		free (dollar);
	}
	return (data->new_input);
}
