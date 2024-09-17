/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:50:50 by momillio          #+#    #+#             */
/*   Updated: 2024/09/12 15:56:01 by momillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_singint(int signal)
{
	(void)signal;
	printf ("\n");
	rl_replace_line ("", 0);
	rl_newline ();
	rl_redisplay ();
}

void	set_signals(void)
{
	struct sigaction	signal;

	signal.sa_handler = handle_sigint;
	sigemptyset (&signal.sa_mask);
	signal.sa_flags = 0;
	sigaction (SIGINT, &signal, NULL);
	signal (SIGQUIT, SIG_IGN);
}
