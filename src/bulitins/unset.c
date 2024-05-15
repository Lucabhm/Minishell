/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 12:54:48 by ntalmon           #+#    #+#             */
/*   Updated: 2024/05/14 11:49:05 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_valid_unset(char *str)
{
	while (*str)
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		str++;
	}
	return (1);
}

void	exe_unset(t_data *data, t_exe *cmd)
{
	if (cmd->argv[1] == NULL)
		return ;
	if (cmd->argv[1][0] == '-')
	{
		error_msg_without_e(cmd->argv[0], cmd->argv[1],
			"invalid option", 2);
		return ;
	}
	else if (!is_valid_unset(cmd->argv[1]) || !ft_strcmp(cmd->argv[1], ""))
	{
		error_msg_without_e(cmd->argv[0], cmd->argv[1],
			"not a valid identifier", 1);
		return ;
	}
	unset_var(&data->envs, cmd);
	unset_var(&data->export, cmd);
	g_signal = 0;
}

void	unset_var(t_var **list, t_exe *cmd)
{
	int		i;
	t_var	*ptr;

	i = 1;
	while (cmd->argv[i])
	{
		ptr = *list;
		if (!cmd->argv[i])
			return ;
		while (ptr != NULL)
		{
			if (!ft_strcmp(ptr->name, cmd->argv[i]))
			{
				ft_lstdelone_new(list, ptr, del);
				break ;
			}
			ptr = ptr->nxt;
		}
		i++;
	}
}
