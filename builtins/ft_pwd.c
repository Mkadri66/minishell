/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:07:16 by mkadri            #+#    #+#             */
/*   Updated: 2024/09/27 11:29:32 by momillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_pwd(void)
{
	char	current_directory[1024];

	getcwd(current_directory, sizeof(current_directory));
	printf("%s\n", current_directory);
}
