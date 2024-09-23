/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkadri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:51:07 by mkadri            #+#    #+#             */
/*   Updated: 2024/09/21 11:44:58 by mkadri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	check_option(char *option)
{
	int	i;

	i = 1;
	if (option[0] != '-' || ft_strlen(option) < 2)
		return (false);
	while (option[i])
	{
		if (option[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

bool	is_quotes(char c)
{
	if (c == '\'')
		return (true);
	return (false);
}

void	print_in_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\'')
	{
		printf("%c", str[i]);
		i++;
	}
}

void	print_args(char **args, bool option)
{
	int	i;

	i = 0;
	if (option)
		i++;
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
}

void	ft_echo(char **args, t_env_node **env_list)
{
	bool	option;

	if (!args)
	{
		printf("\n");
		return ;
	}
	option = check_option(args[0]);
	print_args(args, option);
	if (!option)
		printf("\n");
	(void) env_list;
}
