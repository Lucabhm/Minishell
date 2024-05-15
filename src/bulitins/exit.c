/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 12:55:20 by ntalmon           #+#    #+#             */
/*   Updated: 2024/05/14 12:37:27 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exit_free(t_data data)
{
	if (data.cmd_path)
		freeupm(data.cmd_path);
	if (data.in)
		free(data.in);
	if (data.s_n)
		free_ast(data.s_n);
	if (data.envs)
		free_lst(&data.envs);
	if (data.export)
		free_lst(&data.export);
	if (data.path_exe)
		free(data.path_exe);
}

void	exe_exit(t_data data, t_exe *cmd)
{
	if (cmd)
	{
		if (cmd->argv[1])
		{
			if (is_word(cmd->argv[1]) && !cmd->argv[2])
				g_signal = ft_atoi(cmd->argv[1]);
			if (cmd->argv[1][1] == '-' || cmd->argv[1][1] == '+')
				error_msg(cmd->argv[0], cmd->argv[1],
					"numeric argument required", 255);
			else if (!is_word(cmd->argv[1]))
				error_msg(cmd->argv[0], cmd->argv[1],
					"numeric argument required", 255);
			else if (cmd->argv[2])
				error_msg(cmd->argv[0], cmd->argv[1],
					"too many arguments", 1);
		}
	}
	exit_free(data);
	rl_clear_history();
	c_fds(3);
	exit(g_signal);
}

int	is_word(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]))
			i++;
		else
			return (1);
	}
	return (0);
}

void	c_fds(int i)
{
	while (i < 10240)
	{
		close(i);
		i++;
	}
}
