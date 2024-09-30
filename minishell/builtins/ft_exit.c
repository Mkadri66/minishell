/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momillio <momillio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:51:07 by mkadri            #+#    #+#             */
/*   Updated: 2024/09/30 17:24:24 by momillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"
# include "../includes/parsing.h"

int	is_input_exit(char *input, t_data *data)
{
	int	i;
	char **input_split;
	
	i = 0;
	input_split = ft_split(input, ' ');
	if (!input_split)
		return (1);
	if (ft_strcmp(input_split[0], "exit") == 0)
	{
		while (input_split[i])
			i++;
		if(i > 2)
		{
			printf("exit : error; too many arguments\n");
			ft_free_split(input_split);
			return(g_exit_status = 1, 1);
		}
		else
		{
			printf("exit\n");
			ft_exit(input_split, data);
			exit (0);
		}
	}
	ft_free_split(input_split);
	return (1);
}


int	arg_is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if(!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

void	ft_exit(char **input, t_data *data)
{
	printf ("ft_exit\n");
	free (*input);
	free_env_list (data->env_list);
	free (data);
	exit (0);
}
