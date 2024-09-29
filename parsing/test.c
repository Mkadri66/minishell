/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:29:06 by momillio          #+#    #+#             */
/*   Updated: 2024/09/27 11:09:00 by momillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	print_env(t_data *data)
{
	int	i;

	i = -1;
	while (data->env[++i])
		printf (" %d = %s\n", i, data->env[i]);
}

void	print_tree(t_ast *tree)
{
	int	i;

	i = -1;
	printf ("%snode type : %d\n%s", RED, tree->type, RESET);
	printf ("node_ptr = %p\n", tree);
	if (tree->type == CMD && tree->content.cmd_node.args[0])
	{
		while (tree->content.cmd_node.args[++i])
			printf ("arg = %s\n", tree->content.cmd_node.args[i]);
		printf ("builtin = %d\n", tree->content.cmd_node.is_builtin);
	}
	else if (tree->type == REDIR)
	{
		printf ("redir type = %d\n", tree->content.redir_node.type);
		printf ("filename = %s\n", tree->content.redir_node.filename);
		printf ("mode = %d\n", tree->content.redir_node.mode);
		printf ("fd = %d\n", tree->content.redir_node.fd);
		printf ("redir_cmd = %d,  %p\n", tree->content.redir_node.cmd->type, tree->content.redir_node.cmd);
	}
	else if (tree->type == PIPE)
	{
		printf ("left = %d\n", tree->content.pipe_node.left->type);
		printf ("right = %d\n", tree->content.pipe_node.right->type);
	}
}

void	parse_tree(t_ast *tree)
{
	if (tree->type == CMD)
		print_tree (tree);
	else if (tree->type == REDIR)
	{
		print_tree (tree);
		parse_tree (tree->content.redir_node.cmd);
	}
	else if (tree->type == PIPE)
	{
		print_tree (tree);
		parse_tree (tree->content.pipe_node.left);
		parse_tree (tree->content.pipe_node.right);
	}
}
