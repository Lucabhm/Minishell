/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 12:49:32 by ntalmon           #+#    #+#             */
/*   Updated: 2024/05/08 19:37:15 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	update_pwd(t_var *data)
{
	t_var	*ptr;

	ptr = data;
	while (ptr != NULL)
	{
		if (!(ft_strncmp(ptr->name, "PWD", 3)))
		{
			free(ptr->value);
			ptr->value = prompt_cwd();
		}
		ptr = ptr->nxt;
	}
}

void	update_oldpwd(t_var *data)
{
	t_var	*ptr;
	int		pwd_found;
	t_var	*new_node;

	ptr = data;
	pwd_found = 0;
	new_node = ft_lstnew_new(ft_strdup("OLDPWD"), NULL);
	if (get_env("PWD", &ptr))
		pwd_found = 1;
	ptr = data;
	update_oldpwd_value(ptr, pwd_found, new_node, data);
}

void	update_oldpwd_value(t_var *ptr, int pwd_found,
		t_var *new_node, t_var *data)
{
	while (ptr != NULL)
	{
		if (!(ft_strncmp(ptr->name, "OLDPWD", 6)))
		{
			free_lst(&new_node);
			if (pwd_found)
			{
				free(ptr->value);
				ptr->value = prompt_cwd();
			}
			else
			{
				free(ptr->value);
				ptr->value = ft_strdup("");
			}
			return ;
		}
		ptr = ptr->nxt;
	}
	if (pwd_found)
		new_node->value = prompt_cwd();
	else
		new_node->value = ft_strdup("");
	ft_lstadd_back_new(&data, new_node);
}

void	check_cd_access(char *directory, char *cmd)
{
	if (directory)
	{
		if (access(directory, F_OK) != -1)
		{
			if (access(directory, X_OK) != -1)
			{
				g_signal = 0;
				return ;
			}
			else
				error_msg_without_e(cmd, directory, "Not a directory", 1);
		}
		else
			error_msg_without_e(cmd, directory, "No such file or directory", 1);
	}
}

void	exe_cd(t_data *data, t_exe *cmd)
{
	if (cd_only(data, cmd) == 0 || cd_minus(data, cmd) == 0
		|| cd_minus_minus(data, cmd) == 0)
		return ;
	update_oldpwd(data->envs);
	update_oldpwd(data->export);
	check_cd_access(cmd->argv[1], cmd->argv[0]);
	chdir(cmd->argv[1]);
	update_pwd(data->envs);
	update_pwd(data->export);
}
