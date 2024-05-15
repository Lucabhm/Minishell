/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 12:52:04 by ntalmon           #+#    #+#             */
/*   Updated: 2024/05/14 12:25:08 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exe_pwd(void)
{
	char	*cwd;
	int		size;

	size = 1;
	cwd = malloc(size * sizeof(char));
	if (!cwd)
		error(ERROR_1, 1);
	while (getcwd(cwd, size) == NULL)
	{
		if (errno == ERANGE)
		{
			size++;
			free(cwd);
			cwd = malloc(size * sizeof(char));
			if (!cwd)
				error(ERROR_1, 1);
		}
		else
			error(ERROR_11, 1);
	}
	printf("%s\n", cwd);
	free(cwd);
	g_signal = 0;
}
