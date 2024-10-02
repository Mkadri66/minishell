/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momillio <momillio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:45:21 by momillio          #+#    #+#             */
/*   Updated: 2024/10/02 10:22:20 by momillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUN_H
# define RUN_H

# include "minishell.h"

/* Exec */
void	run_exec(t_ast *tree, t_env_node **env_list);

/* Pipe */
int		run_pipe(t_ast *tree, t_data *data, t_env_node **env_list);

/* Redir */
void	run_redir(t_ast *tree, t_data *data, t_env_node **env_list);
void	ft_heredoc(t_redir *redir_node);

/* Run_tree */
void	check_builtin_and_run(t_ast *tree, t_data *data, t_env_node **env_list);
void	run_tree(t_ast *tree, t_data *data, t_env_node **env_list);
int		ft_fork(void);

/* Run_utils_2 */
void	ft_error(char *error);
void	handle_line(char *line, int file);
int		is_line_delimiter(char *line, t_redir *redir_node);
void	dup_right(int *fd);

/* Run_utils */
int		get_env_list_size(t_env_node *env_list);
char	*get_env_value(t_env_node *env_list, const char *var_name);
int		fill_env_copy(t_env_node *env_list, char **env_copy);
char	**allocate_env_copy(int size);
char	**copy_env_list_to_array(t_env_node *env_list);

#endif