/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:00:20 by ntalmon           #+#    #+#             */
/*   Updated: 2024/05/14 12:41:43 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	exe_export_export(t_data *data, t_exe *cmd)
{
	int	i;

	i = 1;
	if (cmd->argv[1] == NULL)
		return ;
	while (cmd->argv[i])
	{
		if (cmd->argv[i][0] == '-')
		{
			error_msg_without_e(cmd->argv[0], cmd->argv[i],
				"invalid option", 2);
			return ;
		}
		else if (ft_isdigit(cmd->argv[i][0])
					|| (cmd->argv[i][0] == '=' || !is_valid(cmd->argv[i])))
		{
			error_msg_without_e(cmd->argv[0], cmd->argv[i],
				"not a valid identifier", 1);
			return ;
		}
		process_export_argument(data, cmd->argv[i]);
		i++;
	}
	g_signal = 0;
}
