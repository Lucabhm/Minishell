/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct_utils_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:52:06 by lbohm             #+#    #+#             */
/*   Updated: 2024/05/13 19:03:00 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd	*dup_struct(t_exe	*cmd)
{
	t_exe	*new;
	char	**newargv;
	int		i;

	i = 0;
	new = (t_exe *)malloc (sizeof(t_exe));
	if (!new)
		error(ERROR_1, 1);
	new->type = cmd->type;
	newargv = (char **)malloc((count_argvs(cmd->argv) + 1) * sizeof(char *));
	if (!newargv)
		error(ERROR_1, 1);
	while (cmd->argv[i])
	{
		newargv[i] = ft_strdup(cmd->argv[i]);
		i++;
	}
	newargv[i] = NULL;
	new->argv = newargv;
	free_exe(cmd);
	return ((t_cmd *)new);
}

t_cmd	*search_next(t_cmd *cmd, int type)
{
	while (cmd->type != type)
	{
		if (cmd->type == PIPE)
			cmd = ((t_pipe *)cmd)->right;
		else if (cmd->type == REDIR)
			cmd = ((t_redir *)cmd)->cmd;
		else if (cmd->type == HERE)
			cmd = ((t_here_doc *)cmd)->cmd;
		else if (cmd->type == AND)
			cmd = ((t_and_or *)cmd)->right;
		else if (cmd->type == OR)
			cmd = ((t_and_or *)cmd)->right;
	}
	return (cmd);
}

t_cmd	*fill_rightside(char **s, char **q, char **eq, char limit)
{
	char	token;
	t_cmd	*cmd;

	cmd = NULL;
	while (**s && !check_next(*s, limit) && !check_next(*s, 'o')
		&& !check_next(*s, '&') && !check_next(*s, ')'))
	{
		token = get_token(s, q, eq);
		if (token == 'a')
			cmd = fill_exe(q, eq, s);
		else if (token == '<' || token == '>' || token == '+')
			cmd = fill_redir(s, q, eq, cmd);
		else if (token == '-')
			cmd = fill_here_doc(s, q, eq, cmd);
		else if (token == '(')
			cmd = fill_right_sub(s, q, eq);
		else if (token == '|')
			cmd = fill_pipe(cmd, fill_rightside(s, q, eq, '|'));
	}
	if (!cmd)
		error_msg_without_e(NULL, "parse error near token", NULL, 2);
	return (cmd);
}

t_cmd	*process_token2(t_fill_right_sub *vars, char token)
{
	if (token == 'a')
		vars->cmd = fill_exe(vars->q, vars->eq, vars->s);
	else if (token == 'o')
		vars->cmd = fill_and_or(vars->cmd,
				fill_rightside(vars->s, vars->q, vars->eq, 'o'), 5);
	else if (token == '&')
		vars->cmd = fill_and_or(vars->cmd,
				fill_rightside(vars->s, vars->q, vars->eq, '&'), 4);
	else if (token == '|')
		vars->cmd = fill_pipe(vars->cmd,
				fill_rightside(vars->s, vars->q, vars->eq, '|'));
	else if (token == '<' || token == '>' || token == '+')
		vars->cmd = fill_redir(vars->s, vars->q, vars->eq, vars->cmd);
	else if (token == '-')
		vars->cmd = fill_here_doc(vars->s, vars->q, vars->eq, vars->cmd);
	else if (token == '(')
		vars->cmd = fill_right_sub(vars->s, vars->q, vars->eq);
	return (vars->cmd);
}

t_cmd	*fill_right_sub(char **s, char **q, char **eq)
{
	char				token;
	t_fill_right_sub	vars;
	int					count;

	vars.cmd = NULL;
	count = 1;
	vars.s = s;
	vars.q = q;
	vars.eq = eq;
	while (**vars.s && !check_next(*vars.s, ')') && count > 0)
	{
		token = get_token(vars.s, vars.q, vars.eq);
		vars.cmd = process_token2(&vars, token);
		if (check_next(*vars.s, ')'))
		{
			count--;
			get_token(vars.s, vars.q, vars.eq);
		}
	}
	if (!vars.cmd)
		error_msg_without_e(NULL, "parse error near token", NULL, 2);
	return (vars.cmd);
}
