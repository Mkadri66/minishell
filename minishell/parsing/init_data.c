/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momillio <momillio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:10:08 by momillio          #+#    #+#             */
/*   Updated: 2024/10/02 10:24:15 by momillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"
#include "../includes/builtins.h"

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
	*env_list = NULL;
	copy_env_to_list (env_list, env);
	(*data)->env_list = env_list;
	(*data)->new_input = NULL;
	(*data)->nb_cmd = 0;
	(*data)->stdin_cpy = dup (STDIN_FILENO);
	(*data)->stdout_cpy = dup (STDOUT_FILENO);
	(*data)->d_quote = false;
	(*data)->s_quote = false;
	return (1);
}
