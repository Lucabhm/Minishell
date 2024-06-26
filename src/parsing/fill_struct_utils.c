/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 09:31:00 by lbohm             #+#    #+#             */
/*   Updated: 2024/05/13 17:51:54 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**alloc_argv(char *s)
{
	int		i;
	char	**argv;
	t_args	vars;
	int		len;

	vars.q = NULL;
	vars.eq = NULL;
	vars.s = ft_strdup(s);
	len = ft_len(vars.s);
	i = 1;
	while (check_next(vars.s, 'a'))
	{
		get_token(&vars.s, &vars.q, &vars.eq);
		i++;
	}
	free(vars.s - (len - ft_len(vars.s)));
	argv = (char **)malloc ((i + 1) * sizeof(char *));
	if (!argv)
		error(ERROR_1, 1);
	argv[i] = NULL;
	return (argv);
}

void	check_for_mode(t_redir **cmd, char **q)
{
	if (**q == '>')
	{
		(*q)++;
		if (**q == '>')
			(*cmd)->mode = O_WRONLY | O_CREAT | O_APPEND;
		else
		{
			(*cmd)->mode = O_WRONLY | O_CREAT | O_TRUNC;
			(*q)--;
		}
		(*cmd)->fd = 1;
	}
	else
	{
		(*cmd)->mode = O_RDONLY;
		(*cmd)->fd = 0;
	}
}

void	cat_struct(t_cmd *new, t_cmd *cmd)
{
	t_exe	*first;
	t_exe	*second;
	int		pos;
	char	**argvs;

	first = (t_exe *)new;
	second = (t_exe *)cmd;
	pos = count_argvs(first->argv) + count_argvs(second->argv);
	argvs = (char **)malloc ((pos + 1) * sizeof(char *));
	if (!argvs)
		error(ERROR_1, 1);
	argvs[pos] = NULL;
	argvs = cat_struct_2(first->argv, second->argv, argvs);
	freeupm(first->argv);
	first->argv = argvs;
	freeupm(second->argv);
	free(second);
}

char	**cat_struct_2(char **first, char **second, char **new)
{
	int	i;
	int	pos;

	i = 0;
	pos = 0;
	while (first[i])
	{
		new[pos] = ft_strdup(first[i]);
		i++;
		pos++;
	}
	i = 0;
	while (second[i])
	{
		new[pos] = ft_strdup(second[i]);
		i++;
		pos++;
	}
	return (new);
}

int	count_argvs(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}
