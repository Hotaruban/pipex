/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_infile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 20:08:48 by jhurpy            #+#    #+#             */
/*   Updated: 2023/07/24 23:55:36 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	open_infile(char *infile)
{
	int	fd_in;
	int	tmpfd[2];

	fd_in = open(infile, O_RDONLY);
	if (fd_in == -1)
		perror("pipex");
	if ((access(infile, R_OK) == -1 && access(infile, F_OK) == 0)
			|| access(infile, F_OK) == -1 || fd_in == -1)
	{
		if (pipe(tmpfd) == -1)
			exit_error("pipex: ", "pipe failed ");
		if (dup2(tmpfd[0], STDIN_FILENO) == -1)
			exit_error("pipex: ", "dup2 failed ");
		close(tmpfd[0]);
		close(tmpfd[1]);
	}
	else
	{
		if (dup2(fd_in, STDIN_FILENO) == -1)
			exit_error("pipex: ", "dup2 failed ");
		close(fd_in);
	}
}
