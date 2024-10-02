/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momillio <momillio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:53:03 by momillio          #+#    #+#             */
/*   Updated: 2024/10/02 10:25:05 by momillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

/*
	Parse the input and check for redirections in it.
	Peek look if "<>" is the next non-whitespace char in the input.
	Get_token returns the type of redirection.
	Check that the name of the file is correct and does not contain operator.
	Create a redirection node.
	Link the cmd_node created in parse_exec with the redirection node.
*/

t_ast	*parse_redir(t_ast *node, char **s_input, char *e_input)
{
	int		token;
	char	*s_file;
	char	*e_file;

	while (peek(s_input, e_input, "<>"))
	{
		token = get_token (s_input, e_input, 0, 0);
		if (get_token (s_input, e_input, &s_file, &e_file) != CMD)
		{
			free (node);
			return (NULL);
		}
		node = create_redir_node (token, s_file, e_file, node);
	}
	return (node);
}

/*
	Parse the input and create a cmd node.
	Call the parse_redir function to see if there is a redirection associated
	to the command.
	Until we encounter a | , we parse the string.
	Get_token check if we are not at the end of the input.
	Init_cmd fill the cmd_node variables.
	It check if we dont have too much arguments.
	And we call again the parse_redir to check for other redirections
	*/

t_ast	*parse_exec(char **s_input, char *e_input)
{
	t_ast	*node;
	int		i;
	char	*s_token;
	char	*e_token;

	i = 0;
	node = create_cmd_node();
	node = parse_redir (node, s_input, e_input);
	if (!node)
		return (NULL);
	while (!peek (s_input, e_input, "|"))
	{
		if (get_token (s_input, e_input, &s_token, &e_token) == -1)
			break ;
		init_cmd (node, s_token, e_token, &i);
		if (i > MAX_ARGS)
		{
			printf ("Too many arguments\n");
			return (NULL);
		}
		node = parse_redir (node, s_input, e_input);
		if (!node)
			return (NULL);
	}
	return (node);
}
/*
	Parse the input and check if there is | in it.
	Call the parse_exec function first because there should be a command before
	the pipe.
	The peek function check if '|' is the next non-whitespace char in the string.
	Here get_token is used to skip the whitespaces between the last token and
	the pipe, to pass the pipe and to skip the whitespaces between the pipe
	and the nex token.
	It checks that the next token is a command.
	It creates a node pipe and call itself again in the parameters to continue
	parsing the input after the pipe.
*/

t_ast	*parse_pipe(char **s_input, char *e_input, t_data *data)
{
	t_ast	*node;

	node = parse_exec(s_input, e_input);
	if (!node)
		return (NULL);
	if (peek (s_input, e_input, "|"))
	{
		get_token (s_input, e_input, 0, 0);
		if (check_next_token (*s_input, e_input) == 1)
		{
			free (node);
			return (NULL);
		}
		node = create_pipe_node (node, parse_pipe (s_input, e_input, data));
		if (!node)
		{
			free (node);
			return (NULL);
		}
	}
	return (node);
}
