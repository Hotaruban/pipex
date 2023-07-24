/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 21:54:22 by jhurpy            #+#    #+#             */
/*   Updated: 2023/07/25 01:04:08 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

pid_t	*fork_process(int ac, char **av, char **ev, int index)
{
	pid_t	*pid;
	int		pipefd[2];
	int		i;

	pid = (pid_t *)malloc(sizeof(pid_t) * (ac - index - 1));
	if (!pid)
		exit_error("pipex: malloc failed", NULL);
	i = 0;
	while (index + i < ac - 1)
	{
		pipe_process(av[1], pipefd, i);
		pid[i] = fork();
		if (pid[i] == -1)
			exit_error("pipex: fork failed", NULL);
		else if (pid[i] == 0)
			child_process(pipefd, av, ev, i + index);
		else if (pid[i] > 0)
			parent_process(pipefd);
		i++;
	}
	return (pid);
}
