/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:53:46 by momillio          #+#    #+#             */
/*   Updated: 2024/09/24 11:26:20 by momillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Add content char by char to the new input */

char	*add_to_input(char **input, char *str)
{
	str = strjoin_char (str, **input);
	(*input)++;
	return (str);
}

/*
	Skip the quotes inside the quoted token, so quotes who are not read.
	It skips just skips if its a pair of empty quotes.
	If its quotes containing other char it copies the chars.
	If its a double quoted "$" it will call the function to replace the dollar
	by the environnement variable.
	It increment the ptr. 
	*/

char	*skip_quotes(char **str, t_data *data)
{
	int		count;
	char	quote;

	while (**str && is_quote (**str))
	{
		count = 0;
		quote = **str;
		while (**str == quote)
		{
			(*str)++;
			count++;
		}
		if (count % 2)
		{
			while (**str != quote)
			{
				if (**str == '$' && quote == '"')
					data->new_input = replace_dollar (str, data);
				if (**str != quote)
					data->new_input = add_to_input (str, data->new_input);
			}
			(*str)++;
		}
	}
	return (data->new_input);
}
/*
	The token contains quote
	So to delimit the token correctly, it will put the same type of quote at 
	the beginning of the token and at the end.
	If we were not inside a token it will set the bool to true
	If we were already inside a token, it will set the bool to false
*/

char	*delimit_token(t_data *data, bool *token, char quote)
{
	data->new_input = strjoin_char (data->new_input, quote);
	*token = !*token;
	return (data->new_input);
}

/* 
	Skip eventual whitespaces in the beginning of the input
	If the token contain quotes, it will delimit the token according to it.
	It will skip the useless quotes.
	If there is a $, it will replace it by its environnement variable.
	And for the rest, it will copy it in the new input.
*/

char	*parse_line(char *input, t_data *data)
{
	char	quote;
	bool	token;

	quote = 0;
	token = false;
	skipe_whistepaces (&input);
	while (*input)
	{
		if (contain_quote (data->new_input, &quote) && token == 0)
			data->new_input = delimit_token (data, &token, quote);
		if (is_quote (*input))
			data->new_input = skip_quotes (&input, data);
		if (*input && !is_quote (*input))
		{
			if ((is_symbol (*input) || is_whitespaces (*input)) && token == 1)
				data->new_input = delimit_token (data, &token, quote);
			if (*input == '$')
				data->new_input = replace_dollar (&input, data);
			else
				data->new_input = add_to_input (&input, data->new_input);
		}
	}
	if (token == 1)
		data->new_input = delimit_token (data, &token, quote);
	return (data->new_input);
}

/*
	Create a string and allocate memory for it.
	Check if there are open quotes or unclosed pipe in the input.
	Parse the input by lexing it and creating the nodes needed.
	Nulterminate the different nodes created in the parsing tree.
*/

int	parse_input(t_data *data, char *input)
{
	char	*end_input;
	char	*temp;
	t_ast	*tree;

	data->new_input = ft_strdup ("");
	if (!data->new_input)
		return (1);
	if (open_quotes (input, data) || unclosed_pipe (input))
		return (free (input), 1);
	data->new_input = parse_line (input, data);
	end_input = data->new_input + ft_strlen (data->new_input);
	temp = data->new_input;
	printf ("parsed : %s\n", data->new_input);
	tree = parse_pipe (&temp, end_input, data);
	if (!tree)
	{
		free_data (data);
		free (input);
		return (1);
	}
	tree = nulterminate (tree, data);
	parse_tree (tree);
	return (1);
}
