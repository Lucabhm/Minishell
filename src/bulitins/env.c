/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 12:53:56 by ntalmon           #+#    #+#             */
/*   Updated: 2024/05/14 12:29:31 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	check_env_access(char *directory, char *cmd)
{
	if (directory)
	{
		if (!access(directory, F_OK))
		{
			if (!access(directory, X_OK))
				return (error_msg_without_e(cmd, directory,
						"Permission denied", 1));
			else
				return (error_msg_without_e(cmd, directory,
						"No such file or directory", 1));
		}
		else
			return (error_msg_without_e(cmd, directory,
					"No such file or directory", 1));
	}
	g_signal = 0;
}

void	exe_env(t_var *envs, t_exe *cmd)
{
	t_var	*ptr;

	ptr = envs;
	check_env_access(cmd->argv[1], cmd->argv[0]);
	if (envs == NULL || envs->name == NULL)
	{
		printf("Keine Umgebungsvariablen vorhanden.\n");
		return ;
	}
	if (cmd->argv[1] == NULL)
	{
		while (ptr != NULL)
		{
			if (ptr->value != NULL)
				printf("%s=%s\n", ptr->name, ptr->value);
			ptr = ptr->nxt;
		}
	}
}
