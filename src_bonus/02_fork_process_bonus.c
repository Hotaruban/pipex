/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_fork_process_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 21:35:07 by jhurpy            #+#    #+#             */
/*   Updated: 2023/07/23 04:11:25 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/pipex_bonus.h"

static void	exit_error(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

int	fork_process(char *av, char **ev)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		exit_error("fork\n");
	else if (pid == 0)
		execute_cmd(av, ev);
	return (pid);
}
