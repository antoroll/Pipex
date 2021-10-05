/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 16:22:03 by arolland          #+#    #+#             */
/*   Updated: 2021/09/27 17:36:51 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parent_process(t_data *data, int *pid)
{
	int	i;

	i = -1;
	while (++i < 3)
	{
		if (i != 2)
			close(data->pipes_mandatory[i][0]);
		if (i != 0)
			close(data->pipes_mandatory[i][1]);
	}
	close(data->pipes_mandatory[0][1]);
	close(data->pipes_mandatory[2][0]);
	i = -1;
	while (++i < 2)
		waitpid(*pid, 0, 0);
	i = -1;
	while (++i < 2 + 1)
		free(data->pipes_mandatory[i]);
	free(data->pipes_mandatory);
}
