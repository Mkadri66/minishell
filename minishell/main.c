/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momillio <momillio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:05:14 by mkadri            #+#    #+#             */
/*   Updated: 2024/09/30 15:07:54 by momillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"
# include "./includes/parsing.h"
# include "./includes/builtins.h"
# include "./includes/run.h"

int	g_exit_status;

int input_empty(char *input)
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
void	handle_input(t_data *data, t_env_node **env_list, char **input)
{
	t_ast	*tree;
	
	tree = NULL;
//	if (**input = 4)
//		ft_exit ("exit", env_list);
	add_history (*input);
	if (!parse_input (data, input, &tree))
	{
		free_all (&data, tree, input);
		exit (1);
	}
	check_builtin_and_run (tree, data, env_list);
	free_tree (tree);
	free (data->new_input);
	free (*input);
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;
	t_env_node *env_list;
	char	*input;

	if (!init_data (&data, &env_list, env, argc))
		return (1);
//    print_env (data);
	g_exit_status = 0;
	while (1)
	{
		input = readline ("Minishell: ");
//      printf ("input = %s\n", input);
		if (!input)
			continue ;
		if (input_empty (input))
			continue ;
		handle_input (data, &env_list, &input);
//		add_history (input);
//		parse_input (data, input);
	}
	rl_clear_history ();
	(void)argv;
	return (0);
}
