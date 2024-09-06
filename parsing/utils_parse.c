/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momillio <momillio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 22:39:31 by momillio          #+#    #+#             */
/*   Updated: 2024/09/06 10:18:57 by momillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	unclosed_pipe (char *input)
{
	int	i;
	
	i = -1;
	while (input[++i])
	{
		if (input[i] == '|')
			{
				i++;
				while (input[i] && (input[i] >= 9 && input[i] <= 13
				|| input[i] == 32))
					i++;
				if (input[i] == '|')
					continue;
				if (!input[i])
					//message d'erreur "unclosed pipe"
					return (true);
			}
	}
	return (false);
}