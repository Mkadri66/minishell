/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkadri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 18:37:24 by mkadri            #+#    #+#             */
/*   Updated: 2023/10/09 21:25:35 by mkadri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int searched_char)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	while (i >= 0)
	{
		if (str[i] == (char)searched_char)
			return ((char *) str + i);
		i--;
	}
	return (0);
}

/*
int	main()
{
	char *text = "Bienvenue";

	// printf("%s \n", ft_strrchr(text, 'e'));
	printf("%s \n", strrchr(text, 'e'));
}
*/
