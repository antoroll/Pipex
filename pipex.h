/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 19:09:58 by arolland          #+#    #+#             */
/*   Updated: 2021/09/17 18:40:15 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef PIPEX_H

# define PIPEX_H
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>

typedef struct s_data {
	int		i;
	int		j;
	int		k;
	int		o;
	int		g;
	int		b;
	int		flag;
	int		flag2;
	int		flag3;
	int		size;
	int		pid;
	int		outfile;
	int		infile;
	int		heredoc;
	int		**pipes_mandatory;
	char	**cmd;
	char	*paths;
	int		*pids;
	int		**pipes;
}	t_data;

char	**ft_split(const char *str, char c);
char	*ft_strjoin(const char *s1, const char *s2);
void	ft_putendl_fd(char const *s, int fd);
void	ft_putstr_fd(char const *s, int fd);
int		ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_exit(t_data *data, char *str, int file, char *tab);
void	ft_exit_bonus(t_data *data, char *str, int file);
void	free_arr(char **str);
void	free_tab(char **str);
char	*path(t_data *data, char **envp, char **cmd);
void	child_process(t_data *data, char **argv, char **envp, char **cmd);
void	parent_process(t_data *data, int *pid);
void	exec_mandatory(t_data *data, char **argv, char **envp);
int		get_next_line(int fd, char **line, int ret);
void	invalid_command(t_data *data, char **cmd);
void	invalid_command_bonus(t_data *data);
void	open_pipes(t_data *data);
void	exec_multipipes_bonus(t_data *data, char **argv, char **envp);
void	parent_bonus(t_data *data);
void	init_vars(t_data *data, int ac, char **av);
void	error_args(t_data *data);
void	here_doc_parent(t_data *data, int *end, char **argv, char **envp);
void	here_doc_child(t_data *data, int *end, char **argv, char **envp);
void	check_heredoc(t_data *data, int ac, char **argv);
void	exec_heredoc_bonus(t_data *data, char **argv, char **envp);
void	do_fork(t_data *data);
void	free_all(t_data *data);
void	free_mandatory(t_data *data, char **cmd, char *str);
void	free_cmd(t_data *data, char **cmd);
void	free_paths(t_data *data, char *paths, char **cmd);

#	endif
