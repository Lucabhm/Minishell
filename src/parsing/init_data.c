/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntalmon <ntalmon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:08:26 by lbohm             #+#    #+#             */
/*   Updated: 2024/05/14 13:48:13 by ntalmon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	init_data(t_data *data, char **env)
{
	init_data_structure(data);
	init_cmd_path_and_env(data, env);
}

void	init_data_structure(t_data *data)
{
	data->envs = NULL;
	data->export = NULL;
	data->path_exe = NULL;
	data->in = NULL;
	data->cmd_path = NULL;
	data->s_n = NULL;
	data->fdout = dup(STDOUT_FILENO);
	data->fdin = dup(STDIN_FILENO);
	data->fdhere = dup(STDOUT_FILENO);
	data->child = NULL;
	data->childnbr = 0;
	data->fdpipe = dup(STDIN_FILENO);
}

void	init_cmd_path_and_env(t_data *data, char **env)
{
	int	i;

	i = 0;
	data->cmd_path = (char **)malloc((count_argvs(env) + 1) * sizeof(char *));
	while (env[i])
	{
		data->cmd_path[i] = ft_strdup(env[i]);
		i++;
	}
	data->cmd_path[i] = NULL;
	init_env(env, &data->envs, 1);
	init_env(env, &data->export, 0);
	add_oldpwd(&data->export);
	sort_export(&data->export);
}

void	welcome_message(void)
{
	char	*lbohm;
	char	*ntalmon;

	lbohm = "https://profile.intra.42.fr/users/lbohm";
	ntalmon = "https://profile.intra.42.fr/users/ntalmon";
	printf("\n\n\n");
	printf("███    ███ ██ ███    ██ ██ ███████ ");
	printf("██   ██ ███████ ██      ██      \n");
	printf("████  ████ ██ ████   ██ ██ ██      ");
	printf("██   ██ ██      ██      ██      \n");
	printf("██ ████ ██ ██ ██ ██  ██ ██ ███████ ");
	printf("███████ █████   ██      ██      \n");
	printf("██  ██  ██ ██ ██  ██ ██ ██      ██ ");
	printf("██   ██ ██      ██      ██      \n");
	printf("██      ██ ██ ██   ████ ██ ███████ ");
	printf("██   ██ ███████ ███████ ███████ \n");
	printf("\n\n\n");
	printf("\t\t\t\e]8;;%s\albohm\e]8;;\a x \e]8;;%s\antalmon\e]8;;\a\n\n",
		lbohm, ntalmon);
}
