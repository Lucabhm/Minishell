/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:21:51 by lbohm             #+#    #+#             */
/*   Updated: 2024/05/13 17:59:22 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	onlyop(char *in)
{
	char	tok;
	char	*q;
	char	*eq;
	int		i;

	i = 0;
	while (*in)
	{
		tok = get_token(&in, &q, &eq);
		if (check_next(in, tok) && tok != 'a' && tok != '(' && tok != ')')
			return (0);
		if ((tok == '(' && check_next(in, ')')) || (tok == ')'
				&& check_next(in, '(')) || (tok == ')' && check_next(in, 'a'))
			|| ((tok == '|' || tok == 'o' || tok == '&') && i == 0)
			|| (tok != 'a' && tok != '(' && tok != ')'
				&& check_next(in, '|')))
			return (0);
		i++;
		if (tok != 'a' && tok != '(' && tok != ')')
			i--;
	}
	if ((tok != 'a' && tok != '(' && tok != ')' && tok)
		|| (i == 0 && ft_strcmp(in, "")))
		return (0);
	return (1);
}

char	*get_home(t_data data)
{
	char	*pwd;
	char	*home;
	char	*users_pos;
	char	*next_slash_pos;

	home = ft_strdup(get_env("HOME", &data.envs));
	if (!ft_strcmp(home, ""))
	{
		pwd = prompt_cwd();
		free(home);
		home = NULL;
		if (pwd)
		{
			users_pos = ft_strnstr(pwd, "/Users/", ft_len(pwd));
			if (users_pos)
			{
				next_slash_pos = ft_strchr(users_pos + ft_len("/Users/"), '/');
				if (next_slash_pos != NULL)
					home = ft_substr(users_pos, 0,
							ft_len(users_pos) - ft_len(next_slash_pos));
			}
		}
	}
	return (home);
}

void	count_pipe(char *input, t_data *data)
{
	int	i;
	int	count;
	int	d_q;
	int	s_q;

	i = 0;
	count = 0;
	d_q = 0;
	s_q = 0;
	while (input[i])
	{
		double_or_single(&d_q, &s_q, input[i]);
		if (input[i] == '|' && d_q == 0 && s_q == 0)
			count++;
		i++;
	}
	if (count > 0)
	{
		data->child = (pid_t *)malloc ((count + 1) * sizeof(pid_t));
		if (!data->child)
			error(ERROR_1, 1);
	}
}
