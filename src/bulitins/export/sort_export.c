/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:53:50 by lbohm             #+#    #+#             */
/*   Updated: 2024/04/26 21:28:04 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	swap_a(t_var **a)
{
	t_var	*first;
	t_var	*second;

	if (*a)
	{
		first = *a;
		if (first->nxt)
		{
			second = first->nxt;
			first->nxt = second->nxt;
			second->nxt = first;
			*a = second;
		}
	}
}

void	rotate_a(t_var **a)
{
	t_var	*first;
	t_var	*second;
	t_var	*last;

	if (*a)
	{
		first = *a;
		if (first->nxt)
		{
			second = first->nxt;
			last = ft_lstlast_test(first);
			last->nxt = first;
			first->nxt = NULL;
			*a = second;
		}
	}
}

int	check_sort(t_var **export)
{
	t_var	*node;

	node = *export;
	while (node->nxt)
	{
		if (ft_strncmp(node->name, node->nxt->name, ft_len(node->name)) > 0)
			return (1);
		node = node->nxt;
	}
	return (0);
}

void	sort_export(t_var **exp)
{
	char	*big;

	if (*exp)
	{
		big = biggest(exp);
		while (check_sort(exp))
		{
			if (ft_strcmp((*exp)->name, big) == 0)
				rotate_a(exp);
			else if (ft_strncmp((*exp)->name,
					(*exp)->nxt->name, ft_len((*exp)->name)) > 0)
			{
				swap_a(exp);
				rotate_a(exp);
			}
			else
				rotate_a(exp);
		}
	}
}

char	*biggest(t_var **export)
{
	t_var	*node;
	t_var	*node2;
	char	*ret;

	node = *export;
	ret = node->name;
	while (node)
	{
		node2 = *export;
		while (node2)
		{
			if (ft_strncmp(node->name, node2->name, ft_len(node->name)) > 0
				&& ft_strncmp(node->name, ret, ft_len(ret)) >= 0)
				ret = node->name;
			node2 = node2->nxt;
		}
		node = node->nxt;
	}
	return (ret);
}
