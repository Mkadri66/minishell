/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momillio <momillio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:51:07 by mkadri            #+#    #+#             */
/*   Updated: 2024/09/29 18:26:51 by momillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"
# include "../includes/parsing.h"

void	ft_exit(char **args, t_env_node **env_list)
{
	ft_free_split(args);
	free_env_list(env_list);
	exit (1);
}
