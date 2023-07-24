/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_infile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 20:08:48 by jhurpy            #+#    #+#             */
/*   Updated: 2023/07/24 22:52:06 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	open_infile(char *infile, int pipefd[2])
{
	int	fd_in;

	fd_in = open(infile, O_RDONLY);
	if (fd_in == -1)
		perror(infile);
	if ((access(infile, R_OK) == -1 && access(infile, F_OK) == 0)
			|| access(infile, F_OK) == -1 || fd_in == -1)
	{
		if (dup2(pipefd[0], STDIN_FILENO) == -1)
			exit_error("Error: dup2 failed");
		close(pipefd[0]);
		close(pipefd[1]);
	}
	else
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
}
