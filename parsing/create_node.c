/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:23:19 by momillio          #+#    #+#             */
/*   Updated: 2024/09/16 13:54:55 by momillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_ast	*create_cmd_node()
{
	t_ast	*node;

	node = malloc (sizeof (t_ast));
	if (!node)
		return (NULL);
	node->type = CMD;
	node->next = NULL;
	node->content.cmd_node.args = NULL;
	node->content.cmd_node.fd_in = -1;
	node->content.cmd_node.is_builtin = 0;
	node->content.cmd_node.fd_out = -1;
	node->content.cmd_node.name = NULL;
	node->content.cmd_node.type = CMD;
	return (node);
}

t_ast	*create_redir_node(int type)
{
	t_ast	*node;
	
	node = malloc (sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	node->next = NULL;
	node->content.redir_node.
}
