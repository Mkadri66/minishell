/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momillio <momillio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:51:07 by mkadri            #+#    #+#             */
/*   Updated: 2024/10/02 10:29:38 by momillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"
#include "../includes/parsing.h"

int	is_only_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	is_input_exit(char *input, t_data *data)
{
	int		nb_args;
	char	**input_split;

	input_split = ft_split(input, ' ');
	if (!input_split)
		return (1);
	if (ft_strcmp(input_split[0], "exit") == 0)
	{
		nb_args = count_args(input_split + 1);
		if (nb_args >= 2 && !is_only_digits(input_split[1]))
		{
			printf("exit : error; too many arguments\n");
			ft_free_split(input_split);
			return (g_exit_status = 1, 1);
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

void	ft_exit(char **input, t_data *data)
{
	printf ("exit\n");
	free (*input);
	free_env_list (data->env_list);
	free (data);
	exit (0);
}
