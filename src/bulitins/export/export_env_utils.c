/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_env_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:37:51 by ntalmon           #+#    #+#             */
/*   Updated: 2024/04/05 15:59:42 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

t_var	*search_variable(t_data *data, char *name_to_search)
{
	t_var	*ptr_env;

	ptr_env = data->envs;
	while (ptr_env != NULL)
	{
		if (!(ft_strncmp(ptr_env->name,
					name_to_search, ft_len(name_to_search)))
			&& !(ft_strncmp(ptr_env->name,
					name_to_search, ft_len(ptr_env->name))))
			return (ptr_env);
		ptr_env = ptr_env->nxt;
	}
	return (NULL);
}

void	update_variable(t_var *ptr_env, char *arg, int len_name)
{
	free(ptr_env->value);
	ptr_env->value = ft_substr(arg, len_name + 1,
			ft_len(ft_strchr(arg, '=')));
}

void	add_variable(t_data *data, char *arg, int len_name)
{
	ft_lstadd_back_new(&data->envs,
		ft_lstnew_new(ft_substr(arg, 0, len_name),
			ft_substr(arg, len_name + 1, ft_len(ft_strchr(arg, '=')) + 1)));
}
