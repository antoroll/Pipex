/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 14:01:45 by arolland          #+#    #+#             */
/*   Updated: 2021/09/28 15:17:56 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	child2_bonus(t_data *d, char **argv)
{
	if (d->i == 0)
	{
		d->infile = open(argv[1], O_RDONLY);
		ft_exit_bonus(d, "infile", d->infile);
		dup2(d->infile, STDIN_FILENO);
		dup2(d->pipes[d->i + 1][1], STDOUT_FILENO);
		close(d->pipes[d->i + 1][1]);
		close(d->infile);
	}
	else if (d->i == (d->size - 1))
	{
		d->outfile = open(argv[d->size + 2], O_RDWR | O_CREAT | O_TRUNC, 0644);
		ft_exit_bonus(d, "outfile", d->outfile);
		dup2(d->pipes[d->i][0], STDIN_FILENO);
		dup2(d->outfile, STDOUT_FILENO);
		close(d->pipes[d->i][0]);
		close(d->outfile);
	}
	else
	{
		dup2(d->pipes[d->i][0], STDIN_FILENO);
		dup2(d->pipes[d->i + 1][1], STDOUT_FILENO);
		close(d->pipes[d->i + 1][1]);
		close(d->pipes[d->i][0]);
	}
}

void	child3_bonus(t_data *data)
{
	while (++data->j < (data->size + 1))
	{
		if (data->i != data->j)
			if (close(data->pipes[data->j][0]) == -1)
				perror("Close failed");
		if (data->i + 1 != data->j)
			if (close(data->pipes[data->j][1]) == -1)
				perror("Close failed");
	}
}

void	execve_child(t_data *data, char **envp, char **argv)
{
	data->cmd = ft_split(argv[data->i + 2], ' ');
	invalid_command_bonus(data);
	data->paths = path(data, envp, data->cmd);
	if (data->paths == NULL)
	{
		ft_putstr_fd("Command not found: ", 2);
		ft_putendl_fd(data->cmd[0], 2);
		free_all(data);
		exit(EXIT_FAILURE);
	}
	if (execve(data->paths, data->cmd, envp) == -1)
	{
		ft_putstr_fd("Command not found: ", 2);
		ft_putendl_fd(data->cmd[0], 2);
		free_all(data);
		exit(EXIT_FAILURE);
	}
}

void	exec_multipipes_bonus(t_data *data, char **argv, char **envp)
{
	open_pipes(data);
	while (++data->i < data->size)
	{
		do_fork(data);
		if (data->pids[data->i] == 0)
		{
			if (data->cmd)
				free_tab(data->cmd);
			child3_bonus(data);
			child2_bonus(data, argv);
			execve_child(data, envp, argv);
		}
	}
	parent_bonus(data);
	free_all(data);
}

void	parent_bonus(t_data *data)
{
	int	i;
	int	k;

	i = -1;
	while (++i < data->size + 1)
	{
		if (i != data->size)
			close(data->pipes[i][0]);
		if (i != 0)
			close(data->pipes[i][1]);
	}
	close(data->pipes[0][1]);
	close(data->pipes[data->size][0]);
	k = -1;
	while (++k < data->size)
		waitpid(*data->pids, 0, 0);
}
