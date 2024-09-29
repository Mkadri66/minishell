/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:05:14 by mkadri            #+#    #+#             */
/*   Updated: 2024/09/26 12:21:16 by momillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

int	input_empty(char *input)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if (!is_whitespaces (input[i]))
			return (false);
	}
	return (true);
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;
	char	*input;

	if (!init_data (&data, env))
		return (1);
//    print_env (data);
	while (1)
	{
		input = readline ("Minishell: ");
//      printf ("input = %s\n", input);
		if (!input)
			free_data (data); // free data, data.env
		if (input_empty (input))
		{
//			printf ("empty\n");
			continue ;
		}
		add_history (input);
		parse_input (data, input);
	}
	rl_clear_history ();
	argc++;
	argv++;
	return (0);
}
