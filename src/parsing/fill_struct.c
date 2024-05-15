/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 22:20:47 by lucabohn          #+#    #+#             */
/*   Updated: 2024/05/13 19:03:49 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd	*fill_exe(char **q, char **eq, char **s)
{
	t_exe	*cmd;
	int		i;

	i = 0;
	cmd = (t_exe *)malloc (sizeof(t_exe));
	if (!cmd)
		error(ERROR_1, 1);
	if (q)
	{
		cmd->type = EXECVE;
		cmd->argv = alloc_argv(*s);
		cmd->argv[i] = rm_quotes(*q, *eq);
		while (check_next(*s, 'a'))
		{
			i++;
			get_token(s, q, eq);
			cmd->argv[i] = rm_quotes(*q, *eq);
		}
	}
	else
		cmd->type = REDIR;
	return ((t_cmd *)cmd);
}

t_cmd	*fill_pipe(t_cmd *l, t_cmd *r)
{
	t_pipe	*cmd;

	if (!l || !r)
		return (NULL);
	cmd = (t_pipe *)malloc (sizeof(t_pipe));
	if (!cmd)
		error(ERROR_1, 1);
	cmd->type = PIPE;
	cmd->left = l;
	cmd->right = r;
	return ((t_cmd *)cmd);
}

t_cmd	*fill_redir(char **s, char **q, char **eq, t_cmd *s_n)
{
	t_redir				*cmd;
	t_fill_right_sub	sub;

	sub.s = s;
	sub.q = q;
	sub.eq = eq;
	cmd = (t_redir *)malloc (sizeof(t_redir));
	if (!cmd)
		error(ERROR_1, 1);
	cmd->type = REDIR;
	check_for_mode(&cmd, q);
	get_token(s, q, eq);
	cmd->f = rm_quotes(*q, *eq);
	if (s_n && s_n->type != PIPE)
		return (fill_redir_2(&sub, s_n, cmd));
	else if (check_next(*s, 'a'))
	{
		get_token(s, q, eq);
		cmd->cmd = fill_exe(q, eq, s);
	}
	else
		cmd->cmd = NULL;
	return ((t_cmd *)cmd);
}

t_cmd	*fill_here_doc(char **s, char **q, char **eq, t_cmd *s_n)
{
	t_here_doc	*cmd;

	cmd = (t_here_doc *)malloc (sizeof(t_here_doc));
	if (!cmd)
		error(ERROR_1, 1);
	cmd->type = HERE;
	get_token(s, q, eq);
	cmd->l = rm_quotes(*q, *eq);
	if (s_n && check_next(*s, 'a'))
	{
		get_token(s, q, eq);
		cat_struct(search_next(s_n, EXECVE), fill_exe(q, eq, s));
		cmd->cmd = s_n;
	}
	else if (s_n)
		cmd->cmd = s_n;
	else if (check_next(*s, 'a'))
	{
		get_token(s, q, eq);
		cmd->cmd = fill_exe(q, eq, s);
	}
	else
		cmd->cmd = NULL;
	return ((t_cmd *)cmd);
}

t_cmd	*fill_and_or(t_cmd *l, t_cmd *r, int andor)
{
	t_and_or	*cmd;

	cmd = (t_and_or *)malloc (sizeof(t_and_or));
	if (!cmd)
		error(ERROR_1, 1);
	cmd->type = andor;
	cmd->left = l;
	cmd->right = r;
	return ((t_cmd *)cmd);
}
