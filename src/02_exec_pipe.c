/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_exec_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 13:48:01 by jhurpy            #+#    #+#             */
/*   Updated: 2023/07/11 18:12:36 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	first_child(t_cmd cmd, t_input *input)
{
	int		fd;

	fd = open(input->infile, O_RDONLY);
	dup2(fd, STDIN_FILENO);
	dup2(input->pipefd[1], STDOUT_FILENO);
	close(input->pipefd[0]);
	close(input->pipefd[1]);
	close(fd);
	execve(cmd.path, cmd.cmd, input->ev); // exit(EXIT_FAILURE); // manage error EXECVE FAILED
}

static void	middle_child(t_cmd cmd, t_input *input, int tmpfd)
{
	int		fd;

	dup2(tmpfd, STDIN_FILENO);
	dup2(input->pipefd[1], STDOUT_FILENO);
	close(input->pipefd[0]);
	close(input->pipefd[1]);
	close(tmpfd);
	close(fd);
	execve(cmd.path, cmd.cmd, input->ev); // exit(EXIT_FAILURE); // manage error EXECVE FAILED
}

static void	last_child(t_cmd cmd, t_input *input, int tmpfd)
{
	int		fd;

	fd = open(input->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(tmpfd, STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(tmpfd);
	close(fd);
	execve(cmd.path, cmd.cmd, input->ev); //exit(EXIT_FAILURE); // manage error EXECVE FAILED
}

void	exec_cmd(t_cmd *cmd, t_input *input)
{
	pid_t	pid;
	int		i;

	i = -1;
	while (cmd[++i].cmd != NULL)
	{
		if (cmd[i + 1].cmd != NULL)
			pipe(input->pipefd);
		pid = fork();
		if (pid < 0)
			exit(EXIT_FAILURE); // manage error FORK FAILED
		if (pid == 0 && i == 0)
			first_child(cmd[i], input);
		else if (pid == 0 && cmd[i + 1].cmd == NULL)
			last_child(cmd[i], input, input->tmpfd);
		else if (pid == 0)
			middle_child(cmd[i], input, input->tmpfd);
		if (pid > 0)
		{
			input->tmpfd = dup(input->pipefd[0]);
			close(input->pipefd[0]);
			close(input->pipefd[1]);
		}
	}
	waitpid(pid, NULL, 0);
}
