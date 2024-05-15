/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:02:58 by ntalmon           #+#    #+#             */
/*   Updated: 2024/05/14 12:41:34 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	add_oldpwd(t_var **export)
{
	t_var	*ptr;

	if (*export)
	{
		ptr = *export;
		if (export == NULL)
			return ;
		while (ptr->nxt)
		{
			if (!(ft_strncmp(ptr->name, "OLDPWD", 6)))
				return ;
			ptr = ptr->nxt;
		}
		ft_lstadd_back_new(export, ft_lstnew_new(ft_strdup("OLDPWD"), NULL));
	}
}

void	init_env_without(char **env, t_var **envs, int a)
{
	char	*cwd;

	cwd = prompt_cwd();
	if (env[0] == NULL)
	{
		ft_lstadd_back_new(envs, ft_lstnew_new(ft_strdup("OLDPWD"), NULL));
		ft_lstadd_back_new(envs, ft_lstnew_new(ft_strdup("PWD"), prompt_cwd()));
		ft_lstadd_back_new(envs, ft_lstnew_new(
				ft_strdup("SHLVL"), ft_strdup("1")));
	}
	if (env[0] == NULL && a == 1)
	{
		ft_lstadd_back_new(envs, ft_lstnew_new(ft_strdup("_"),
				ft_strjoin(ft_strdup("./"),
					ft_substr(cwd, find_s(cwd), ft_len(cwd) - find_s(cwd)))));
	}
	free(cwd);
}
