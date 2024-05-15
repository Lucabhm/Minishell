/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:00:16 by lbohm             #+#    #+#             */
/*   Updated: 2024/05/13 17:23:18 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*check_input(char *input, t_data *data)
{
	if (!ft_strcmp(input, ""))
		return (free(input), NULL);
	input = check_for_quotes(input);
	input = check_for_schar(input, *data);
	if (!input)
		return (NULL);
	if (!ft_strcmp(input, "||") || !ft_strcmp(input, "&&")
		|| !ft_strcmp(input, "|") || !ft_strcmp(input, "<")
		|| !ft_strcmp(input, "<<") || !ft_strcmp(input, ">>")
		|| !ft_strcmp(input, ">") || !onlyop(input))
		return (free(input),
			error_msg_without_e(NULL, "parse error near token", NULL, 2), NULL);
	count_pipe(input, data);
	return (input);
}

char	*check_for_schar(char *input, t_data data)
{
	char	*token;
	char	*q;
	char	*eq;
	char	*new;
	int		len;

	len = ft_len(input);
	new = NULL;
	while (input && *input)
	{
		get_token(&input, &q, &eq);
		token = ft_substr(q, 0, ft_len(q) - ft_len(eq));
		token = check_for_schar_2(token, data);
		if (token && !new)
		{
			new = ft_strdup(token);
			free(token);
		}
		else if (token)
		{
			new = free_used_string(new, " ", 1, 0);
			new = free_used_string(new, token, 1, 1);
		}
	}
	return (free(input - len), new);
}

char	*check_for_schar_2(char *token, t_data data)
{
	int			i;
	int			d_q;
	int			s_q;

	i = 0;
	d_q = 0;
	s_q = 0;
	while (token && token[i])
	{
		double_or_single(&d_q, &s_q, token[i]);
		if (i >= 0 && token && token[i] == '$' && s_q == 0)
			token = check_env(token, &i, data, d_q);
		if (i >= 0 && token && token[i] == '*' && s_q == 0 && d_q == 0)
			token = check_dir(token, &i);
		if (i >= 0 && token && token[i] == '~' && s_q == 0 && d_q == 0)
			token = check_tilde(token, data);
		i++;
	}
	return (token);
}

char	*check_env(char *token, int *i, t_data data, int d_q)
{
	char	*value;
	int		j;
	char	*ret;
	int		len;

	j = 1;
	len = 0;
	ret = NULL;
	value = ft_substr(token, *i, ft_len(token + *i));
	if ((value[j] == '\"' && d_q == 1) || value[j] == '/' || value[j] == '.'
		|| value[j] == '$' || value[j] == '\0' || value[j] == ' ')
		return (free(value), token);
	if (value[j] == '?')
		return (free(value), c_env_2(ft_itoa(g_signal), token, i, *i + 2));
	while (value[j] && !ft_strchr(" \"\'/.$?", value[j]))
		j++;
	if (j > 1)
		ret = ft_substr(value, 1, j - 1);
	free(value);
	value = ft_strdup(get_env(ret, &data.envs));
	len = ft_len(ret);
	if (!ft_strcmp(value, ""))
		return (free(ret), free(value), c_env_2(NULL, token, i, *i + len + 1));
	return (free(ret), c_env_2(value, token, i, *i + len + 1));
}

char	*check_tilde(char *token, t_data data)
{
	char	*tilde;
	char	*new;

	tilde = get_home(data);
	if (!ft_strcmp(token, "~"))
	{
		free(token);
		return (tilde);
	}
	else if (token[1] == '/')
	{
		tilde = free_used_string(tilde, "/", 1, 0);
		new = free_used_string(tilde, token + 2, 1, 0);
		return (free(token), new);
	}
	else
		free(tilde);
	return (token);
}
