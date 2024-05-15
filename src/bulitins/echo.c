/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 12:48:53 by ntalmon           #+#    #+#             */
/*   Updated: 2024/05/14 12:23:48 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_echo(int i, int nline, t_exe *cmd)
{
	while (cmd->argv[i] != NULL)
	{
		printf("%s", cmd->argv[i]);
		if (cmd->argv[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (nline == 0)
		printf("\n");
	g_signal = 0;
}

void	exe_echo(t_exe *cmd)
{
	int	nline;
	int	i;
	int	j;

	nline = 0;
	i = 1;
	while (cmd->argv[i] != NULL && ft_strncmp(cmd->argv[i], "-n", 2) == 0)
	{
		j = 2;
		while (cmd->argv[i][j] == 'n')
			j++;
		if (cmd->argv[i][j] == '\0')
		{
			nline = 1;
			i++;
		}
		else
			break ;
	}
	print_echo(i, nline, cmd);
}
