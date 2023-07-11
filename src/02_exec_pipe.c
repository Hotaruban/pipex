/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_exec_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 13:48:01 by jhurpy            #+#    #+#             */
/*   Updated: 2023/07/11 23:54:50 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	first_child(t_cmd cmd, t_input *input)
{
	int		fd;

	if (cmd.status > 0)
		message_shell(cmd);
	input->status = 0;
	fd = open(input->infile, O_RDONLY);
	if (fd == -1)
		error(input->infile, errno, NULL, input);
	input->status += dup2(fd, STDIN_FILENO);
	input->status += dup2(input->pipefd[1], STDOUT_FILENO);
	input->status += close(input->pipefd[0]);
	input->status += close(input->pipefd[1]);
	input->status += close(fd);
	input->status += execve(cmd.path, cmd.cmd, input->ev);
	if (input->status != 0)
		error(cmd.path, errno, NULL, input);
}

static void	middle_child(t_cmd cmd, t_input *input, int tmpfd)
{
	if (cmd.status > 0)
		message_shell(cmd);
	input->status = 0;
	input->status += dup2(tmpfd, STDIN_FILENO);
	input->status += dup2(input->pipefd[1], STDOUT_FILENO);
	input->status += close(input->pipefd[0]);
	input->status += close(input->pipefd[1]);
	input->status += close(tmpfd);
	input->status += execve(cmd.path, cmd.cmd, input->ev);
	if (input->status != 0)
		error(cmd.path, errno, NULL, input);
}

static void	last_child(t_cmd cmd, t_input *input, int tmpfd)
{
	int		fd;

	if (cmd.status > 0)
		message_shell(cmd);
	input->status = 0;
	fd = open(input->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		error(input->infile, errno, NULL, input);
	input->status += dup2(tmpfd, STDIN_FILENO);
	input->status += dup2(fd, STDOUT_FILENO);
	input->status += close(tmpfd);
	input->status += close(fd);
	input->status += execve(cmd.path, cmd.cmd, input->ev);
	if (input->status != 0)
		error(cmd.path, errno, NULL, input);
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
			exit(EXIT_FAILURE);
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
