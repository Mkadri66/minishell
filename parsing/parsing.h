/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:57:57 by momillio          #+#    #+#             */
/*   Updated: 2024/09/27 16:20:15 by momillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include "../minishell.h"

/* Create_node */
void	init_cmd(t_ast *node, char *s_token, char *e_token, int *i);
t_ast	*create_cmd_node(void);
t_ast	*create_redir_node(int type, char *s_file, char *e_file, t_ast *cmd);
t_ast	*create_pipe_node(t_ast *left, t_ast *right);

/* Dollar */
char	*replace_dollar(char **input, t_data *data);

/* Error */
void	free_data(t_data *data);
int	error_exit(char *s);

/* Init_data */
int	init_data(t_data **data, t_env_node **env_list, char **env, int argc);

/* Lexing */
int	parse_input(t_data *data, char **input, t_ast **tree);

/* Nulterminate */
t_ast	*nulterminate(t_ast *tree, t_data *data);

/* Parsing */
t_ast	*parse_pipe(char **s_input, char *e_input, t_data *data);

/* Token */
int	get_token(char **s_input, char *e_input, char **s_token, char **e_token);

/* Utils_parse */
bool	unclosed_pipe(char *input);
bool	is_whitespaces(char c);
void	skipe_whistepaces(char **str);
bool	is_symbol(char c);
char	*strjoin_char(char *src, char c);

/* Utils_quote */
bool	is_quote(char c);
void	check_quotes(char c, t_data *data);
bool	open_quotes(char *input, t_data *data);
bool	contain_quote(char *str, char *quote);

/* Utils_redir */
void	init_redir(int type, t_ast *node);
t_ast	*multiple_redir(t_ast *old, t_ast *new);
int	check_next_token(char *s_input, char *e_input);

/* Test */
void	print_env(t_data *data);
void	print_tree(t_ast *tree);
void	parse_tree(t_ast *tree);

#endif
