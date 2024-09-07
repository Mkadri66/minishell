/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkadri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:05:14 by mkadri            #+#    #+#             */
/*   Updated: 2024/09/06 16:29:13 by mkadri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
    char *input;
    //char **cmd;
    t_env_node *env_list = NULL;

    copy_env_to_list(&env_list, envp);
    //=ft_env(env_list);

    while ((input = readline("Minishell> ")) != NULL) {
        if (*input) { 
            add_history(input);
        }
        //cmd = ft_split(input, ' ');
        if (ft_strcmp(input, "pwd") == 0)
            ft_pwd();
        else if (ft_strcmp(input, "env") == 0)
            ft_env(env_list);
        else if (ft_strncmp(input, "export",6) == 0)
            ft_export(input, &env_list);
    }
    free_env_list(env_list);
    rl_clear_history();
    // (void) cmd;
    (void) argc;
    (void) argv;
    return(0);
}