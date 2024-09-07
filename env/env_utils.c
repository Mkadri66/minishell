/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkadri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:20:09 by mkadri            #+#    #+#             */
/*   Updated: 2024/09/04 21:34:47 by mkadri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void print_env_list(t_env_node *head) 
{
    t_env_node *current = head;
    while (current != NULL) 
    {
        printf("%s\n", current->env_name);
        current = current->next;
    }
}

void copy_env_to_list(t_env_node **head, char **envp)
{
    while (*envp != NULL)
    {
        add_env_node(head, *envp);
        envp++;
    }
}

t_env_node *add_env_node(t_env_node **head, const char *env_name) 
{
    t_env_node *new_node = (t_env_node*)malloc(sizeof(t_env_node));
    if (!new_node) {
        perror("Failed to allocate memory");
        return NULL;
    }
    new_node->env_name = strdup(env_name);
    if (!new_node->env_name) 
    {
        free(new_node);
        perror("Failed to copy environment variable");
        return NULL;
    }
    new_node->next = *head;
    new_node->prev = NULL;
    if (*head != NULL)
        (*head)->prev = new_node;
    *head = new_node;
    return new_node;
}


void remove_env_node(t_env_node **head, t_env_node *node_to_remove) {
    if (node_to_remove == NULL || head == NULL || *head == NULL) {
        return;
    }
    if (node_to_remove->prev != NULL)
        node_to_remove->prev->next = node_to_remove->next;
    else
        *head = node_to_remove->next;
    if (node_to_remove->next != NULL)
        node_to_remove->next->prev = node_to_remove->prev;
    free(node_to_remove->env_name);
    free(node_to_remove);
}


void free_env_list(t_env_node *head)
{
    t_env_node *current = head;
    t_env_node *next_node;

    while (current != NULL) 
    {
        next_node = current->next;
        free(current->env_name);
        free(current);
        current = next_node;
    }
}
