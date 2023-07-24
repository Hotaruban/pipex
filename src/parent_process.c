/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 21:48:57 by jhurpy            #+#    #+#             */
/*   Updated: 2023/07/24 23:54:39 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	parent_process(int pipefd[2])
{
	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
		exit_error("pipex: ", "dup2 failed ");
	close(pipefd[0]);
}
