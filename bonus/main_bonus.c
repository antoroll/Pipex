/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 15:15:50 by arolland          #+#    #+#             */
/*   Updated: 2021/09/18 14:42:45 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_data	d[1];

	if (envp == NULL)
		return (1);
	init_vars(d, ac, av);
	if (ac < 5)
		error_args(d);
	if (d->flag == 0)
		exec_multipipes_bonus(d, av, envp);
	else
		exec_heredoc_bonus(d, av, envp);
	return (0);
}
