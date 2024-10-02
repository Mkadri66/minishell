/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momillio <momillio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:10:29 by mkadri            #+#    #+#             */
/*   Updated: 2024/10/02 10:20:27 by momillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdarg.h>
# include <string.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdio.h>
# include <stdbool.h>
# include <unistd.h>
# include <ctype.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "../libft/libft.h"

extern int	g_exit_status;

# define RED     "\033[0;31m"
# define GREEN	"\033[1;32m"
# define RESET   "\033[0m"
# define MAX_ARGS 100

void	set_signals(void);

typedef enum s_token_type
{
	CMD,	
	PIPE,		// "|"
	REDIR,
	INP_REDIR,	// "<"
	OUT_REDIR,	// ">"
	HEREDOC,		// "<<"
	APPEND,		// ">>"
}	t_token_type;

typedef struct s_dollar
{
	char	*name;
	int		len;
	int		index;
}	t_dollar;

typedef struct s_signal
{
	int		sig_int;
	int		sig_quit;
	int		exit_status;
	pid_t	pid;
}	t_signal;

typedef struct s_cmd
{
	t_token_type	type;
	char			*args[MAX_ARGS];
	char			*e_args[MAX_ARGS];
	bool			is_builtin;
}	t_cmd;

typedef struct s_pipe
{
	t_token_type	type;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_pipe;

typedef struct s_redir
{
	t_token_type	type;
	char			*filename;
	char			*e_filename;
	struct s_ast	*cmd;
	int				mode;
	int				fd;
	bool			is_output;
}	t_redir;

typedef union u_node_content
{
	t_cmd	cmd_node;
	t_pipe	pipe_node;
	t_redir	redir_node;
}	t_node_content;

typedef struct s_ast
{
	t_token_type	type;
	t_node_content	content;
}	t_ast;

typedef struct s_env_node
{
	char				*env_name;
	struct s_env_node	*prev;
	struct s_env_node	*next;

}	t_env_node;

typedef struct s_data
{
	t_env_node	**env_list;
	char		*new_input;
	int			nb_cmd;
	int			stdin_cpy;
	int			stdout_cpy;
	bool		s_quote;
	bool		d_quote;
}	t_data;

#endif