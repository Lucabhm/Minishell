/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 12:25:32 by lbohm             #+#    #+#             */
/*   Updated: 2024/05/13 15:06:42 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*check_dir(char *token, int *i)
{
	t_wild	w;
	char	*ret;

	w.befor = NULL;
	w.middle = NULL;
	w.after = NULL;
	if (ft_strcmp(token, "*"))
	{
		if (token[*i + 1] == '\0')
			w.befor = ft_substr(token, 0, ft_len(token) - ft_len(token + *i));
		else if (*i == 0)
			star_at_front(&w, token, i);
		else
			star_in_middle(&w, token, i);
	}
	if (w.befor)
		w.befor = rm_star_and_quotes(w.befor);
	if (w.middle)
		w.middle = rm_star_and_quotes(w.middle);
	if (w.after)
		w.after = rm_star_and_quotes(w.after);
	ret = get_dir(w.befor, w.middle, w.after);
	if (!ret)
		return (token);
	return (free(token), *i = -1, ret);
}

void	star_at_front(t_wild *w, char *tmp, int *i)
{
	w->j = 0;
	w->d_q = 0;
	w->s_q = 0;
	w->after = ft_substr(tmp, *i + 1, ft_len(tmp + *i + 1));
	while (w->after && w->after[w->j])
	{
		double_or_single(&w->d_q, &w->s_q, w->after[w->j]);
		if (w->after[w->j] == '*' && w->d_q == 0 && w->s_q == 0)
		{
			w->middle = ft_substr(w->after, 0, w->j);
			check_empty_str(&w->middle);
			w->tmp2 = ft_strdup(w->after);
			free(w->after);
			w->after = ft_substr(w->tmp2, w->j + 1, ft_len(w->tmp2 + w->j + 1));
			check_empty_str(&w->after);
			free(w->tmp2);
			break ;
		}
		else
			w->j++;
	}
}

void	star_in_middle(t_wild *w, char *tmp, int *i)
{
	w->j = 0;
	w->d_q = 0;
	w->s_q = 0;
	w->befor = ft_substr(tmp, 0, ft_len(tmp) - ft_len(tmp + *i));
	check_empty_str(&w->befor);
	w->after = ft_substr(tmp, *i + 1, ft_len(tmp + *i + 1));
	check_empty_str(&w->after);
	while (w->after && w->after[w->j])
	{
		double_or_single(&w->d_q, &w->s_q, w->after[w->j]);
		if (w->after[w->j] == '*' && w->d_q == 0 && w->s_q == 0)
		{
			w->middle = ft_substr(w->after, 0, w->j);
			check_empty_str(&w->middle);
			w->tmp2 = ft_strdup(w->after);
			free(w->after);
			w->after = ft_substr(w->tmp2, w->j + 1, ft_len(w->tmp2 + w->j + 1));
			check_empty_str(&w->after);
			free(w->tmp2);
			break ;
		}
		else
			w->j++;
	}
}

char	*rm_star_and_quotes(char *str)
{
	char	*tmp;

	str = rm_star(str);
	if (ft_strcmp(str, ""))
	{
		tmp = ft_strdup(str);
		free(str);
		str = rm_quotes(tmp, tmp + ft_len(tmp));
		free(tmp);
	}
	else
	{
		free(str);
		str = NULL;
	}
	return (str);
}

void	check_empty_str(char **str)
{
	if (!ft_strcmp(*str, ""))
	{
		free(*str);
		*str = NULL;
	}
}
