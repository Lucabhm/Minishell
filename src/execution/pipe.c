/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:22:44 by lbohm             #+#    #+#             */
/*   Updated: 2024/05/13 17:59:01 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exe_pipe(t_data *data, t_pipe *cmd)
{
	data->childnbr = 0;
	if (cmd->left->type == PIPE)
		pipe_middle(data, cmd->left, 0);
	else
		fork_and_exe(data, cmd->left, 0);
	if (dup2(data->fdout, STDOUT_FILENO) == -1)
		error(ERROR_3, 1);
	if (cmd->right->type == PIPE)
		pipe_middle(data, cmd->right, 1);
	else
		fork_and_exe(data, cmd->right, 1);
	wait_for_child(data);
	exit(g_signal);
}

void	pipe_middle(t_data *data, t_cmd *cmd, int last)
{
	if (cmd->type == PIPE)
	{
		pipe_middle(data, ((t_pipe *)cmd)->left, 0);
		pipe_middle(data, ((t_pipe *)cmd)->right, last);
	}
	else
	{
		fork_and_exe(data, cmd, last);
		return ;
	}
	return ;
}

void	fork_and_exe(t_data *data, t_cmd *cmd, int last)
{
	pid_t	pid;
	int		pfd[2];

	if (pipe(pfd) == -1)
		error(ERROR_5, 1);
	pid = fork();
	if (pid == -1)
		error(ERROR_6, 1);
	if (pid == 0)
		child_process(pfd, data, cmd, last);
	if (pid > 0)
	{
		close(pfd[1]);
		close(data->fdpipe);
		data->fdpipe = pfd[0];
		data->child[data->childnbr] = pid;
		data->childnbr++;
	}
	if (cmd->type == HERE)
	{
		wait_for_child(data);
		data->childnbr = 0;
	}
	return ;
}

void	child_process(int *pfd, t_data *data, t_cmd *cmd, int last)
{
	char	buffer[BUFFER_SIZE];

	close(pfd[0]);
	if (dup2(data->fdpipe, STDIN_FILENO) == -1)
		error(ERROR_3, 1);
	if (cmd->type == HERE)
	{
		while (read(data->fdpipe, buffer, BUFFER_SIZE) > 0)
			get_next_line(data->fdpipe);
		close(data->fdpipe);
		if (dup2(data->fdin, STDIN_FILENO) == -1)
			error(ERROR_3, 1);
		if (last == 1)
			data->fdhere = data->fdout;
		else
			data->fdhere = pfd[1];
		if (dup2(data->fdout, STDOUT_FILENO) == -1)
			error(ERROR_3, 1);
	}
	else if (last == 0)
	{
		if (dup2(pfd[1], STDOUT_FILENO) == -1)
			error(ERROR_3, 1);
	}
	execute_cmd(cmd, data);
}

void	wait_for_child(t_data *data)
{
	int	status;
	int	i;

	i = 0;
	while (i < data->childnbr)
	{
		if (waitpid(data->child[i], &status, 0) == -1)
			error(ERROR_9, 1);
		g_signal = WEXITSTATUS(status);
		i++;
	}
}
