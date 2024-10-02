/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momillio <momillio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:29:59 by mkadri            #+#    #+#             */
/*   Updated: 2024/10/02 12:33:08 by momillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/run.h"

void	ft_error(char *error)
{
	perror(error);
	exit(1);
}

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
		return (0);
	if (*line == '\0')
		return (0);
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

int	wait_for_process(pid_t pid1)
{
	int	status;
	int	return_status;

	status = 0;
	return_status = 0;
	waitpid(pid1, &status, 0);
	if (WIFEXITED(status))
		return_status = WEXITSTATUS(status);
	return (return_status);
}
