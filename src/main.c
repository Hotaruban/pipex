/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 18:08:50 by jhurpy            #+#    #+#             */
/*   Updated: 2023/07/25 02:35:36 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int ac, char **av, char **ev)
{
	int		index;
	pid_t	*pid;
	int		status;
	int		i;

	index = check_args(ac, av);
	pid = fork_process(ac, av, ev, index);
	i = 0;
	while (i + index < ac - 1)
		waitpid(pid[i++], &status, WUNTRACED);
	if (ft_strncmp("here_doc", av[1], 9) == 0)
		unlink("here_doc");
	free(pid);
	return (WEXITSTATUS(status));
}
