/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkadri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 21:07:30 by mkadri            #+#    #+#             */
/*   Updated: 2023/10/23 18:07:53 by mkadri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	size_t	str_size;
	size_t	copy_size;
	char	*substr;

	if (!str)
		return (NULL);
	str_size = ft_strlen(str);
	copy_size = 0;
	if (start >= str_size)
		return (ft_strdup(""));
	if (start < str_size)
		copy_size = str_size - start;
	if (copy_size > len)
		copy_size = len;
	substr = (char *)malloc(sizeof(char) * copy_size + 1);
	if (!substr)
		return (0);
	ft_strlcpy(substr, str + start, copy_size + 1);
	return (substr);
}
