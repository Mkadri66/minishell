/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:10:29 by mkadri            #+#    #+#             */
/*   Updated: 2024/09/26 15:58:55 by momillio         ###   ########.fr       */
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

#define RED     "\033[0;31m"
#define GREEN	"\033[1;32m"
#define RESET   "\033[0m"
# define MAX_ARGS 100

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
	int	len;
	int	index;
}	t_dollar;

/*typedef struct s_token
 {
	t_token_type	type;
	char	*str;
	struct s_token	*next;
	struct s_token	*previous;
 }	t_token;*/

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
//	char	*name;
	char	*args[MAX_ARGS];
	char	*e_args[MAX_ARGS];
	bool	is_builtin;
 }	t_cmd;

 typedef struct s_pipe
 {
	t_token_type	type;
	struct s_ast *left;
	struct s_ast *right;
 }	t_pipe;
 
 typedef struct s_redir
 {
	t_token_type	type;
	char	*filename;
	char	*e_filename;
	struct s_ast *cmd;
	int	mode;
	int fd;
	bool	is_output;
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
}	t_ast;

typedef struct s_data
{
	char **env;
	char	*new_input;
	int	nb_cmd;
	bool	s_quote;
	bool	d_quote;
//	t_token *token;
//	t_ast	*redir;
}	t_data;


/* Test */
void print_env (t_data *data);

/* Init_data */
int	init_data(t_data **data, char **env);

/* Parse */
int	parse_input(t_data *data, char *input);
t_ast	*parse_pipe(char **s_input, char *e_input, t_data *data);


/* Utils_quotes */
bool	open_quotes(char *input, t_data *data);
int	is_single_quote(char *input, char **new_input, int index);
int	is_double_quotes(char *input, char **new_input, int index);
void	check_quotes(char c, t_data *data);
bool	contain_quote(char *str, char *quote);
bool	is_quote(char c);



/* Dollar */
char	*replace_dollar(char **input, t_data *data);

/* Utils_parse */
bool	is_symbol(char c);
bool	is_whitespaces(char c);
char	*strjoin_char(char *src, char c);
bool	unclosed_pipe (char *input);
void	skipe_whistepaces(char **str);

/* Signals */
void	set_signals(void);

/* Create node */
t_ast	*create_cmd_node();
t_ast	*create_raw_node();
t_ast	*create_redir_node(int type, char *s_file, char *e_file, t_ast *cmd);
void	init_cmd(t_ast *node, char *s_token, char *e_token, int *i);
t_ast	*create_pipe_node(t_ast *left, t_ast *right);

/* Nulterminate */
t_ast	*nulterminate(t_ast *tree, t_data *data);
bool	is_builtin(char *cmd);


/* Token */
int	peek(char **s_input, char *e_input, char *c);
int	get_token(char **s_input, char *e_input, char **s_token, char **e_token);

/* Utils redir */
void	init_redir(int type, t_ast *node);
t_ast	*multiple_redir(t_ast *old_redir, t_ast *new_redir);
int	check_next_token(char *s_input, char *e_input);

int	error_exit(char *s);
void    free_data(t_data *data);

void	print_tree (t_ast *tree);
void	parse_tree(t_ast *tree);



#endif