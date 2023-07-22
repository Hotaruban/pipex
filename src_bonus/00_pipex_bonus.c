/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_pipex_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 17:36:44 by jhurpy            #+#    #+#             */
/*   Updated: 2023/07/23 04:25:46 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/pipex_bonus.h"

static void	exit_error(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

static int	argv_check(int ac, char **av)
{
	int	flag;

	flag = 2;
	if (ac < 5 || (ac < 6 && ft_strncmp(av[1], "here_doc", 9) == 0))
		exit_error("Wrong number of arguments");
	if (ft_strncmp(av[1], "here_doc", 9) == 0)
	{
		here_doc(av[1], av[2]);
		flag = 3;
	}
	return (flag);
}

void static	execute_pipe(int flag)
{
	int	fd[2];

	if (pipe(fd) == -1)
		exit_error("pipe");
	if (flag == 1)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			exit_error("dup2");
		if (close(fd[0]) == -1 || close(fd[1]) == -1)
			exit_error("close");
	}
	if (flag == 2)
	{
		if (dup2(fd[0], STDIN_FILENO) == -1)
			exit_error("dup2");
		if (close(fd[0]) == -1 || close(fd[1]) == -1)
			exit_error("close");
	}
}

int	main(int ac, char **av, char **ev)
{
	int	i;
	int j;
	int	flag;
	pid_t	*pid;
	int	status;

	flag = argv_check(ac, av);
	i = flag;
	pid = (pid_t *)malloc(sizeof(pid_t) * (ac - (i + 1)));
	j = 0;
	infile_open(av[1]);
	while (i < ac - 1)
	{
		if (i != 1)
			execute_pipe(2);
		pid[j++] = fork_process(av[i++], ev);
		if (i == ac - 2)
			outfile_open(av[ac - 1], flag);
		else
			execute_pipe(1);
	}
	if (access("here_doc", F_OK) == 0)
		unlink("here_doc");
	j = 0;
	while (j < ac - flag - 2)
		waitpid(pid[j++], &status, WUNTRACED);
	return (WEXITSTATUS(status));
}
