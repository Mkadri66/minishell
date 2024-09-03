/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkadri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 19:26:33 by mkadri            #+#    #+#             */
/*   Updated: 2023/10/27 19:40:45 by mkadri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	int		j;
	int		s_len;
	char	*str_map;

	i = 0;
	j = 0;
	s_len = ft_strlen(s);
	str_map = (char *) malloc((sizeof(char) * (s_len + 1)));
	if (!str_map)
		return (NULL);
	while (s[i] != '\0')
	{
		str_map[j] = f(i, s[i]);
		i++;
		j++;
	}
	str_map[j] = '\0';
	return (str_map);
}
