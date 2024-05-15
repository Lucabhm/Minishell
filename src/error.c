/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:56:36 by lbohm             #+#    #+#             */
/*   Updated: 2024/05/13 16:37:17 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	error_msg_without_e(char *cmd, char *msg, char *msg2, int error_code)
{
	g_signal = error_code;
	ft_putstr_fd("minishell: ", 2);
	if (cmd)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(msg, 2);
	if (msg2)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(msg2, 2);
	}
	ft_putstr_fd("\n", 2);
}

void	error_msg(char *cmd, char *msg, char *msg2, int error_code)
{
	g_signal = error_code;
	ft_putstr_fd("minishell: ", 2);
	if (cmd)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(msg, 2);
	if (msg2)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(msg2, 2);
	}
	ft_putstr_fd("\n", 2);
	exit(g_signal);
}

void	error(char *msg, int error_code)
{
	g_signal = error_code;
	ft_putstr_fd("minishell: ", 2);
	perror(msg);
	exit(g_signal);
}

char	*error_quotes(int par, int double_q, int single_q, char *input)
{
	if (par != 0 || double_q == 1 || single_q == 1)
	{
		if (par != 0)
			error_msg_without_e(NULL, "unclosed parenthesis", NULL, 2);
		else
			error_msg_without_e(NULL, "unclosed quote", NULL, 1);
		return (free(input), NULL);
	}
	return (input);
}
