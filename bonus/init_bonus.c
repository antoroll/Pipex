/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 16:33:40 by arolland          #+#    #+#             */
/*   Updated: 2021/09/18 15:14:59 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	check_heredoc(t_data *data, int ac, char **av)
{
	int	i;

	data->size = 0;
	data->g = -1;
	if (ac == 6 && (ft_strncmp(av[1], "here_doc", ft_strlen("here_doc")) == 0))
	{
		i = -1;
		data->flag = 1;
		while (av[++i])
			data->size++;
		data->size -= 4;
	}
	else
	{
		i = -1;
		data->flag = 0;
		while (av[++i])
			data->size++;
		data->size -= 3;
	}
}

void	init_counters(t_data *data)
{
	data->i = -1;
	data->j = -1;
	data->k = -1;
	data->o = -1;
	data->g = -1;
	data->flag2 = 0;
	data->flag3 = 0;
	data->pid = 0;
	data->paths = NULL;
	data->cmd = NULL;
	data->pipes = NULL;
	data->pids = NULL;
}

void	init_vars(t_data *data, int ac, char **av)
{
	check_heredoc(data, ac, av);
	init_counters(data);
	if (data->flag == 0)
	{
		data->pids = malloc(sizeof(int) * data->size);
		if (!data->pids)
			free_all(data);
		data->pipes = malloc(sizeof(int *) * (data->size + 1));
		if (!data->pipes)
			free(data->pipes);
		while (++data->g < data->size + 1)
		{
			data->pipes[data->g] = malloc(2 * sizeof(int));
			if (!data->pipes[data->g])
				free_all(data);
		}
	}
}
