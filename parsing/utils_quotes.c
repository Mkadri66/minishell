/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momillio <momillio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 22:19:10 by momillio          #+#    #+#             */
/*   Updated: 2024/09/06 10:19:01 by momillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	parse_quotes(char c, bool *single_q, bool *double_q)
{
	if (c == '\'')
	{
		if (!*single_q && !*double_q)
			*single_q = true;
		else
			*single_q = false;
	}
	else if (c == '"')
	{
		if (!*single_q && !*double_q)
			*double_q = true;
		else
			*double_q = false;
	}
}

bool	open_quotes(char *input)
{
	int	i;
	bool	single_q;
	bool	double_q;
	
	i = -1;
	single_q = false;
	double_q = false;
	while (input[++i])
		parse_quotes (input[i], &single_q, &double_q);
	if (single_q || double_q)
		return (true); // gestion des free
	return (false);
}
