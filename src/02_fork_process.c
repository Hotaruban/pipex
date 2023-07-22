/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_fork_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 21:35:07 by jhurpy            #+#    #+#             */
/*   Updated: 2023/07/22 22:18:33 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	exit_error(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	fork_process(char *av, char **ev)
{
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
		exit_error("pipe\n");
	pid = fork();
	if (pid == -1)
		exit_error("fork\n");
	else if (pid == 0)
	{
		if (close(fd[0]) == -1)
			exit_error("close\n");
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			exit_error("dup2\n");
		execute_cmd(av, ev);
	}
	else if (pid > 0)
	{
		if (close(fd[1]) == -1)
			exit_error("close\n");
		if (dup2(fd[0], STDIN_FILENO) == -1)
			exit_error("dup2\n");
		waitpid(pid, 0, WUNTRACED);
	}
}
