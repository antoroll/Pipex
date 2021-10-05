/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 14:59:40 by arolland          #+#    #+#             */
/*   Updated: 2021/09/27 17:35:04 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_pipes(t_data *data)
{
	int	i;

	i = -1;
	data->pipes_mandatory = NULL;
	data->pipes_mandatory = malloc(sizeof(int *) * 3);
	if (!data->pipes_mandatory)
		exit(EXIT_FAILURE);
	while (++i < 3)
	{
		data->pipes_mandatory[i] = malloc(sizeof(int) * 2);
		if (!data->pipes_mandatory[i])
			free_mandatory(data, NULL, NULL);
	}
	i = -1;
	while (++i < 3)
	{
		if (pipe(data->pipes_mandatory[i]) == -1)
		{
			ft_putstr_fd("Error\nPipe creation failed\n", 2);
			free_mandatory(data, NULL, NULL);
		}
	}
}

void	execve_child(t_data *data, char **cmd, char *paths, char **envp)
{
	if (execve(paths, cmd, envp) == -1)
	{
		ft_putstr_fd("Error\nPipex: command not found: ", 2);
		ft_putendl_fd(cmd[0], 2);
		free_mandatory(data, cmd, paths);
	}
}

void	child_process(t_data *data, char **argv, char **envp, char **cmd)
{
	char	*paths;

	paths = NULL;
	if (data->b == 0)
	{
		data->infile = open(argv[1], O_RDONLY);
		ft_exit(data, "infile", data->infile, paths);
		dup2(data->infile, STDIN_FILENO);
		close(data->infile);
		dup2(data->pipes_mandatory[data->b + 1][1], STDOUT_FILENO);
		close(data->pipes_mandatory[data->b + 1][1]);
	}
	else if (data->b == 1)
	{
		data->outfile = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
		ft_exit(data, "outfile", data->outfile, paths);
		dup2(data->pipes_mandatory[data->b][0], STDIN_FILENO);
		dup2(data->outfile, STDOUT_FILENO);
		close(data->outfile);
		close(data->pipes_mandatory[data->b][0]);
	}
	cmd = ft_split(argv[data->b + 2], ' ');
	invalid_command(data, cmd);
	paths = path(data, envp, cmd);
	execve_child(data, cmd, paths, envp);
}

void	child2(t_data *data)
{
	int	i;

	i = -1;
	while (++i < 3)
	{
		if (data->b != i)
			close(data->pipes_mandatory[i][0]);
		if (data->b + 1 != i)
			close(data->pipes_mandatory[i][1]);
	}
}

void	exec_mandatory(t_data *data, char **argv, char **envp)
{
	int		pid[2];
	char	**cmd;

	data->b = -1;
	cmd = NULL;
	open_pipes(data);
	while (++data->b < 2)
	{
		pid[data->b] = fork();
		if (pid[data->b] == 0)
		{
			if (cmd)
				free_tab(cmd);
			child2(data);
			child_process(data, argv, envp, cmd);
		}
	}
	parent_process(data, pid);
}
