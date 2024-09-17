/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 22:19:10 by momillio          #+#    #+#             */
/*   Updated: 2024/09/16 14:26:28 by momillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_single_quote(char *input, char **new_input, int index)
{
	if (input[index] == '\'')
	{
		index++;
		while (input[index] && input[index] != '\'')
		{
			if (input[index] == '"' && input[index + 1] == '"')
			{
				index += 2;
				continue ;
			}
			*new_input = strjoin_char (*new_input, input[index]);
//			printf ("Squotes : %s\n", *new_input);
			index++;
		}
		index++;
	}
	return (index);
}
int	is_double_quotes(char *input, char **new_input, int index)
{
	if (input[index] == '"')
	{
		index++;
		while (input[index] && input[index] != '"')
		{
			if (input[index] == '"' && input[index + 1] == '"')
			{
				index += 2;
				continue ;
			}
//			if (input[index] == '$')
//				replace_dollar (input, new_input, index);
			*new_input = strjoin_char (*new_input, input[index]);
//			printf ("Dquotes : %s\n", *new_input);
			index++;
		}
		index++;
	}
	return (index);
}

t_data	*check_quotes(char c, t_data *data)
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
		data = check_quotes (input[i], data);
//		printf ("SQ = %i  DQ = %i\n", single_q, double_q);	
	}
	if (data->s_quote || data->d_quote)
		return (true); // gestion des free
	return (false);
}
