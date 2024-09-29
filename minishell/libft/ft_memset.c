/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkadri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:39:21 by mkadri            #+#    #+#             */
/*   Updated: 2023/10/11 17:51:08 by mkadri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *array, int value, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		*((unsigned char *)(array + i)) = (unsigned char)value;
		i++;
	}
	return (array);
}

/*
int	main()
{
	char array [] = "Salut le sang";


	int i = 0;
	
	ft_memset(array, 0, 13);
	//memset(array,5,6);

	while(i < 13)
	{
		printf("%d \n", array[i]);
		i++;
	}	
		
}
*/
