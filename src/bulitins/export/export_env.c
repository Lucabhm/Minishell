/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 12:52:54 by ntalmon           #+#    #+#             */
/*   Updated: 2024/05/14 11:47:25 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	is_valid(char *str)
{
	while (*str && *str != '=')
	{
		if (*str == '+' && *(str + 1) == '=')
			return (1);
		if (!ft_isalnum(*str) && *str != '_' && *str != '"')
			return (0);
		str++;
	}
	return (1);
}

void	process_env_argument(t_data *data, t_exe *cmd, int i)
{
	t_var	*ptr_env;
	char	*name_to_search;
	int		len_name;

	ptr_env = data->envs;
	while (cmd->argv[i])
	{
		if (ft_strchr(cmd->argv[i], '=') && (cmd->argv[i][0] != '='
			|| !is_valid(cmd->argv[i])))
		{
			len_name = (ft_len(cmd->argv[i])
					- ft_len(ft_strchr(cmd->argv[i], '=')));
			name_to_search = ft_substr(cmd->argv[i], 0, len_name);
			ptr_env = search_variable(data, name_to_search);
			if (ptr_env != NULL)
				update_variable(ptr_env, cmd->argv[i], len_name);
			else
				add_variable(data, cmd->argv[i], len_name);
			free(name_to_search);
		}
		i++;
	}
}

void	exe_export_env(t_data *data, t_exe *cmd)
{
	int	i;

	i = 1;
	if (cmd->argv[1] == NULL)
		print_export(&data->export);
	while (cmd->argv[i])
	{
		if (cmd->argv[i][0] == '-')
			return ;
		else if (ft_isdigit(cmd->argv[i][0]))
			return ;
		else if (cmd->argv[i][0] == '=' || !is_valid(cmd->argv[i]))
			return ;
		i++;
	}
	process_env_argument(data, cmd, 1);
	g_signal = 0;
}

void	print_export_element(t_var *element)
{
	char	*temp;
	char	*pos;

	if (element->value == NULL)
		printf("declare -x %s\n", element->name);
	else if (element->value != NULL)
	{
		pos = ft_strchr(element->name, '+');
		if (pos != NULL)
		{
			temp = malloc(pos - element->name + 1);
			ft_strlcpy(temp, element->name, pos - element->name);
			temp[pos - element->name] = '\0';
			printf("declare -x %s=\"%s\"\n", temp, element->value);
			free(temp);
		}
		else
			printf("declare -x %s=\"%s\"\n", element->name, element->value);
	}
}

void	print_export(t_var **export)
{
	t_var	*ptr;

	ptr = *export;
	if (ptr == NULL || ptr->name == NULL)
	{
		printf("Keine Umgebungsvariablen vorhanden.\n");
		return ;
	}
	while (ptr != NULL)
	{
		print_export_element(ptr);
		ptr = ptr->nxt;
	}
}
