/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momillio <momillio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 22:11:49 by momillio          #+#    #+#             */
/*   Updated: 2024/09/06 11:19:01 by momillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parse_input(t_data *data, char *input)
{
	int	i;

	i = -1;
	if (open_quotes (input) || unclosed_pipe (input))
		return (1); // free data, data.                                    env
}
