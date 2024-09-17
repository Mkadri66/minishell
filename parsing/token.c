/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:52:10 by momillio          #+#    #+#             */
/*   Updated: 2024/09/16 15:30:34 by momillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_ast	*get_redir_type(char *str)
{
	char *temp;
	int	type;
	t_ast	*node;

	temp = str;
	if (*temp == '<')
	{
		(*temp)++;
		if (*temp == '<')
			type = HEREDOC;
		else
			type == INP_REDIR;			
	}
	else if (*temp == '>')
		{
			(*temp)++;
			if (*temp == '>')
				type == APPEND;
			else
				type == OUT_REDIR;
		}
		node->content.cmd_node.
	node = create_redir_node ();
	return (node);
}
