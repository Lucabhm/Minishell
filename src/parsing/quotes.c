/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:28:27 by lbohm             #+#    #+#             */
/*   Updated: 2024/05/13 17:26:39 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*check_for_quotes(char *input)
{
	int		i;
	int		double_q;
	int		single_q;
	int		par;

	i = 0;
	par = 0;
	double_q = 0;
	single_q = 0;
	while (input[i])
	{
		double_or_single(&double_q, &single_q, input[i]);
		if (input[i] == '\t')
			input[i] = ' ';
		else if (input[i] == '(' && !double_q && !single_q)
			par++;
		else if (input[i] == ')' && !double_q && !single_q)
			par--;
		i++;
	}
	if (!error_quotes(par, double_q, single_q, input))
		return (NULL);
	return (input);
}

void	double_or_single(int *d, int *s, char quote)
{
	if (quote == '"')
	{
		if (*d == 1)
			*d = 0;
		else
		{
			if (*s == 0)
				*d = 1;
		}
	}
	else if (quote == '\'')
	{
		if (*s == 1)
			*s = 0;
		else
		{
			if (*d == 0)
				*s = 1;
		}
	}
}

char	*rm_quotes(char *q, char *eq)
{
	int		i;
	int		pos;
	int		len;
	char	*new;

	i = 0;
	pos = 0;
	len = ft_len(q) - ft_len(eq);
	new = ft_calloc(len + 1, 1);
	while (i < len)
	{
		if (q[i] == '"' && ft_strchr(q + (i + 1), '"'))
			rm_quotes_2(q, &new, &i, &pos);
		else if (q[i] == '\'' && ft_strchr(q + (i + 1), '\''))
			rm_quotes_2(q, &new, &i, &pos);
		else
		{
			new[pos] = q[i];
			i++;
			pos++;
		}
	}
	return (new);
}

void	rm_quotes_2(char *q, char **new, int *i, int *pos)
{
	char	*tmp;
	int		wordlen;

	tmp = ft_substr(q, *i + 1,
			ft_len(q + *i) - ft_len(ft_strchr(q + (*i + 1), q[*i])) - 1);
	if (ft_strcmp(tmp, ""))
	{
		wordlen = ft_len(tmp) + 1;
		ft_strlcat(*new, tmp, ft_len(*new) + wordlen);
		*i += wordlen + 1;
		*pos += wordlen - 1;
	}
	else
		*i += 2;
	free(tmp);
}
