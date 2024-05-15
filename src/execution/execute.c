/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:04:24 by lbohm             #+#    #+#             */
/*   Updated: 2024/05/14 12:21:20 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exe_execve(t_data *data, t_exe *cmd)
{
	check_for_bultin(data, cmd);
	data->path_exe = check_for_access(*data, cmd->argv);
	if (!data->path_exe)
		error_msg(cmd->argv[0], "command not found", NULL, 127);
	if (execve(data->path_exe, cmd->argv, data->cmd_path) == -1)
		error_msg(cmd->argv[0], "command not found", NULL, 127);
}

void	check_for_bultin(t_data *data, t_exe *cmd)
{
	if (!ft_strcmp(cmd->argv[0], "export"))
	{
		exe_export_export(data, cmd);
		exe_export_env(data, cmd);
	}
	else if (!ft_strcmp(cmd->argv[0], "env") || !ft_strcmp(cmd->argv[0], "ENV"))
		exe_env(data->envs, cmd);
	else if (!ft_strcmp(cmd->argv[0], "unset"))
		exe_unset(data, cmd);
	else if (!ft_strcmp(cmd->argv[0], "echo"))
		exe_echo(cmd);
	else if (!ft_strcmp(cmd->argv[0], "pwd"))
		exe_pwd();
	else if (!ft_strcmp(cmd->argv[0], "exit"))
		exe_exit(*data, cmd);
	else if (!ft_strcmp(cmd->argv[0], "cd"))
	{
		exe_cd(data, cmd);
		exit(g_signal);
	}
	else
		return ;
	exit(g_signal);
}

void	exe_redir(t_data *data, t_redir *cmd)
{
	int		fdd;

	fdd = 0;
	if (cmd->fd == 0)
	{
		fdd = open(cmd->f, cmd->mode);
		if (fdd < 0)
			error(cmd->f, 1);
		else if (dup2(fdd, STDIN_FILENO) == -1)
			error(ERROR_3, 1);
	}
	else
	{
		fdd = open(cmd->f, cmd->mode, 0644);
		if (fdd < 0)
			error(cmd->f, 1);
		if (dup2(fdd, STDOUT_FILENO) == -1)
			error(ERROR_3, 1);
	}
	if (!cmd->cmd)
		exit(g_signal);
	execute_cmd(cmd->cmd, data);
}

void	handle_input(t_data *data, t_here_doc *cmd)
{
	int		fdd;
	char	*input;

	input = "";
	fdd = open("here_doc.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fdd < 0)
		error("here_doc.txt", 1);
	while (input)
	{
		input = readline("\001\e[1;33m\002> \001\e[0m\002");
		input = check_for_schar_2(input, *data);
		if (!input || !ft_strcmp(input, cmd->l))
			break ;
		ft_putstr_fd(ft_strjoin(input, "\n"), fdd);
		free(input);
	}
	free(input);
	close(fdd);
}

void	exe_here_doc(t_data *data, t_here_doc *cmd)
{
	int		fdd;

	handle_input(data, cmd);
	fdd = open("here_doc.txt", O_RDONLY);
	if (dup2(fdd, STDIN_FILENO) == -1)
		error(ERROR_3, 1);
	if (!cmd->cmd)
		exit(0);
	if (dup2(data->fdhere, STDOUT_FILENO) == -1)
		error(ERROR_3, 1);
	execute_cmd(cmd->cmd, data);
}
