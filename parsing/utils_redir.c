/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:44:43 by momillio          #+#    #+#             */
/*   Updated: 2024/09/26 12:18:07 by momillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Intialize the variables of the redir_node.
	Depending on the type, it will set the file descriptor and the mode for the
	open function accordingly.
*/

void	init_redir(int type, t_ast *node)
{
	if (type == INP_REDIR)
	{
		node->content.redir_node.mode = O_RDONLY;
		node->content.redir_node.fd = STDIN_FILENO;
		node->content.redir_node.is_output = false;
	}
	if (type == OUT_REDIR)
	{
		node->content.redir_node.mode = O_RDWR | O_CREAT | O_TRUNC;
		node->content.redir_node.fd = STDOUT_FILENO;
		node->content.redir_node.is_output = true;
	}
	if (type == APPEND)
	{
		node->content.redir_node.mode = O_RDWR | O_CREAT | O_APPEND;
		node->content.redir_node.fd = STDOUT_FILENO;
		node->content.redir_node.is_output = true;
	}
}

/* 
	Check if there is multiple same redirections.
	If there is it will link the cmd to the newest redirection and
	forget about the previous one.
*/

t_ast	*multiple_redir(t_ast *old, t_ast *new)
{
	t_ast	*temp;
//	printf ("multiple redir function\n");	
	if (old->content.redir_node.type == new->content.redir_node.type \
		|| (old->content.redir_node.is_output == true 
		&& new->content.redir_node.is_output == true))
	{
//		printf ("inside if multiple redir\n");
		new->content.redir_node.cmd = old->content.redir_node.cmd;
//		if (old->content.redir_node.cmd->type == CMD)
//		{
//		new->content.redir_node.cmd = old->content.redir_node.cmd;
		free (old);
		return (new);
//		}
	}
	temp = old->content.redir_node.cmd;
	if (new->content.redir_node.type == temp->content.redir_node.type \
		|| (new->content.redir_node.is_output == true 
		&& temp->content.redir_node.is_output == true))
	{
//		printf ("inside if 3 redir\n");
		old->content.redir_node.cmd = temp->content.redir_node.cmd;
		free (temp);
	}
	return (new);
}

/*
	This function check if after the pipe, there is another pipe or a
	redirection.
	If there is it return true.
*/

int	check_next_token(char *s_input, char *e_input)
{
	while (s_input < e_input && is_whitespaces (*s_input))
		s_input++;
	if (*s_input == '|')
	{
		printf ("Pipe following a pipe");
		return (1);
	}
	if (*s_input == '<' || *s_input == '>')
	{
		printf ("Redirection after a pipe. Need a command\n");
		return (1);
	}
	return (0);
}
