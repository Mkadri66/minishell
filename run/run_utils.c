/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkadri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:36:07 by mkadri            #+#    #+#             */
/*   Updated: 2024/09/21 13:31:43 by mkadri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_error(char *error)
{
	perror(error);
	exit(1);
}

int get_env_list_size(t_env_node *env_list) {
    int size = 0;
    t_env_node *current = env_list;
    
    while (current != NULL) {
        size++;
        current = current->next;
    }
    return size;
}

char *get_env_value(t_env_node *env_list, const char *var_name) 
{
    t_env_node *current = env_list;

    while (current != NULL)
    {
        if (ft_strncmp(current->env_name, var_name, ft_strlen(var_name)) == 0 && current->env_name[strlen(var_name)] == '=') 
            return current->env_name + ft_strlen(var_name) + 1;
        current = current->next;
    }
    return NULL;
}

char **copy_env_list_to_array(t_env_node *env_list)
{
    int size;
    int i;
    char **env_copy;
    t_env_node *current;
    
    
    size = get_env_list_size(env_list);
    env_copy = malloc((size + 1) * sizeof(char *));
    if (env_copy == NULL) {
        perror("Failed to allocate memory for env_copy");
        return NULL;
    }
    current = env_list;
    i = 0;
    while (current != NULL)
    {
        env_copy[i] = ft_strdup(current->env_name);
        if (env_copy[i] == NULL) 
        {
            perror("Failed to duplicate environment variable");
            return NULL;
        }
        current = current->next;
        i++;
    }
    env_copy[i] = NULL;
    return env_copy;
}
