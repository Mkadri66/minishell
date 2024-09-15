/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkadri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:10:29 by mkadri            #+#    #+#             */
/*   Updated: 2024/09/15 08:31:41 by mkadri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <stdarg.h>
# include <string.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdio.h>
# include <ctype.h>
# include <stddef.h>
# include <readline/readline.h>
# include <readline/history.h>

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

// Builtins and utils

void    ft_pwd(void);
void    ft_env(t_env_node *env_node);
void    ft_unset(char **args, t_env_node **env_list);
void    ft_export(char **args, t_env_node **env_list);
void    ft_cd(char **args, t_env_node **env_list);
void    ft_echo(char **args, t_env_node **env_list);
void    ft_exit(char **args, t_env_node **env_list);
int     count_args(char **cmd);
int     ft_strcmp(const char *s1,const char *s2);
void    ft_free_split(char **split);

#endif