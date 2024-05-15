/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 17:11:20 by lucabohn          #+#    #+#             */
/*   Updated: 2024/05/13 19:06:00 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	token(char *input, t_data *data)
{
	char	token;
	t_args	args;

	args.s = input;
	args.q = NULL;
	args.eq = NULL;
	while (*args.s)
	{
		token = get_token(&args.s, &args.q, &args.eq);
		process_token(token, &args, data);
	}
}

void	process_token(char token, t_args *args, t_data *data)
{
	if (token == '|')
	{
		data->s_n = fill_pipe(data->s_n,
				fill_rightside(&args->s, &args->q, &args->eq, '|'));
		if (!data->s_n)
			return ;
	}
	else if (token == '>' || token == '<' || token == '+')
		data->s_n = fill_redir(&args->s, &args->q, &args->eq, data->s_n);
	else if (token == '-')
		data->s_n = fill_here_doc(&args->s, &args->q, &args->eq, data->s_n);
	else if (token == 'a')
		data->s_n = fill_exe(&args->q, &args->eq, &args->s);
	else if (token == 'o')
		data->s_n = fill_and_or(data->s_n,
				fill_rightside(&args->s, &args->q, &args->eq, 'o'), 5);
	else if (token == '&')
		data->s_n = fill_and_or(data->s_n,
				fill_rightside(&args->s, &args->q, &args->eq, '&'), 4);
	else if (token == '(')
		data->s_n = fill_right_sub(&args->s, &args->q, &args->eq);
}

char	get_token(char **s, char **q, char **eq)
{
	char	*delimiter;
	char	ret;
	int		d_q;
	int		s_q;

	d_q = 0;
	s_q = 0;
	delimiter = "<|>&()";
	ret = 0;
	while (**s == ' ' && *s)
		(*s)++;
	*q = *s;
	get_token_2(s, &ret);
	if (!ret)
		return (0);
	if (ret == 'a')
		process_a(s, delimiter, &d_q, &s_q);
	else if (ret == '<' || ret == '>' || ret == '|'
		|| ret == '(' || ret == ')')
		(*s)++;
	else
		(*s) += 2;
	*eq = *s;
	return (ret);
}

void	get_token_2(char **s, char *ret)
{
	if (**s == '\0')
		return ;
	else if (!ft_strncmp(*s, "(", 1))
		*ret = '(';
	else if (!ft_strncmp(*s, ")", 1))
		*ret = ')';
	else if (!ft_strncmp(*s, "||", 2))
		*ret = 'o';
	else if (!ft_strncmp(*s, "&&", 2))
		*ret = '&';
	else if (!ft_strncmp(*s, "|", 1))
		*ret = '|';
	else if (!ft_strncmp(*s, ">>", 2))
		*ret = '+';
	else if (!ft_strncmp(*s, "<<", 2))
		*ret = '-';
	else if (!ft_strncmp(*s, "<", 1))
		*ret = '<';
	else if (!ft_strncmp(*s, ">", 1))
		*ret = '>';
	else
		*ret = 'a';
}

void	process_a(char **s, char *delimiter, int *d_q, int *s_q)
{
	if (**s == '&')
		(*s)++;
	while (!ft_strchr(delimiter, **s) && **s && **s != ' ')
	{
		double_or_single(d_q, s_q, **s);
		if (*d_q || *s_q)
		{
			while ((*d_q || *s_q) && **s)
			{
				(*s)++;
				double_or_single(d_q, s_q, **s);
			}
			(*s)++;
		}
		else
			(*s)++;
	}
}
