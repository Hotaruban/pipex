/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 21:26:30 by jhurpy            #+#    #+#             */
/*   Updated: 2023/07/24 22:44:41 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	pipe_process(char *infile, int pipefd[2], int flag)
{
	if (pipe(pipefd) == -1)
		exit_error("Error: pipe failed");
	if (flag == 0)
		open_infile(infile, pipefd);
}
