/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:44:43 by momillio          #+#    #+#             */
/*   Updated: 2024/09/24 12:27:35 by momillio         ###   ########.fr       */
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
	}
	if (type == OUT_REDIR)
	{
		node->content.redir_node.mode = O_RDWR | O_CREAT | O_TRUNC;
		node->content.redir_node.fd = STDOUT_FILENO;
	}
	if (type == APPEND)
	{
		node->content.redir_node.mode = O_RDWR | O_CREAT | O_APPEND;
		node->content.redir_node.fd = STDOUT_FILENO;
	}
}

/* 
	Check if there is multiple redirections.
	If there is it will link the cmd to the newest redirection and
	forget about the previous one.
*/

t_ast	*multiple_redir(t_ast *old_redir, t_ast *new_redir)
{
	printf ("here\n");
	while (old_redir->content.redir_node.cmd->type == REDIR)
		old_redir = old_redir->content.redir_node.cmd;
	printf ("multi type = %d, filename = %s\n", old_redir->type, old_redir->content.redir_node.filename);
	if (old_redir->content.redir_node.cmd->type == CMD)
	{
		new_redir->content.redir_node.cmd = old_redir->content.redir_node.cmd;
		old_redir->content.redir_node.cmd = new_redir;
	}
	return (old_redir);
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
