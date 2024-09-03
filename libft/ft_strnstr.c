/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkadri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 20:48:57 by mkadri            #+#    #+#             */
/*   Updated: 2023/10/23 15:25:13 by mkadri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	little_size;

	i = 0;
	j = 0;
	little_size = ft_strlen(little);
	if (!little || little_size == 0)
		return ((char *)big);
	while (big[i] != '\0' && i < len)
	{
		if (big[i] == little[j])
		{
			j++;
		}
		else
		{
			i -= j;
			j = 0;
		}
		if (j == little_size)
			return ((char *)&big[i - j + 1]);
		i++;
	}
	return (NULL);
}
