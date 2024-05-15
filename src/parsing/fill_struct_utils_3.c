/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct_utils_3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:02:07 by lbohm             #+#    #+#             */
/*   Updated: 2024/05/14 09:44:29 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd	*fill_redir_2(t_fill_right_sub *sub, t_cmd *s_n, t_redir *cmd)
{
	t_here_doc	*doc;

	if (check_next(*sub->s, 'a'))
	{
		get_token(sub->s, sub->q, sub->eq);
		cat_struct(search_next(s_n, EXECVE),
			fill_exe(sub->q, sub->eq, sub->s));
	}
	if (s_n->type == HERE)
	{
		doc = (t_here_doc *)s_n;
		cmd->cmd = doc->cmd;
		doc->cmd = (t_cmd *)cmd;
		return ((t_cmd *)doc);
	}
	else if (s_n->type == REDIR)
		return (fill_redir_at_fornt((t_redir *)s_n, cmd));
	cmd->cmd = s_n;
	return ((t_cmd *)cmd);
}

int	check_next(char *s, char t)
{
	char	*isspace;
	char	*tokens;

	isspace = " \t\n\v\f\r";
	tokens = "<|>&()";
	while (ft_strchr(isspace, *s) && *s)
		s++;
	if (!ft_strncmp(s, "||", 2) && t == 'o')
		return (1);
	else if ((!ft_strncmp(s, "&&", 2) && t == '&')
		|| (!ft_strncmp(s, "(", 1) && t == '('))
		return (1);
	else if ((!ft_strncmp(s, ")", 1) && t == ')')
		|| (!ft_strncmp(s, "|", 1) && t == '|'))
		return (1);
	else if ((!ft_strncmp(s, ">>", 2) && t == '+')
		|| (!ft_strncmp(s, "<<", 2) && t == '-'))
		return (1);
	else if (!ft_strncmp(s, "<", 1) && ft_strncmp(s + 1, "<", 1) && t == '<')
		return (1);
	else if (!ft_strncmp(s, ">", 1) && ft_strncmp(s + 1, ">", 1) && t == '>')
		return (1);
	else if (!ft_strchr(tokens, *s) && t == 'a')
		return (1);
	return (0);
}

t_cmd	*fill_redir_at_fornt(t_redir *s_n, t_redir *cmd)
{
	t_redir	*start;
	int		i;

	i = 0;
	start = s_n;
	while (s_n->cmd->type == REDIR)
	{
		s_n = (t_redir *)s_n->cmd;
		i++;
	}
	cmd->cmd = s_n->cmd;
	if (i > 0)
		s_n->cmd = (t_cmd *)cmd;
	else
		start->cmd = (t_cmd *)cmd;
	return ((t_cmd *)start);
}
