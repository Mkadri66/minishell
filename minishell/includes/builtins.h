/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momillio <momillio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:17:46 by momillio          #+#    #+#             */
/*   Updated: 2024/09/30 17:00:54 by momillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

/* Builtins_utils */
bool	is_empty_quotes(char *str);
int		count_args(char **cmd);
int		ft_strcmp(const char *s1, const char *s2);
void	ft_free_split(char **split);
int		is_in_list(char *var, t_env_node **env_list);

/* Env_utils_2 */
char	**split_and_validate(char *env_var);
int		replace_env_var(t_env_node *current, char **split_var);
void	update_env_list(char *env_var, t_env_node **env_list);

/* Env_utils_3 */
void	increase_shell_lvl(t_env_node **env_list);

/* Env_utils */
void		print_env_list(t_env_node *head);
void		copy_env_to_list(t_env_node **head, char **envp);
t_env_node	*add_env_node(t_env_node **head, const char *env_name);
void		remove_env_node(const char *var_name, t_env_node **env_list);
void	free_env_list(t_env_node **head);


/* Ft_cd */
void	ft_cd(char **args, t_env_node **env_list);

/* Ft_echo */
void	ft_echo(char **args, t_env_node **env_list);
void	print_in_quote(char *str);
bool	is_quotes(char c);

/* Ft_env */
void	ft_env(t_env_node *env_node);

/* Ft_exit */
int	is_input_exit(char *input, t_data *data);
void	ft_exit(char **input, t_data *data);

/* Ft_export */
void	ft_export(char **args, t_env_node **env_list);

/* Ft_pwd */
void	ft_pwd(void);

/* Ft_unset */
void	ft_unset(char **args, t_env_node **env_list);

/* Run_builtins */
void	run_builtins(char *cmd, char **args, t_env_node **env_list);

#endif