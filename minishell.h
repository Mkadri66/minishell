/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkadri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:10:29 by mkadri            #+#    #+#             */
/*   Updated: 2024/09/29 11:09:54 by mkadri           ###   ########.fr       */
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
# include <signal.h>
# include <ctype.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>

extern int	g_exit_status;

typedef struct s_ast t_ast;

typedef enum s_token_type
{
	CMD,	
	PIPE,		// "|"
	REDIR,
	INP_REDIR,	// "<"
	OUT_REDIR,	// ">"
	HEREDOC,		// "<<"
	APPEND,		// ">>"
	DOLLARS,		// "$"
	ARG,
	SQ,		// '
	DQ,		// "
}	t_token_type;

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
	t_ast *left;
	t_ast *right;
 }	t_pipe;
 
 typedef struct s_redir
 {
	t_token_type	type;
	int		r_type;
	t_ast	*cmd;
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


typedef struct s_data
{
	char **env;
	char	*new_input;
	int		nb_cmd;
	int		stdin_cpy;
	int		stdout_cpy;
	bool	s_quote;
	bool	d_quote;
	t_token *token;
	t_ast	*tree;
	t_ast	*redir;
}	t_data;



// Env Struct 

typedef struct s_env_node {
    char *env_name;
    struct s_env_node *prev;
    struct s_env_node *next;
}   t_env_node;

// Env functions 

void print_env_list(t_env_node *head);
void copy_env_to_list(t_env_node **head, char **envp);
t_env_node *add_env_node(t_env_node **head, const char *env_name);
void update_env_list(char *env_var, t_env_node **env_list);
void remove_env_node(const char *var_name, t_env_node **env_list);
void free_env_list(t_env_node *head);
int is_in_list(char *var, t_env_node **env_list);
int	replace_env_var(t_env_node *current, char **split_var);
int is_shlvl_present(t_env_node **env_list);
bool	valid_num_content(char *str);
int increase_lvl(t_env_node **env_list);
void increase_shell_lvl(t_env_node **env_list);


// Builtins and utils

void    ft_pwd(void);
void    ft_env(t_env_node *env_list);
void    ft_unset(char **args, t_env_node **env_list);
void    ft_export(char **args, t_env_node **env_list);
void    ft_cd(char **args, t_env_node **env_list);
void    ft_echo(char **args, t_env_node **env_list);
void    ft_exit(char **args, t_env_node **env_list);
void    run_builtins(char *cmd, char **args, t_env_node **env_list);
int     count_args(char **cmd);
int     ft_strcmp(const char *s1,const char *s2);
void    ft_free_split(char **split);
bool	is_empty_quotes(char *str);
bool	is_quotes(char c);

// Runs

void	run_tree(t_ast *tree, t_data *data, t_env_node **env_list);
void    run_exec(t_ast *tree, t_env_node **env_list);
void	run_redir(t_ast *tree, t_data *data, t_env_node **env_list);
int		run_pipe(t_ast *tree, t_data *data, t_env_node **env_list);
char	*get_env_value(t_env_node *env_list, const char *var_name);
char	**copy_env_list_to_array(t_env_node *env_list);
int		ft_fork(void);
void	ft_error(char *error);
void	handle_line(char *line, int file);
int		is_line_delimiter(char *line, t_redir *redir_node);
void	dup_right(int *fd);
void	ft_heredoc(t_redir *redir_node);
void	run_heredoc(t_redir *redir_node);
void	reopen_stdin_stdout(int fd);
void	check_builtin_and_run(t_ast *tree, t_data *data, t_env_node **env_list);


#endif