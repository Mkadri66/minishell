/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 22:39:31 by momillio          #+#    #+#             */
/*   Updated: 2024/09/27 11:09:08 by momillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	unclosed_pipe(char *input)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if (input[i] == '|')
		{
			i++;
			while (input[i] && ((input[i] >= 9 && input[i] <= 13) \
					|| input[i] == 32))
				i++;
			if (input[i] == '|')
				continue ;
			if (!input[i])
				//message d'erreur "unclosed pipe"
				return (true);
		}
	}
	return (false);
}

bool	is_whitespaces(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (true);
	return (false);
}

void	skipe_whistepaces(char **str)
{
	while (**str && is_whitespaces (**str))
		(*str)++;
}

bool	is_symbol(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (true);
	return (false);
}

char	*strjoin_char(char *src, char c)
{
	char	*str;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen (src);
//	printf ("len = %d\n", len);
	str = malloc (sizeof (char) * (len + 2));
	if (!str)
	{
		free (src);
		return (NULL);
	}
	while (src[i])
	{
		str[i] = src[i];
		i++;
	}
	str[i] = c;
	str[++i] = '\0';
	free (src);
	return (str);
}
