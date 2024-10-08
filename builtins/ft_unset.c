/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:47:36 by mkadri            #+#    #+#             */
/*   Updated: 2024/09/27 11:29:34 by momillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_unset(char **args, t_env_node **env_list)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		if (is_in_list(args[i], env_list) == 0)
			remove_env_node(args[i], env_list);
		i++;
	}
}
