/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 20:04:24 by jhurpy            #+#    #+#             */
/*   Updated: 2023/07/24 22:56:11 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	child_process(int pipefd[2], char **av, char **ev, int index)
{
	if (av[index + 3] == NULL && ft_strncmp("here_doc", av[1], 9) == 0)
		open_outfile(av[index + 1], 1);
	else if (av[index + 2] == NULL)
		open_outfile(av[index + 1], 2);
	else
	{
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			exit_error("Error: dup2 failed");
	}
	close(pipefd[0]);
	close(pipefd[1]);
	execute_cmd(av[index], ev);
}
