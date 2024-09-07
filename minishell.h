/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkadri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:10:29 by mkadri            #+#    #+#             */
/*   Updated: 2024/09/07 14:46:45 by mkadri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <stdarg.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <ctype.h>
# include <stddef.h>
# include <readline/readline.h>
# include <readline/history.h>

// Env Struct 

typedef struct s_env_node {
    char *cmd;
    char **arguments;
    struct s_env_node *prev;
    struct s_env_node *next;
}   t_env_node;

// Env functions 

void print_env_list(t_env_node *head);
void copy_env_to_list(t_env_node **head, char **envp);
t_env_node *add_env_node(t_env_node **head, const char *env_name);
void remove_env_node(t_env_node **head, t_env_node *node_to_remove);
void free_env_list(t_env_node *head);

// Builtins and utils

void    ft_cd(char **cmd);
void    ft_pwd(void);
void    ft_env(t_env_node *env_node);
void    ft_export(char *input, t_env_node **env_list);
int     count_args(char **cmd);
int     ft_strcmp(char *s1, char *s2);
void    ft_free_split(char **split);

#endif