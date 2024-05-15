/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:56:03 by lbohm             #+#    #+#             */
/*   Updated: 2024/05/13 14:03:15 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_signals_heredoc(void)
{
	struct sigaction	sa;
	struct termios		te;

	ft_memset(&sa, 0, sizeof(sa));
	ft_memset(&te, 0, sizeof(te));
	tcgetattr(0, &te);
	te.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &te);
	sa.sa_handler = &control_c_heredoc;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
}

void	handle_signals(void)
{
	struct sigaction	sa;
	struct termios		te;

	ft_memset(&sa, 0, sizeof(sa));
	ft_memset(&te, 0, sizeof(te));
	tcgetattr(0, &te);
	te.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &te);
	sa.sa_handler = &control_c;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
}

void	handle_signals2(void)
{
	struct sigaction	sa;
	struct termios		te;

	ft_memset(&sa, 0, sizeof(sa));
	ft_memset(&te, 0, sizeof(te));
	tcgetattr(0, &te);
	te.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &te);
	sa.sa_handler = &control_c_2;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
}
