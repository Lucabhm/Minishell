/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 12:35:09 by ntalmon           #+#    #+#             */
/*   Updated: 2024/05/14 09:20:01 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*check_for_access(t_data data, char **cmd)
{
	char	*newpath;
	char	**paths;

	paths = ft_split(get_env("PATH", &data.envs), ':');
	if (ft_strchr(cmd[0], '/') || !paths)
	{
		if (access(cmd[0], F_OK) != -1)
		{
			newpath = ft_strdup(cmd[0]);
			if (paths)
				freeupm(paths);
			return (newpath);
		}
		else if (!paths)
			return (handle_nonexistent_path(cmd));
		else
			return (handle_no_executable_in_path(paths, cmd));
	}
	return (search_executable_in_paths(paths, cmd));
}

char	*handle_nonexistent_path(char **cmd)
{
	char	*cwd;

	cwd = free_used_string(prompt_cwd(), "/", 1, 0);
	cwd = free_used_string(cwd, cmd[0], 1, 0);
	if (access(cmd[0], F_OK) != -1)
		return (cwd);
	else
		return (free(cwd), NULL);
}

char	*handle_no_executable_in_path(char **paths, char **cmd)
{
	char	*cwd;

	cwd = free_used_string(prompt_cwd(), "/", 1, 0);
	cwd = free_used_string(cwd, cmd[0], 1, 0);
	if (access(cmd[0], F_OK) != -1)
		return (cwd);
	else
		return (free(cwd), freeupm(paths), NULL);
}

char	*search_executable_in_paths(char **paths, char **cmd)
{
	int		i;
	char	*newpath;
	char	*tmp;

	i = 0;
	while (paths && paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		newpath = ft_strjoin(tmp, cmd[0]);
		free(tmp);
		if (access(newpath, X_OK) == -1)
		{
			i++;
			free(newpath);
		}
		else
			return (freeupm(paths), newpath);
	}
	return (freeupm(paths), NULL);
}
