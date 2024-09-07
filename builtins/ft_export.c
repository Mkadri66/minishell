/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkadri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:47:36 by mkadri            #+#    #+#             */
/*   Updated: 2024/09/06 17:17:52 by mkadri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int correct_format(char *str)
{
    char **split_str;
    int     i;

    split_str = ft_split(str, '=');
    i = 0;
    if(!(ft_isalpha(split_str[0][0])) && split_str[0][0] != '_')
        return (1);
    while(split_str[0][i])
    {
        if(!(ft_isalpha(split_str[0][i])) && split_str[0][i] != '_' && !(ft_isalnum(split_str[0][i])))
            return (1);
        i++;
    }
    free(split_str);
    return(0);
}

int is_in_list(char *var, t_env_node **env_list)
{
    char **var_name_input;
    char **var_name_env;
    t_env_node *current;

    var_name_input = ft_split(var, '=');
    current = *env_list;
    while (current != NULL)
    {
        var_name_env = ft_split(current->env_name, '=');
        if(ft_strcmp(var_name_input[0], var_name_env[0]) == 0)
            return (0);
        ft_free_split(var_name_env);
        current = current->next;
    }
    ft_free_split(var_name_input);
    return (1);
}

void    ft_export(char *input, t_env_node **env_list)
{
    char **args;
    
    args = ft_split(input, ' ');
    if (!args || !args[1])
    {
        printf("argument error\n");
        free(args);
        return ;
    }
    if (correct_format(args[1]) == 1)
    {
        printf("incorrect variable name\n");
        free(args);
        return ;
    }
    else if(is_in_list(args[1], env_list) == 0)
    {
        printf("Update needed\n");
        free(args);
        return ;
    }
    //verifier si la variable n est pas vide
    add_env_node(env_list, args[1]);
    free(args);
}
