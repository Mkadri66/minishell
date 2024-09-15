/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkadri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:05:14 by mkadri            #+#    #+#             */
/*   Updated: 2024/09/15 11:44:48 by mkadri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_args_str(char *str)
{
    if(*str)
        return(1);
    int count = 0;
    char *token = strtok(str, " ");
    while (token != NULL)
    {
        count++;
        token = strtok(NULL, " ");
    }
    return count;
}

char **get_arguments_array(char *input)
{
    // Trouver le premier espace après la commande
    char *space_pos = strchr(input, ' ');
    if (space_pos == NULL)
        return NULL;

    // Passer après la commande
    space_pos++;

    // Compter les arguments
    int arg_count = 0;
    char *temp = strdup(space_pos);  // Créer une copie temporaire pour compter les arguments
    char *token = strtok(temp, " ");
    while (token != NULL)
    {
        arg_count++;
        token = strtok(NULL, " ");
    }
    free(temp); // Libérer la copie temporaire

    // Allouer la mémoire pour le tableau de chaînes
    char **args = malloc((arg_count + 1) * sizeof(char *));
    if (args == NULL)
        return NULL;

    // Découper et remplir le tableau des arguments
    int i = 0;
    token = strtok(space_pos, " ");
    while (token != NULL)
    {
        args[i] = strdup(token);  // Copier chaque argument dans le tableau
        i++;
        token = strtok(NULL, " ");
    }
    args[i] = NULL; // Terminer le tableau par NULL

    return args;
}

// Fonction pour libérer le tableau d'arguments
void free_arguments_array(char **args)
{
    int i = 0;
    while (args[i] != NULL)
    {
        free(args[i]);
        i++;
    }
    free(args);
}

int main(int argc, char **argv, char **envp)
{
    char *input;
    char **args;
    char **cmd;
    
    t_env_node *env_list = NULL;

    copy_env_to_list(&env_list, envp);

    while ((input = readline("Minishell> ")) != NULL) {
        if (*input) { 
            add_history(input);
            args = get_arguments_array(input);
            cmd = ft_split(input, ' ');
            if (ft_strcmp(input, "pwd") == 0)
                ft_pwd();
            else if (ft_strcmp(input, "env") == 0)
                ft_env(env_list);
            else if (ft_strcmp(cmd[0], "export") == 0)
                ft_export(args, &env_list);
            else if (ft_strcmp(cmd[0], "unset") == 0)
                ft_unset(args, &env_list);
            else if (ft_strcmp(cmd[0], "cd") == 0)
                ft_cd(args,&env_list);
            else if (ft_strcmp(cmd[0], "echo") == 0)
                ft_echo(args,&env_list);
            else if (ft_strcmp(cmd[0], "exit") == 0)
            {
                ft_free_split(cmd);
                ft_free_split(args);
                ft_exit(args,&env_list);
            }
            else   
            {
                ft_strcmp(input, "");
                continue;
            }
        }
    }
    if(env_list)
    {
        free_env_list(env_list);
        rl_clear_history();
    }
    // (void) cmd;
    (void) argc;
    (void) argv;
    return(0);
}