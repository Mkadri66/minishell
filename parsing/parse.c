/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 22:11:49 by momillio          #+#    #+#             */
/*   Updated: 2024/09/16 14:33:00 by momillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Skip les whitespaces, remplace le $ si la syntaxe est correcte par la variable d'environnement et dup
	le tout dans une nouvelle string */
	
char	*parse_line(char *input, t_data *data)
{
	data->s_quote = false;
	data->d_quote = false;
	while (*input && is_whitespaces (*input))
		input++;
	while (*input)
	{
		check_quotes (*input, data);
		if (*input == '$' && !data->s_quote && *input - 1 != '\'')
		{
			data->new_input = replace_dollar (&input, data);
			continue ;
		}
			
		else
		{
			data->new_input = strjoin_char (data->new_input, *input);
			input++;
		}
	}
	return (data->new_input);
}

t_ast	*parse_exec(char **s_input, char *e_input, t_data *data)
{
	t_ast	*node;
	int	i;
	char	*s_token;
	char	*e_token;

	node = create_cmd_node();
	node = parse_redir (node, s_input, e_input, data);
}

t_ast	*parse_redir(t_data	*data)
{
	t_ast	*node;
	int	i;
	
	i = 0;
	data->s_quote = false;
	data->d_quote = false;
	while ((*input)[i])
	{
		check_quotes (input[i], data);
		while (input[i] && (data->s_quote || data->d_quote))
		{
			i++;
			check_quotes (input[i], data);
		}
		if (input[i] == '<' || input[i] == '>')
			node = get_redir_type (input + i);
	}
}

t_ast	*parse_pipe(char **s_input, char *e_input, t_data *data)
{
	t_ast	*node;

	node = parse_exec(s_input, e_input, data);
}

int	parse_input(t_data *data, char *input)
{
	char	*new_input;
	char	*end_input;
	t_ast	*tree;
	
	data->new_input = ft_strdup ("");
	if (!data->new_input)
		return (1); // free data, data.env
	if (open_quotes (input, data) || unclosed_pipe (input))
		return (1); // free data, data.env
	data->new_input = parse_line (input, data);
	end_input = new_input + ft_strlen (new_input);
	printf ("parsed : %s\n", new_input);
	data->redir = parse_redir (new_input); 
	tree = parse_pipe (&new_input, end_input, data);
	return (1);
}
