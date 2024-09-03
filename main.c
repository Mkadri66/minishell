/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkadri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:05:14 by mkadri            #+#    #+#             */
/*   Updated: 2024/09/03 17:06:23 by mkadri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main()
{
    char *input;
    char **cmd;

    while ((input = readline("Minishell> ")) != NULL) {
        if (*input) { 
            add_history(input);
        }
        cmd = ft_split(input, ' ');
        ft_pwd(cmd);
        //ft_cd(cmd);
    }
    (void) cmd;
    return(0);
}