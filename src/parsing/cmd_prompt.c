/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 11:16:37 by lbohm             #+#    #+#             */
/*   Updated: 2024/05/14 12:40:04 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*print_prompt(void)
{
	char	*input;
	char	*tmp;

	input = NULL;
	if (isatty(fileno(stdin)))
		input = readline("\001\e[1;32m\002minishell\001\e[0m\002$ ");
	if (input)
	{
		tmp = ft_strtrim(input, " \t\n\v\f\r");
		free(input);
		input = tmp;
		if (ft_strcmp(input, ""))
			add_history(input);
	}
	return (input);
}

char	*free_used_string(char *f, char *s, int ff, int sf)
{
	char	*tmp;

	tmp = ft_strjoin(f, s);
	if (ff == 1 && f)
		free(f);
	if (sf == 1 && s)
		free(s);
	return (tmp);
}

char	*prompt_cwd(void)
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
	return (cwd);
}

int	find_s(char *pwd)
{
	int	len;

	len = ft_len(pwd);
	while (pwd[len - 1] != '/' && len > 0)
		len--;
	return (len);
}

char	*get_username(char *cwd, t_data data)
{
	char	*tmp;
	char	*user;

	user = ft_strdup(get_env("USER", &data.envs));
	if (!ft_strcmp(user, ""))
	{
		tmp = ft_strtrim(cwd, "/Users/");
		user = ft_substr(tmp, 0, ft_len(tmp) - ft_len(ft_strchr(tmp, '/')));
		free(tmp);
	}
	return (user);
}
