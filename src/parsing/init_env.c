/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:29:58 by ntalmon           #+#    #+#             */
/*   Updated: 2024/05/07 14:23:23 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	del(void *var)
{
	free(var);
}

void	ft_lstdelone_new(t_var **head,
		t_var *node_to_remove, void (*del)(void *))
{
	t_var	*current;

	if (*head == NULL || node_to_remove == NULL)
		return ;
	if (!ft_strcmp((*head)->name, node_to_remove->name))
	{
		current = (*head)->nxt;
		del(node_to_remove->name);
		del(node_to_remove->value);
		free(node_to_remove);
		*head = current;
		return ;
	}
	current = *head;
	while (current != NULL && current->nxt != node_to_remove)
		current = current->nxt;
	if (current != NULL)
	{
		current->nxt = node_to_remove->nxt;
		del(node_to_remove->name);
		del(node_to_remove->value);
		free(node_to_remove);
	}
}

t_var	*ft_lstnew_new(char *name, char *value)
{
	t_var	*new;

	new = ((t_var *)malloc (sizeof(*new)));
	if (!(new))
		return (NULL);
	new->name = name;
	new->value = value;
	new->nxt = NULL;
	return (new);
}

void	ft_lstadd_back_new(t_var **lst, t_var *new)
{
	t_var	*now;

	if (!(*lst))
		*lst = new;
	else
	{
		now = *lst;
		while (now->nxt)
			now = now->nxt;
		now->nxt = new;
	}
}

void	init_env(char **env, t_var **envs, int a)
{
	int		index;
	char	*equal_sign;
	int		name_len;

	index = 0;
	equal_sign = NULL;
	init_env_without(env, envs, a);
	while (env[index] != NULL)
	{
		equal_sign = ft_strchr(env[index], '=');
		if (equal_sign != NULL)
		{
			name_len = ft_len(env[index]) - ft_len(equal_sign);
			ft_lstadd_back_new(envs, ft_lstnew_new(ft_substr(env[index],
						0, name_len), ft_substr(equal_sign,
						1, ft_len(equal_sign - 1))));
		}
		index++;
	}
}
