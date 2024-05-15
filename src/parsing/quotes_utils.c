/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:36:22 by lbohm             #+#    #+#             */
/*   Updated: 2024/05/13 16:14:08 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*c_env_2(char *ret, char *input, int *start, int end)
{
	char	*tmp;
	char	*tmp2;

	if (ret == NULL)
	{
		tmp = ft_substr(input, 0, *start);
		if (ft_len(input) > (size_t)end)
			ret = free_used_string(tmp, input + end, 1, 0);
		else
			ret = tmp;
		*start -= 1;
	}
	else
	{
		tmp = ft_substr(input, 0, *start);
		ret = check_for_op(ret);
		tmp2 = free_used_string(tmp, ret, 1, 0);
		*start += ft_len(ret) - 1;
		free(ret);
		if (ft_len(input) > (size_t)end)
			ret = free_used_string(tmp2, input + end, 1, 0);
		else
			ret = tmp2;
	}
	return (free(input), ret);
}

char	*get_env(char *value, t_var **env)
{
	t_var	*lst;
	t_var	*first;

	first = *env;
	lst = *env;
	while (lst)
	{
		if (!ft_strcmp(lst->name, value))
			return (lst->value);
		lst = lst->nxt;
	}
	*env = first;
	return (NULL);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (s1)
	{
		if (ft_len(s1) != ft_len(s2))
			return (-1);
		while (s1[i] != '\0')
		{
			if ((unsigned char)s1[i] != (unsigned char)s2[i])
				return ((unsigned char)s1[i] - (unsigned char)s2[i]);
			i++;
		}
		return (0);
	}
	return (-1);
}

char	*check_for_op(char *input)
{
	if (ft_strnstr(input, "&&", ft_len(input)))
		input = check_for_op_2(input, "&&");
	if (ft_strnstr(input, "||", ft_len(input)))
		input = check_for_op_2(input, "||");
	if (ft_strnstr(input, "<<", ft_len(input)))
		input = check_for_op_2(input, "<<");
	if (ft_strnstr(input, ">>", ft_len(input)))
		input = check_for_op_2(input, ">>");
	if (ft_strnstr(input, "<", ft_len(input))
		&& !ft_strnstr(input, "<<", ft_len(input)))
		input = check_for_op_2(input, "<");
	if (ft_strnstr(input, ">", ft_len(input))
		&& !ft_strnstr(input, ">>", ft_len(input)))
		input = check_for_op_2(input, ">");
	if (ft_strnstr(input, "|", ft_len(input))
		&& !ft_strnstr(input, "||", ft_len(input)))
		input = check_for_op_2(input, "|");
	if (ft_strnstr(input, "(", ft_len(input)))
		input = check_for_op_2(input, "(");
	if (ft_strnstr(input, ")", ft_len(input)))
		input = check_for_op_2(input, ")");
	if (ft_strnstr(input, "$", ft_len(input)))
		input = check_for_op_2(input, "$");
	return (input);
}

char	*check_for_op_2(char *input, char *op)
{
	char	*tmp;
	char	*tmp2;
	char	*new;

	tmp = ft_strnstr(input, op, ft_len(input));
	tmp2 = ft_substr(input, 0, ft_len(input) - ft_len(tmp));
	tmp2 = free_used_string(tmp2, "'", 1, 0);
	tmp2 = free_used_string(tmp2, op, 1, 0);
	tmp2 = free_used_string(tmp2, "'", 1, 0);
	if (ft_len(op) > 1)
	{
		new = free_used_string(tmp2,
				ft_substr(tmp, 2, ft_len(tmp) - 2), 1, 1);
	}
	else
	{
		new = free_used_string(tmp2,
				ft_substr(tmp, 1, ft_len(tmp) - 1), 1, 1);
	}
	free(input);
	return (new);
}
