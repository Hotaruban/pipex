/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 01:03:38 by jhurpy            #+#    #+#             */
/*   Updated: 2023/07/20 23:02:04 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	exit_error(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

static int	fork_process(char *av, char **ev)
{
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
		exit_error("Error: pipe failed\n");
	pid = fork();
	if (pid == -1)
		exit_error("Error: fork failed\n");
	else if (pid == 0)
	{
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			exit_error("Error: dup2 failed\n");
		execute_cmd(av, ev);
	}
	else if (pid > 0)
	{
		close(fd[1]);
		if (dup2(fd[0], STDIN_FILENO) == -1)
			exit_error("Error: dup2 failed\n");
		waitpid(pid, 0, WUNTRACED);
	}
	return (0);
}

static int	open_fd(char *infile, char *outfile)
{
	int	fd_in;
	int	fd_out;

	fd_in = open(infile, O_RDONLY);
	fd_out = open(outfile, O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (fd_in == -1 || fd_out == -1)
		exit_error("Error: open failed\n");
	if (dup2(fd_in, STDIN_FILENO) == -1)
	{
		close(fd_in);
		if (fd_out != -1)
			close(fd_out);
		exit_error("Error: dup2 failed\n");
	}
	close(fd_in);
	return (fd_out);
}

int	main(int ac, char **av, char **ev)
{
	int	i;
	int	fd_out;
	int	signal;

	if (ac != 5)
		exit_error("Error: too few arguments\n");
	else
		fd_out = open_fd(av[1], av[ac - 1]);
		i = 2;
	while (i < ac - 2)
		signal = fork_process(av[i++], ev);
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		exit_error("Error: dup2 failed\n");
	execute_cmd(av[i], ev);
	return (WEXITSTATUS (signal));
}
