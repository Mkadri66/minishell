/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momillio <momillio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 22:19:10 by momillio          #+#    #+#             */
/*   Updated: 2024/10/02 10:08:17 by momillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

bool	is_quote(char c)
{
	if (c == '"' || c == '\'')
		return (true);
	return (false);
}

/*
	Set the booleans to true if the quote must be read as a symbol and to false
	if the quote must be read as a char.
*/

void	check_quotes(char c, t_data *data)
{
	if (c == '\'')
	{
		if (!data->s_quote && !data->d_quote)
			data->s_quote = true;
		else
			data->s_quote = false;
	}
	else if (c == '"')
	{
		if (!data->s_quote && !data->d_quote)
			data->d_quote = true;
		else
			data->d_quote = false;
	}
}

bool	open_quotes(char *input, t_data *data)
{
	int	i;

	i = -1;
	data->s_quote = false;
	data->d_quote = false;
	while (input[++i])
	{
		check_quotes (input[i], &(*data));
	}
	if (data->s_quote || data->d_quote)
	{
		printf ("Quotes are open\n");
		return (true);
	}
	return (false);
}

/*
	Check if the string contain and return true and the type of quote
	Increment the ptr to skip the quote
 */

bool	contain_quote(char *str, char *quote)
{
	while (*str && !is_whitespaces(*str) && !is_symbol (*str))
	{
		if (is_quote (*str))
		{
			*quote = *str;
			return (true);
		}
		str++;
	}
	return (false);
}
