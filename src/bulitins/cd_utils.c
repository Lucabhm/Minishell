/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 21:55:46 by ntalmon           #+#    #+#             */
/*   Updated: 2024/04/26 21:58:08 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	cd_only(t_data *data, t_exe *cmd)
{
	if (cmd->argv[1] == NULL)
	{
		if (get_env("HOME", &data->envs) == NULL)
		{
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
			g_signal = 1;
			return (0);
		}
		update_oldpwd(data->envs);
		update_oldpwd(data->export);
		chdir(get_env("HOME", &data->envs));
		update_pwd(data->envs);
		update_pwd(data->export);
		return (0);
	}
	return (1);
}

int	cd_minus(t_data *data, t_exe *cmd)
{
	if (cmd->argv[1][0] == '-' && cmd->argv[1][1] != '-')
	{
		if (get_env("OLDPWD", &data->envs) == NULL)
		{
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
			g_signal = 1;
			return (0);
		}
		if (cmd->argv[1][1] != '\0')
		{
			error_msg_without_e(cmd->argv[0],
				ft_substr(cmd->argv[1], 0, 2), "invalid option", 1);
			return (0);
		}
		printf("%s\n", get_env("OLDPWD", &data->envs));
		free(cmd->argv[1]);
		cmd->argv[1] = ft_strdup(get_env("OLDPWD", &data->envs));
	}
	return (1);
}

int	cd_minus_minus(t_data *data, t_exe *cmd)
{
	if (cmd->argv[1][0] == '-' && cmd->argv[1][1] == '-')
	{
		if (cmd->argv[1][2] != '\0')
		{
			error_msg_without_e(cmd->argv[0],
				ft_substr(cmd->argv[1], 0, 2), "invalid option", 1);
			return (0);
		}
		free(cmd->argv[1]);
		cmd->argv[1] = ft_strdup(get_env("HOME", &data->envs));
		if (cmd->argv[2] != NULL)
		{
			free(cmd->argv[1]);
			cmd->argv[1] = ft_strdup(cmd->argv[2]);
		}
	}
	return (1);
}
