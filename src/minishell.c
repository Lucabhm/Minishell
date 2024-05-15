/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 12:53:56 by lucabohn          #+#    #+#             */
/*   Updated: 2024/05/14 16:23:09 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_signal = 0;

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	pid_t	id;

	id = 0;
	if (argc == 1 && !argv[1])
	{
		signal(SIGQUIT, SIG_IGN);
		init_data(&data, env);
		welcome_message();
		while (1)
			start_point(&data, id);
	}
	else
		error_msg(NULL, "don't allow args", NULL, 1);
	return (0);
}

void	execute_command(t_data *data, pid_t id)
{
	int	status;

	id = fork();
	if (id < 0)
		error(ERROR_6, 1);
	else if (id == 0)
		execute_cmd(data->s_n, data);
	else if (id > 0)
	{
		waitpid(0, &status, 0);
		if (g_signal == 0)
			g_signal = WEXITSTATUS(status);
		unlink("here_doc.txt");
	}
}

void	start_point(t_data *data, pid_t id)
{
	handle_signals();
	data->in = print_prompt();
	if (data->in)
	{
		handle_signals2();
		data->in = check_input(data->in, data);
		if (data->in && ft_strcmp(data->in, ""))
		{
			token(data->in, data);
			if (!check_builtin_main(data) && data->s_n)
				execute_command(data, id);
		}
		free_for_new_cmd(data);
	}
	else
		exe_exit(*data, NULL);
}

int	check_builtin_main(t_data *data)
{
	t_exe	*cmd;

	if (data->s_n && data->s_n->type == EXECVE)
	{
		cmd = (t_exe *)data->s_n;
		if (!ft_strcmp(cmd->argv[0], "export"))
		{
			exe_export_export(data, cmd);
			exe_export_env(data, cmd);
			sort_export(&data->export);
		}
		else if (!ft_strcmp(cmd->argv[0], "exit"))
			exe_exit(*data, cmd);
		else if (!ft_strcmp(cmd->argv[0], "unset"))
			exe_unset(data, cmd);
		else if (!ft_strcmp(cmd->argv[0], "cd"))
			exe_cd(data, cmd);
		else
			return (0);
		return (1);
	}
	return (0);
}

void	execute_cmd(t_cmd *t, t_data *data)
{
	if (t->type == EXECVE)
		exe_execve(data, (t_exe *)t);
	else if (t->type == PIPE)
		exe_pipe(data, (t_pipe *)t);
	else if (t->type == REDIR)
		exe_redir(data, (t_redir *)t);
	else if (t->type == HERE)
	{
		handle_signals_heredoc();
		exe_here_doc(data, (t_here_doc *)t);
	}
	else if (t->type == AND || t->type == OR)
		exe_and_or(data, (t_and_or *)t);
}
