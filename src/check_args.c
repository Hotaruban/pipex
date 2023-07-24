/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 18:10:30 by jhurpy            #+#    #+#             */
/*   Updated: 2023/07/24 22:46:47 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	check_args(int ac, char **av)
{
	int	index;

	if (ac < 5 || (ac < 6 && ft_strncmp("here_doc", av[1], 9) == 0))
	{
		perror("Error: wrong number of arguments");
		exit(EXIT_FAILURE);
	}
	index = 2;
	if (!ft_strncmp("here_doc", av[1], 9))
	{
		creat_here_doc(av[1], av[2]);
		index++;
	}
	return (index);
}
