/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momillio <momillio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:50:50 by momillio          #+#    #+#             */
/*   Updated: 2024/09/30 16:01:55 by momillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	handle_sigint(int signal)
{
	(void)signal;
	printf ("\n");
	rl_replace_line ("", 0);
	rl_on_new_line ();
	rl_redisplay ();
}

void	set_signals(void)
{
	struct sigaction	sign;

	sign.sa_handler = handle_sigint;
	sigemptyset (&sign.sa_mask);
	sign.sa_flags = 0;
	sigaction (SIGINT, &sign, NULL);
	signal (SIGQUIT, SIG_IGN);
}
