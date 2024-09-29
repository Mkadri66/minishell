/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkadri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 14:49:06 by mkadri            #+#    #+#             */
/*   Updated: 2023/10/07 14:09:56 by mkadri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int character)
{
	if (character >= 'a' && character <= 'z')
	{
		return (character - 32);
	}
	return (character);
}

/*
int	main()
{
	int result = ft_toupper(5);
	int result2 = toupper(5);

	printf("%d \n", result);
	printf("%d \n", result2);

	return(0);
}
*/