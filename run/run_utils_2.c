/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkadri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:29:59 by mkadri            #+#    #+#             */
/*   Updated: 2024/09/22 13:16:13 by mkadri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_line(char *line, int file)
{
	ft_putstr_fd(line, file);
	ft_putchar_fd('\n', file);
	free(line);
}

int	is_line_delimiter(char *line, t_redir *redir_node)
{
	size_t	line_len;
	size_t	delimiter_len;

	if (!line)
	{
		printf("Debug: line is NULL\n");
		return (0);
	}
	if (*line == '\0')
	{
		printf("Debug: line is empty\n");
		return (0);
	}
	line_len = ft_strlen(line);
	delimiter_len = ft_strlen(redir_node->filename);
	if (ft_strncmp(line, redir_node->filename, delimiter_len) == 0
		&& (line_len == delimiter_len))
		return (1);
	else
		return (0);
}

void	dup_right(int *fd)
{
	close (fd[1]);
	dup2(fd[0], 0);
    close(fd[0]);
}
	