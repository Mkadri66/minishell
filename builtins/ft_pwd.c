/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkadri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:07:16 by mkadri            #+#    #+#             */
/*   Updated: 2024/09/03 17:12:25 by mkadri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    ft_pwd(char **cmd)
{
    char current_directory[1024];

    if(count_args(cmd) == 1)
        printf("%s\n", getcwd(current_directory, sizeof(current_directory)));
    else
        printf("too many arguments\n");
}