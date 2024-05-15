/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_export_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbohm <lbohm@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 18:15:10 by ntalmon           #+#    #+#             */
/*   Updated: 2024/05/07 17:38:30 by lbohm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	process_export_argument(t_data *data, char *argument)
{
	if (ft_strchr(argument, '='))
		process_export_with_equal(data, argument);
	else
		process_export_without_equal(data, argument);
}

void	process_export_with_equal(t_data *data, char *argument)
{
	t_var	*ptr_export;
	char	*name_to_search;
	int		len_name;

	ptr_export = data->export;
	len_name = (ft_len(argument) - ft_len(ft_strchr(argument, '=')));
	name_to_search = ft_substr(argument, 0, len_name);
	while (ptr_export != NULL)
	{
		if (!ft_strcmp(ptr_export->name, name_to_search))
		{
			free(ptr_export->value);
			ptr_export->value = ft_substr(argument,
					len_name + 1, ft_len(ft_strchr(argument, '=')));
			free(name_to_search);
			return ;
		}
		ptr_export = ptr_export->nxt;
	}
	if (ptr_export == NULL)
		handle_export_null(data, argument, len_name);
	free(name_to_search);
}

void	process_export_without_equal(t_data *data, char *argument)
{
	t_var	*ptr_export;
	char	*name_to_search;
	int		len_name;

	ptr_export = data->export;
	len_name = (ft_len(argument));
	name_to_search = ft_substr(argument, 0, len_name);
	while (ptr_export != NULL)
	{
		if (!(ft_strcmp(ptr_export->name, name_to_search)))
			return ;
		ptr_export = ptr_export->nxt;
	}
	if (ptr_export == NULL)
		ft_lstadd_back_new(&data->export,
			ft_lstnew_new(ft_substr(argument, 0, ft_len(argument)), NULL));
	free(name_to_search);
}

void	handle_export_null(t_data *data, char *argument, int len_name)
{
	if (((ft_strchr(argument, '=')) + 1) == NULL)
		ft_lstadd_back_new(&data->export,
			ft_lstnew_new(ft_substr(argument, 0, len_name), ft_strdup("")));
	else
		ft_lstadd_back_new(&data->export,
			ft_lstnew_new(ft_substr(argument, 0, len_name),
				ft_substr(argument, len_name + 1,
					ft_len(ft_strchr(argument, '=')) + 1)));
}

t_var	*ft_lstlast_test(t_var *lst)
{
	if (!(lst))
		return (NULL);
	while (lst->nxt)
		lst = lst->nxt;
	return (lst);
}
