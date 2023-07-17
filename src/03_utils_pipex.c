/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_utils_pipex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 01:19:43 by jhurpy            #+#    #+#             */
/*   Updated: 2023/07/17 16:30:34 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	error(char *str, char *cmd, int flag)
{
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd(cmd, STDERR_FILENO);
	if (flag == 1)
		exit(EXIT_FAILURE);
}

void	free_2d(char **array)
{
	int	i;

	i = -1;
	while (array[++i] != NULL)
		free(array[i]);
	free(array);
}
