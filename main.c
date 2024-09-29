/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkadri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:05:14 by mkadri            #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2024/09/03 13:31:49 by mkadri           ###   ########.fr       */
=======
/*   Updated: 2024/09/27 16:24:26 by momillio         ###   ########.fr       */
>>>>>>> Stashed changes
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main()
{
<<<<<<< Updated upstream
    return(0);
}
=======
	int	i;

	i = -1;
	while (input[++i])
	{
		if (!is_whitespaces (input[i]))
			return (false);
	}
	return (true);
}
void	handle_input(t_data **data, t_env_node **env_list, char **input)
{
	t_ast	*tree;
	
	tree = NULL;
	add_history (*input);
	if (parse_input (data, input, &tree))
	{
		free ;
		exit (1);
	}
	check_builtin_and_run (tree, *data, env_list);
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;
	t_env_node *env_list;
	char	*input;

	if (!init_data (&data, &env_list, env, argc))
		return (1);
//    print_env (data);
	while (1)
	{
		input = readline ("Minishell: ");
//      printf ("input = %s\n", input);
		if (!input)
			continue ;
		if (input_empty (input))
			continue ;
		handle_input (&data, &env_list, &input);
//		add_history (input);
//		parse_input (data, input);
	}
	rl_clear_history ();
	(void)argv;
	return (0);
}
>>>>>>> Stashed changes
