/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nulterminate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:24:04 by momillio          #+#    #+#             */
/*   Updated: 2024/09/26 16:05:30 by momillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_builtin(char *cmd)
{
	if (!ft_strncmp (cmd, "echo", 4) && !cmd[4])
		return (true);
	else if (!ft_strncmp (cmd, "pwd", 3) && !cmd[3])
		return (true);
	else if (!ft_strncmp (cmd, "export", 6) && !cmd[6])
		return (true);
	else if (!ft_strncmp (cmd, "cd", 2) && !cmd[2])
		return (true);
	else if (!ft_strncmp (cmd, "env", 3) && !cmd[3])
		return (true);
	else if (!ft_strncmp (cmd, "unset", 5) && !cmd[5])
		return (true);
	return (false);
}

/*
	Nulterminate the cmd_node.
	Count the number of cmd.
	Nulterminate the arrays.
	Check if the command is a builtin.
*/

void	nulterminate_cmd(t_ast *node, t_data *data)
{
	int	i;

	i = 0;
	if (node->content.cmd_node.args[i])
	{
		data->nb_cmd += 1;
		while (node->content.cmd_node.args[i])
		{
		//	printf ("here");
		*(node->content.cmd_node.e_args[i]) = 0;
		//	printf ("cmd = %s\n", node->content.cmd_node.args[i]);
			i++;
		}
		if (is_builtin (node->content.cmd_node.args[0]))
			node->content.cmd_node.is_builtin = true;
	}
}

/* Nulterminate the different nodes. */

t_ast	*nulterminate(t_ast *tree, t_data *data)
{
	data->nb_cmd = 0;
	if (tree->type == CMD)
		nulterminate_cmd (tree, data);
	if (tree->type == PIPE)
	{
		nulterminate(tree->content.pipe_node.left, data);
		nulterminate(tree->content.pipe_node.right, data);
	}
	if (tree->type == REDIR)
	{
		nulterminate (tree->content.redir_node.cmd, data);
		*tree->content.redir_node.e_filename = 0;
	}
	return (tree);
}
