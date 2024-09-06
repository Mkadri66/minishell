/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:05:14 by mkadri            #+#    #+#             */
/*   Updated: 2024/09/05 18:52:10 by momillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int input_empty(char *input)
{
    int i;

    i = -1;
    while (input[++i])
    {
        if (input[i] < 9 && input[i] > 13 && input[i] != 32)
            return (false);
    }
    return (true);
}


// Init global structure
// Copy env
/*  While boucle for readline : 
        check empty line
        add history
        parseline
        exec
        free : cmd & token
        init global signal
    clear history
    free global structure
*/

int main(int argc, char **argv, char **env)
{
    t_data  data;
    char    *input;

    if (!init_data (&data, env))
        return (1);
    while (1)
    {
        input = readline ("Minishell: ");
        if (!input)
            return (1); // free data, data.env
        if (input_empty (input))
            continue ;
        add_history (input);
        parse_input (&data, input);
    }
    rl_clear_history ();
    argc++;
    argv++;
    return(0);
}