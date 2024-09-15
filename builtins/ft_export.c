/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkadri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:47:36 by mkadri            #+#    #+#             */
/*   Updated: 2024/09/14 11:36:21 by mkadri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void update_env_list(char *env_var, t_env_node **env_list)
{
    t_env_node *current;
    char **split_var;
    char **existing_var;
    
    if (!env_var)
        return;
    split_var = ft_split(env_var, '=');
    if (!split_var || !split_var[0] || !split_var[1])
    {
        ft_free_split(split_var);
        return;
    }
    current = *env_list;
    while (current != NULL)
    {
        existing_var = ft_split(current->env_name, '=');
        if (ft_strcmp(existing_var[0], split_var[0]) == 0)
        {
            free(current->env_name);
            current->env_name = ft_strjoin(split_var[0], "=");
            current->env_name = ft_strjoin(current->env_name, split_var[1]);
            ft_free_split(existing_var);
            ft_free_split(split_var);
            return;
        }
        ft_free_split(existing_var);
        current = current->next;
    }
    ft_free_split(split_var);
}

static int correct_format(char *str)
{
    int     i;

    i = 0;
    if(!(ft_isalpha(str[0])) && str[0] != '_')
        return (1);
    i++;
    while(str[i] != '=')
    {
        if(!(ft_isalpha(str[i])) && str[i] != '_' && !(ft_isalnum(str[i])))
            return (1);
        i++;
    }
    if (str[i] != '=')
        return (1);
    return(0);
}

void    ft_export(char **args, t_env_node **env_list)
{
    int i;

    i = 0;
    if(!args)
    {
        ft_env(*env_list);
        return ;
    }
    while(args[i])
    {    
        if (correct_format(args[i]) == 1)
        {
            printf("bash: export not a valid identifier\n");
            ft_free_split(args);
            return ;
        }
        if(is_in_list(args[i], env_list) == 0)
        {
            update_env_list(args[i], env_list);
        } else
            add_env_node(env_list, args[i]);
        i++;
    }
    ft_free_split(args);
}
