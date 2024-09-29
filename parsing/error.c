/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 10:19:54 by momillio          #+#    #+#             */
/*   Updated: 2024/09/27 16:09:25 by momillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	free_data(t_data *data)
{
	int	i;

	i = -1;
	if (data->env)
	{
		while (data->env[++i])
			free (data->env[i]);
	}
	if (data->new_input)
		free (data->new_input);
	free (data);
}

void	free_all(t_data *data, t_ast *tree,)

int	error_exit(char *s)
{
	perror (s);
	exit (1);
}
