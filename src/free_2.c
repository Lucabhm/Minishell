/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:35:40 by ntalmon           #+#    #+#             */
/*   Updated: 2024/05/14 09:46:05 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_exe(t_exe	*node)
{
	if (node->argv)
		freeupm(node->argv);
	free(node);
}

void	free_redir(t_redir *node)
{
	free(node->f);
	free(node);
}

void	free_here(t_here_doc *node)
{
	free(node->l);
	free(node);
}

void	free_lst(t_var	**lst)
{
	t_var	*node;
	t_var	*tmp;

	if (lst)
	{
		node = *lst;
		while (node)
		{
			tmp = node->nxt;
			if (node->name)
				free(node->name);
			if (node->value)
				free(node->value);
			free(node);
			node = tmp;
		}
	}
}

void	free_for_new_cmd(t_data *data)
{
	if (data->in)
		free(data->in);
	data->in = NULL;
	if (data->s_n)
		free_ast(data->s_n);
	data->s_n = NULL;
	if (data->path_exe)
		free(data->path_exe);
	data->path_exe = NULL;
	if (data->child)
		free(data->child);
	data->child = NULL;
}
