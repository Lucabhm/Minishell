/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:31:50 by lbohm             #+#    #+#             */
/*   Updated: 2024/05/13 16:05:48 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_dir(char *b, char *m, char *a)
{
	DIR				*dir;
	char			*ret;
	char			*cwd;

	ret = NULL;
	cwd = prompt_cwd();
	dir = opendir(cwd);
	if (dir == NULL)
		error("opendir", 1);
	ret = loop_for_wild(b, m, a, dir);
	if (closedir(dir) == -1)
		error("closedir", 1);
	if (b)
		free(b);
	if (m)
		free(m);
	if (a)
		free(a);
	return (free(cwd), ret);
}

char	*rm_star(char *token)
{
	int		i;
	int		j;
	char	*new;
	int		d_q;
	int		s_q;

	i = 0;
	j = 0;
	d_q = 0;
	s_q = 0;
	new = ft_calloc(ft_len(token) + 1, 1);
	if (!new)
		error(ERROR_1, 1);
	while (token[i])
	{
		double_or_single(&d_q, &s_q, token[i]);
		if (token[i] != '*' || (token[i] == '*' && (d_q == 1 || s_q == 1)))
		{
			new[j] = token[i];
			j++;
		}
		i++;
	}
	return (free(token), new);
}

int	match(char *b, char *m, char *a, struct dirent *i)
{
	if ((!b && !m && !a && i->d_name[0] != '.')
		|| (b && !m && !a && !ft_strncmp(i->d_name, b, ft_len(b)))
		|| (m && !b && !a
			&& ft_strnstr(i->d_name + 1, m, ft_len(i->d_name) - 2))
		|| (a && !m && !b
			&& !ft_strncmp(i->d_name + (ft_len(i->d_name)
					- ft_len(a)), a, ft_len(a)))
		|| (b && a && !m
			&& !ft_strncmp(i->d_name, b, ft_len(b)) && !ft_strncmp(i->d_name
				+ (ft_len(i->d_name) - ft_len(a)), a, ft_len(a)))
		|| (b && m && !a
			&& !ft_strncmp(i->d_name, b, ft_len(b)) && ft_strnstr(i->d_name
				+ ft_len(b), m, ft_len(i->d_name) - ft_len(b)))
		|| (m && a && !b && !ft_strncmp(i->d_name + (ft_len(i->d_name)
					- ft_len(a)), a, ft_len(a))
			&& ft_strnstr(i->d_name, m, ft_len(i->d_name) - ft_len(a)))
		|| (b && m && a && !ft_strncmp(i->d_name, b, ft_len(b))
			&& ft_strnstr(i->d_name + ft_len(b), m, ft_len(i->d_name)
				- ft_len(b)) && !ft_strncmp(i->d_name + (ft_len(i->d_name)
					- ft_len(a)), a, ft_len(a))))
		return (1);
	return (0);
}

char	*loop_for_wild(char *b, char *m, char *a, DIR *dir)
{
	struct dirent	*i;
	char			*ret;

	ret = NULL;
	i = readdir(dir);
	while (i)
	{
		if (match(b, m, a, i))
		{
			ret = free_used_string(ret, "'", 1, 0);
			ret = free_used_string(ret, i->d_name, 1, 0);
			ret = free_used_string(ret, "' ", 1, 0);
		}
		i = readdir(dir);
	}
	return (ret);
}
