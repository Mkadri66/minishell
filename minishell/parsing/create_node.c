/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momillio <momillio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:23:19 by momillio          #+#    #+#             */
/*   Updated: 2024/09/29 18:29:10 by momillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

/*
	Fills the args variables of the cmd_node.
*/

void	init_cmd(t_ast *node, char *s_token, char *e_token, int *i)
{
//	printf ("init_ptr before = %p\n", node);
	t_ast	*temp;

	temp = node;
	if (temp->type == REDIR)
	{
	//	printf ("temp_ptr = %p\n", temp);
	//	printf ("temp_cmd_type = %d\n", temp->type);
		while (temp->type == REDIR)
			temp = temp->content.redir_node.cmd;
	//	printf ("temp_ptr after = %p\n", temp);
	//	printf ("temp_cmd_type after = %d\n", temp->type);
	//	node->content.redir_node.cmd->content.cmd_node.args[*i] = s_token;
	//	node->content.redir_node.cmd->content.cmd_node.e_args[*i] = e_token;
	}
	if (temp->type == CMD)
	{
	//	printf ("inside init\n");
	temp->content.cmd_node.args[*i] = s_token;
	temp->content.cmd_node.e_args[*i] = e_token;
	}
	//*(node->content.cmd_node.e_args[*i]) = 0;
//	printf ("cmd = %s   i = %d\n", node->content.cmd_node.args[*i], *i);
//	printf ("e_cmd = %s\n", (node->content.cmd_node.e_args[*i] - 1));
	(*i)++;
//	printf ("init_ptr after = %p\n", node);
}

/*
	Create a cmd_node and initialize the variables.
*/

t_ast	*create_cmd_node(void)
{
	t_ast	*node;

	node = malloc (sizeof (t_ast));
	if (!node)
		return (NULL);
	node->type = CMD;
	node->content.cmd_node.is_builtin = false;
	ft_memset (node->content.cmd_node.args, 0, sizeof (node->content.cmd_node.args));
	ft_memset (node->content.cmd_node.e_args, 0, sizeof (node->content.cmd_node.e_args));
	node->content.cmd_node.type = CMD;
	return (node);
}

/* 
	Create a redirection node, define its type. If its an HEREDOC it changes
	global variable exit_status to -42.
	It links the redirection node to the command it will work on.
	It checks if there was another redirection linked before to the command
*/

t_ast	*create_redir_node(int type, char *s_file, char *e_file, t_ast *cmd)
{
	t_ast	*node;

	node = malloc (sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = REDIR;
	if (type == HEREDOC)
		g_exit_status = -42;
	node->content.redir_node.filename = s_file;
	node->content.redir_node.e_filename = e_file;
	*(node->content.redir_node.e_filename) = 0;
	node->content.redir_node.type = type;
	node->content.redir_node.cmd = cmd;
	node->content.redir_node.mode = -1;
	node->content.redir_node.fd = -1;
//	printf ("cmd ptr = %p\n", cmd);
//	printf ("cmd type = %d\n", cmd->type);
//	if (cmd->type == REDIR)
//		printf ("cmd_redir_type = %d\n", cmd->content.redir_node.type);
	init_redir (type, node);
	if (cmd->type == REDIR)
		return (multiple_redir (cmd, node));
	return (node);
}

/*
	Create a pipe_node, set its type and link the left and right ptr to the
	previous command and the next command.
	If there is no next command, its an unclosed pipe and its an error.
*/

t_ast	*create_pipe_node(t_ast *left, t_ast *right)
{
	t_ast	*pipe_node;

	pipe_node = malloc (sizeof (t_ast));
	if (!pipe_node)
		return (NULL);
	pipe_node->type = PIPE;
	pipe_node->content.pipe_node.left = left;
	pipe_node->content.pipe_node.right = right;
	pipe_node->content.pipe_node.type = PIPE;
	if (!pipe_node->content.pipe_node.right)
	{
		free (pipe_node->content.pipe_node.left);
		free (pipe_node);
		return (NULL);
	}
	return (pipe_node);
}
