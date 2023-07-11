/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 22:23:44 by jhurpy            #+#    #+#             */
/*   Updated: 2023/07/11 23:40:34 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static t_input	*init_input(int ac, char **av, char **ev)
{
	t_input	*input;

	input = (t_input *)malloc(sizeof(t_input));
	if (input == NULL)
		error("malloc", errno, NULL, NULL);
	input->ac = ac;
	input->cmd_nbr = ac - 2;
	input->pipefd[0] = -1;
	input->av = av;
	input->ev = ev;
	input->infile = av[0];
	input->outfile = av[ac - 1];
	return (input);
}

static t_cmd	*init_cmd(t_input *input)
{
	t_cmd	*cmd;
	int		i;

	cmd = (t_cmd *)malloc(sizeof(t_cmd) * (input->cmd_nbr + 1));
	if (cmd == NULL)
		error("malloc", errno, NULL, input);
	i = 0;
	while (i < input->cmd_nbr)
	{
		cmd[i].status = 0;
		cmd[i].cmd = ft_split(input->av[i + 1], ' ');
		if (cmd[i].cmd == NULL)
			error("malloc", errno, cmd, input);
		cmd[i].path = check_cmd_path(cmd, input, i);
		i++;
	}
	cmd[input->cmd_nbr].cmd = NULL;
	return (cmd);
}

int	main(int ac, char **av, char **ev)
{
	t_input	*input;
	t_cmd	*cmd;

	if (ac < 5)
		exit(0);
	input = init_input((ac - 1), &av[1], ev);
	cmd = init_cmd(input);
	exec_cmd(cmd, input);
	free_struct(cmd);
	free(input);
	return (0);
}

/*
	int i = 0;
	while (i < ac - 2)
	{
		int j = 0;
		while (cmd[i].cmd[j] != NULL)
		{
			printf("cmd[%d].cmd[%d] = %s\n", i, j, cmd[i].cmd[j]);
			j++;
		}
		printf("cmd[%d].path = %s\n", i, cmd[i].path);
		i++;
	}
*/
