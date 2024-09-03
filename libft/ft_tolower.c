/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkadri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 13:41:45 by mkadri            #+#    #+#             */
/*   Updated: 2023/10/07 14:09:53 by mkadri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int character)
{
	if (character >= 'A' && character <= 'Z')
	{
		return (character + 32);
	}
	return (character);
}

/*
int	main()
{
	int result = ft_tolower(69);
	int result2 = tolower(69);

	printf("%d \n", result);
	printf("%d \n", result2);

	return(0);
}
*/