/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes2_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 17:58:25 by arolland          #+#    #+#             */
/*   Updated: 2021/09/18 15:00:57 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	open_pipes(t_data *data)
{
	while (++data->o < (data->size + 1))
	{
		if (pipe(data->pipes[data->o]) == -1)
		{
			ft_putstr_fd("Error\nPipe creation failed\n", 2);
			free_all(data);
			exit(EXIT_FAILURE);
		}
	}
}

void	do_fork(t_data *data)
{
	data->pids[data->i] = fork();
	if (data->pids[data->i] == -1)
	{
		ft_putstr_fd("Error\nProcess creation failed\n", 2);
		free_all(data);
		exit(EXIT_FAILURE);
	}
}

void	free_cmd(t_data *data, char **cmd)
{
	if (cmd[0] == NULL)
	{
		if (cmd)
		{
			ft_putstr_fd("Command not found : «  »\n", 2);
			free_tab(cmd);
			cmd = NULL;
		}
		free_all(data);
		exit(EXIT_FAILURE);
	}
}

void	free_paths(t_data *data, char *paths, char **cmd)
{
	if (paths == NULL)
	{
		ft_putstr_fd("Command not found: ", 2);
		ft_putendl_fd(cmd[0], 2);
		free_arr(&paths);
		free_tab(cmd);
		paths = NULL;
	}
	free_all(data);
	exit(EXIT_FAILURE);
}
