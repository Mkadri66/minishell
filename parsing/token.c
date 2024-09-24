/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:52:10 by momillio          #+#    #+#             */
/*   Updated: 2024/09/24 11:32:38 by momillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
	Determine what kind of redirection it is.
*/

int	get_redir_type(char **str, int type)
{
	if (**str == '<')
	{
		(*str)++;
		if (**str == '<')
		{
			type = HEREDOC;
			(*str)++;
		}
		else
			type = INP_REDIR;
	}
	else if (**str == '>')
	{
		(*str)++;
		if (**str == '>')
		{
			type = APPEND;
			(*str)++;
		}
		else
			type = OUT_REDIR;
	}
	return (type);
}
/*
	Skip eventual whitespaces, return the incremented ptr and true if the
	symbol we are looking for is the next non-whitespace char in the input.
*/

int	peek(char **s_input, char *e_input, char *c)
{
	char	*str;

	str = *s_input;
	while (str < e_input && is_whitespaces (*str))
		str++;
	*s_input = str;
	return (*str && ft_strchr (c, *str));
}

/*
	Quoted_token will trim the token of its quotes.
	Its will set the start_ptr on the char after the beginning quote and the
	end_ptr the char before the ending quote.
	Then it will increment the ptr of the input to pass the ending quote.
	Then it returns the type CMD.
*/

int	quoted_token(char **str, char **s_token, char **e_token)
{
	char	quote;

	quote = **str;
	*s_token = *str;
	(*str)++;
	if (**str == quote)
	{
		(*str)++;
		*e_token = *str;
	}
	else
	{
		*s_token = *str;
		while (**str != quote)
			(*str)++;
		*e_token = *str;
		if (is_quote (**str))
			(*str)++;
	}
	return (CMD);
}

/*
	Determine the type of the token.
	If its a redirection it calls the get_redir_type function.
	If its a | it returns PIPE and increment the ptr to pass it.
	Else its a CMD type, and will increment the ptr until the next token.
*/

int	get_token_type(char **str, int type, char *e_input)
{
	if (**str == '<' || **str == '>')
		type = get_redir_type (str, type);
	else if (**str == '|')
	{
		type = PIPE;
		(*str)++;
	}
	else
	{
		type = CMD;
		while (*str < e_input && !is_symbol (**str) \
				&& !is_whitespaces (**str) && !is_quote (**str))
			(*str)++;
	}
	return (type);
}

/*
	Get_token will look into the string to isolate the token and define
	its type.
	If the token begins by a quote, it calls the quoted_token function.
	Else it call the get_token_type function to get the type.
	It will update the ptr to the start and the end of the token.
*/

int	get_token(char **s_input, char *e_input, char **s_token, char **e_token)
{
	char	*str;
	int		type;

	str = *s_input;
	type = 0;
	while (str < e_input && is_whitespaces (*str))
		str++;
	if (str >= e_input)
		return (-1);
	if (is_quote (*str))
		type = quoted_token (&str, s_token, e_token);
	else
	{
		if (s_token)
			*s_token = str;
		type = get_token_type (&str, type, e_input);
		if (e_token)
			*e_token = str;
	}
	while (str < e_input && is_whitespaces (*str))
		str++;
	*s_input = str;
	return (type);
}
