/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_pipex_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 17:36:44 by jhurpy            #+#    #+#             */
/*   Updated: 2023/07/22 23:44:26 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/pipex_bonus.h"

int	main(int ac, char **av, char **ev)
{
	int	i;

	i = 2;
	if (ac < 5 || (ac < 6 && ft_strncmp(av[1], "here_doc", 9) == 0))
	{
		perror("Wrong number of arguments\n");
		exit(EXIT_FAILURE);
	}
	if (ft_strncmp(av[1], "here_doc", 9) == 0)
	{
		here_doc(av[1], av[2]);
		i++;
	}
	infile_open(av[1]);
	while (i < ac - 2)
		fork_process(av[i++], ev);
	outfile_open(av[ac - 1]);
	if (access("here_doc", F_OK) == 0)
		unlink("here_doc");
	execute_cmd(av[i], ev);
	return (0);
}
