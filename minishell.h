/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:10:29 by mkadri            #+#    #+#             */
/*   Updated: 2024/09/05 22:29:17 by momillio         ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>

typedef enum s_token_type
{
	EXEC,	
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

/*typedef struct s_list
{
	char	*name;
	char	*value;
	struct s_list	*next;
}	t_list;*/

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
	int	input;
	int	output;
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
	t_token *token;
	t_ast	*tree;
}	t_data;


/* Test */
void print_env (t_data *data);

int	init_data(t_data *data, char **env);
bool	open_quotes(char *input);



#endif