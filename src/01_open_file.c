/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_open_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:10:52 by jhurpy            #+#    #+#             */
/*   Updated: 2023/07/22 23:02:47 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	exit_error(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	infile_open(char *infile)
{
	int	fd_in;
	int	fd[2];

	fd_in = open(infile, O_RDONLY);
	if ((access(infile, R_OK) == -1 && access(infile, F_OK) == 0)
		|| fd_in == -1 || access(infile, F_OK) == -1)
	{
		perror(infile);
		pipe(fd);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
	}
	if (fd_in != -1)
	{
		if (dup2(fd_in, STDIN_FILENO) == -1)
			perror("Error: dup2 failed\n");
		close(fd_in);
	}
}

void	outfile_open(char *outfile)
{
	int	fd_out;

	fd_out = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd_out == -1)
		exit_error(outfile);
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		perror("Error: dup2 failed\n");
	close(fd_out);
}
