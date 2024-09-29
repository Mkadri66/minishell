/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkadri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:57:15 by mkadri            #+#    #+#             */
/*   Updated: 2023/10/23 18:39:07 by mkadri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*str_trim;

	start = 0;
	end = ft_strlen(s1);
	if (!s1 || !set)
		return (NULL);
	while (s1[start] != '\0' && ft_strchr(set, s1[start]))
		start++;
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	str_trim = (char *) malloc(sizeof(char) * (end - start + 1));
	if (!str_trim)
		return (NULL);
	ft_strlcpy(str_trim, s1 + start, (end - start + 1));
	return (str_trim);
}

/*
int	main()
{
	char str[] = ".!Salut.";
	char set[] = "!*.";

	ft_strtrim(str, set);
}
*/
