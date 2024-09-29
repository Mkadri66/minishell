/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momillio <momillio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:29:59 by mkadri            #+#    #+#             */
/*   Updated: 2024/09/29 18:22:28 by momillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/run.h"

void	reopen_stdin_stdout(int fd)
{
	if (fd == 0)
	{
		if (open("/dev/tty", O_RDONLY) < 0)
			ft_error("open stdin failed");
	}
	else if (fd == 1)
	{
		if (open("/dev/tty", O_WRONLY) < 0)
			ft_error("open stdout failed");
	}
}

void	run_heredoc(t_redir *redir_node)
{
	char	*line;
	int		file;

	file = open(".here_doc", O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (file < 0)
		ft_error(redir_node->filename);
//	setup_heredoc_signals();
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			printf("minishell: warning: here-document delimited by\
			end-of-file (wanted %s)\n", redir_node->filename);
			return ;
		}
		if (is_line_delimiter(line, redir_node))
		{
			free(line);
			close(file);
			return ;
		}
		else
			handle_line(line, file);
	}
}

void	ft_heredoc(t_redir *redir_node)
{
	int	file;

	file = 0;
	run_heredoc(redir_node);
	file = open(".here_doc", O_RDONLY, 0777);
	if (file < 0)
		ft_error("heredoc");
	if (dup2(file, 0) < 0)
		ft_error("dup2");
	close(file);
}

void	run_redir(t_ast *tree, t_data *data, t_env_node **env_list)
{
	t_redir	*redir_node;

	redir_node = &tree->content.redir_node;
	if (redir_node->type == HEREDOC)
	{
		dup2(data->stdin_cpy, STDIN_FILENO);
		ft_heredoc(redir_node);
	}
	else
	{
	//	if (redir_node->fd != -1 && close(redir_node->fd) < 0)
	//		ft_error("close stdin/stdout failed");
		redir_node->fd = open(redir_node->filename, redir_node->mode, 0777);
		if (redir_node->fd < 0)
			ft_error(redir_node->filename);
		if (dup2(redir_node->fd, STDOUT_FILENO) < 0)
			ft_error("dup2 failed");
	}
	run_tree(redir_node->cmd, data, env_list);
	reopen_stdin_stdout(redir_node->fd);
	return ;
}
