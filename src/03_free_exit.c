/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_free_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 02:33:05 by jhurpy            #+#    #+#             */
/*   Updated: 2023/07/11 18:39:22 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	exit_error(char *str, int status, t_cmd *cmd, t_input *input)
{
	perror(str);
	if (cmd)
		free_struct(cmd);
	if (input)
		free(input);
	exit(EXIT_FAILURE);
}

void	free_2d_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_struct(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd[i].cmd != NULL)
	{
		free_2d_array(cmd[i].cmd);
		free(cmd[i].path);
		i++;
	}
	free(cmd);
}
