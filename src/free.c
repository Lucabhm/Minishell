/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:13:52 by lbohm             #+#    #+#             */
/*   Updated: 2024/05/14 09:38:46 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**freeupm(char	**arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

void	free_ast_helper(t_cmd *cmd)
{
	if (cmd->type == PIPE)
	{
		free_ast(((t_pipe *)cmd)->left);
		free_ast(((t_pipe *)cmd)->right);
		free(cmd);
	}
	else if (cmd->type == REDIR)
	{
		if (((t_redir *)cmd)->cmd)
			free_ast(((t_redir *)cmd)->cmd);
		free_redir((t_redir *)cmd);
	}
	else if (cmd->type == HERE)
	{
		if (((t_here_doc *)cmd)->cmd)
			free_ast(((t_here_doc *)cmd)->cmd);
		free_here((t_here_doc *)cmd);
	}
}

void	free_ast(t_cmd *cmd)
{
	if (cmd->type == EXECVE)
	{
		free_exe((t_exe *)cmd);
		return ;
	}
	else if (cmd->type == OR || cmd->type == AND)
	{
		free_ast(((t_and_or *)cmd)->left);
		free_ast(((t_and_or *)cmd)->right);
		free(cmd);
		return ;
	}
	else
	{
		free_ast_helper(cmd);
		return ;
	}
}
