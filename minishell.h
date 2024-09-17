/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:10:29 by mkadri            #+#    #+#             */
/*   Updated: 2024/09/16 15:38:39 by momillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
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

extern int	g_exit_status;

typedef enum s_token_type
{
	CMD,	
	PIPE,		// "|"
	INP_REDIR,	// "<"
	OUT_REDIR,	// ">"
	HEREDOC,		// "<<"
	APPEND,		// ">>"
	DOLLARS,		// "$"
	ARG,
	SQ,		// '
	DQ,		// "
}	t_token_type;

typedef struct s_dollar
{
	char	*name;
	int	len;
	int	index;
}	t_dollar;

typedef struct s_token
 {
	t_token_type	type;
	char	*str;
	struct s_token	*next;
	struct s_token	*previous;
 }	t_token;

 typedef struct s_signal
 {
	int	sig_int;
	int	sig_quit;
	int	exit_status;
	pid_t	pid;
 }	t_signal;

 typedef struct s_cmd
 {
	t_token_type type;
	char	*name;
	char	**args;
	bool	is_builtin;
	int	fd_in;
	int	fd_out;
 }	t_cmd;

 typedef struct s_pipe
 {
	t_token_type	type;
	struct ast *left;
	struct ast *right;
 }	t_pipe;
 
 typedef struct s_redir
 {
	t_token_type	type;
	char	*filename;
	char	*e_filename;
	int	mode;
	int fd;
 } t_redir;

typedef union u_node_content
{
	t_cmd	cmd_node;
	t_pipe	pipe_node;
	t_redir	redir_node;
}	t_node_content;

typedef struct s_ast
{
	t_token_type type;
	t_node_content	content;
	struct ast *next;
}	t_ast;

typedef struct s_data
{
	char **env;
	char	*new_input;
	bool	s_quote;
	bool	d_quote;
	t_token *token;
	t_ast	*tree;
	t_ast	*redir;
}	t_data;


/* Test */
void print_env (t_data *data);

/* Init_data */
int	init_data(t_data **data, char **env);

/* Parse */
int	parse_input(t_data *data, char *input);

/* Utils_quotes */
bool	open_quotes(char *input, t_data *data);
int	is_single_quote(char *input, char **new_input, int index);
int	is_double_quotes(char *input, char **new_input, int index);
void	check_quotes(char c, bool *single_q, bool *double_q);


/* Dollar */
char	*replace_dollar(char **input, char *new_input, t_data *data);

/* Utils_parse */
bool	is_symbol(char c);
bool	is_quote(char c);
bool	is_whitespaces(char c);
char	*strjoin_char(char *src, char c);
bool	unclosed_pipe (char *input);

/* Signals */
void	set_signals(void);

/* Create node */
t_ast	*create_cmd_node();

/* Token */
t_ast	*get_redir_type(char *str);

#endif