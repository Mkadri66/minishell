/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkadri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:00:33 by mkadri            #+#    #+#             */
/*   Updated: 2023/10/19 17:32:56 by mkadri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *str1, char const *str2)
{
	int		total_size;
	char	*str_cat;
	int		i;
	int		j;

	i = 0;
	j = 0;
	total_size = ft_strlen(str1) + ft_strlen(str2);
	str_cat = malloc((total_size + 1) * sizeof(char));
	if (!str_cat || (!str1 || !str2))
		return (NULL);
	while (str1[i] != '\0')
		str_cat[j++] = str1[i++];
	i = 0;
	while (str2[i] != '\0')
		str_cat[j++] = str2[i++];
	str_cat[j] = '\0';
	return (str_cat);
}
/*
int main() {
    
    //char *ptr;
    char *text1 = "Bon";
    char *text2 = "jour";
    printf("%s",ft_strjoin(text1, text2));
    return 0;
}
*/