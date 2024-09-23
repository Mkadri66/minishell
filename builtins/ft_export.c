/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkadri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:47:36 by mkadri            #+#    #+#             */
/*   Updated: 2024/09/21 12:06:12 by mkadri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char **split_env_var(char *env_var)
{
    char **split_var;

    if (!env_var)
        return NULL;
    split_var = ft_split(env_var, '=');
    if (!split_var || !split_var[0] || !split_var[1])
    {
        ft_free_split(split_var);
        return NULL;
    }
    return split_var;
}

void update_existing_var(char **split_var, t_env_node *current)
{
    char **existing_var;

    while (current != NULL)
    {
        existing_var = ft_split(current->env_name, '=');
        if (ft_strcmp(existing_var[0], split_var[0]) == 0)
        {
            free(current->env_name);
            current->env_name = ft_strjoin(split_var[0], "=");
            current->env_name = ft_strjoin(current->env_name, split_var[1]);
            ft_free_split(existing_var);
            return;
        }
        ft_free_split(existing_var);
        current = current->next;
    }
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
