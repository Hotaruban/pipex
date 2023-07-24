/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_outfile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 20:11:56 by jhurpy            #+#    #+#             */
/*   Updated: 2023/07/24 22:54:34 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	open_outfile(char *outfile, int index)
{
	int	fd_out;

	if (index == 1)
		fd_out = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd_out = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
		exit_error("Open failed");
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		exit_error("Dup2 failed");
	close(fd_out);
}
