/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:26:28 by ntalmon           #+#    #+#             */
/*   Updated: 2024/05/13 14:13:29 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exe_and_or(t_data *data, t_and_or *cmd)
{
	int		id;
	int		status;

	status = 0;
	id = fork();
	if (id < 0)
		error(ERROR_6, 1);
	if (cmd->type == AND)
		execute_and(data, cmd, id, status);
	else
		execute_or(data, cmd, id, status);
}

void	execute_and(t_data *data, t_and_or *cmd, int id, int status)
{
	if (id == 0)
		execute_cmd(cmd->left, data);
	else
		waitpid(0, &status, 0);
	g_signal = WEXITSTATUS(status);
	if (g_signal == 0)
	{
		id = fork();
		if (id == 0)
			execute_cmd(cmd->right, data);
		else
			waitpid(0, &status, 0);
		g_signal = WEXITSTATUS(status);
	}
	exit(g_signal);
}

void	execute_or(t_data *data, t_and_or *cmd, int id, int status)
{
	if (id == 0)
		execute_cmd(cmd->left, data);
	else
		waitpid(0, &status, 0);
	g_signal = WEXITSTATUS(status);
	if (g_signal != 0)
	{
		id = fork();
		if (id == 0)
			execute_cmd(cmd->right, data);
		else
			waitpid(0, &status, 0);
		g_signal = WEXITSTATUS(status);
	}
	exit(g_signal);
}
