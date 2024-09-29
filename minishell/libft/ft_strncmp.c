/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkadri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 17:07:54 by mkadri            #+#    #+#             */
/*   Updated: 2024/05/15 09:08:33 by mkadri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *first, const char *second, size_t lenght)
{
	unsigned long	i;

	i = 0;
	while ((first[i] != '\0' || second[i] != '\0') && i < lenght)
	{
		if (first[i] != second[i])
		{
			return ((unsigned char) first[i] - (unsigned char) second[i]);
		}
		i++;
	}
	return (0);
}
/*
int	main()
{
	char *first = "Hello";
	char *second = "Hello";

	printf("%d \n", ft_strncmp(first, second, 5));
	printf("%d \n", strncmp(first, second, 5));
}
*/