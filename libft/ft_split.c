/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkadri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 13:56:58 by mkadri            #+#    #+#             */
/*   Updated: 2023/11/01 18:01:59 by mkadri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int		i;
	int		words;

	i = 0;
	words = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			i++;
		}
		else
		{
			words++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (words);
}

static	int	free_words(char **str, int size)
{
	while (size--)
		free(str[size]);
	free(str);
	return (-1);
}

static	void	write_word(char *dest, const char *from, char c)
{
	int		i;

	i = 0;
	while (!(from[i] == c || from[i] == '\0'))
	{
		dest[i] = from[i];
		i++;
	}
	dest[i] = '\0';
}

static int	split_words(char **split, const char *str, char c)
{
	int		i;
	int		j;
	int		word;

	word = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == c || str[i] == '\0'))
			i++;
		else
		{
			j = 0;
			while ((str[i + j] == c || str[i + j] == '\0') == 0)
				j++;
			split[word] = (char *) malloc(sizeof(char) * (j + 1));
			if (split[word] == NULL)
				return (free_words(split, word));
			write_word(split[word], str + i, c);
			i += j;
			word++;
		}
	}
	return (0);
}

char	**ft_split(const char *s, char c)
{
	char	**str_splited;
	int		words;

	words = count_words(s, c);
	str_splited = (char **) malloc((words + 1) * sizeof(char *));
	if (!str_splited)
		return (NULL);
	str_splited[words] = 0;
	if (split_words(str_splited, s, c) == -1)
		return (NULL);
	return (str_splited);
}
