/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 17:36:44 by jhurpy            #+#    #+#             */
/*   Updated: 2023/07/22 23:41:59 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int ac, char **av, char **ev)
{
	if (ac != 5)
	{
		perror("Wrong number of arguments\n");
		exit(EXIT_FAILURE);
	}
	infile_open(av[1]);
	fork_process(av[2], ev);
	outfile_open(av[4]);
	execute_cmd(av[3], ev);
	return (0);
}
