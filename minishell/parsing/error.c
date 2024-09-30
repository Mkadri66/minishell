/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momillio <momillio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 10:19:54 by momillio          #+#    #+#             */
/*   Updated: 2024/09/30 17:23:15 by momillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"
# include "../includes/builtins.h"

void	free_data(t_data *data)
{
	int	i;

	i = -1;
	if (data->env_list)
		free_env_list (data->env_list);
	if (data->new_input)
		free (data->new_input);
	free (data);
}

void	free_tree(t_ast *tree)
{
	if (tree->type == CMD)
		free (tree);
	else if (tree->type == REDIR)
	{
		free_tree (tree->content.redir_node.cmd);
		free (tree);
	}
	else if (tree->type == PIPE)
	{
		free_tree (tree->content.pipe_node.left);
		free_tree (tree->content.pipe_node.right);
		free (tree);
	}
}

void	free_all(t_data **data, t_ast *tree, char **input)
{
	if (*input)
		free (*input);
	if (*data)
		free_data (*data);
	if (tree)
		free_tree (tree);
	exit (0);
}

int	error_exit(char *s)
{
	perror (s);
	exit (1);
}
