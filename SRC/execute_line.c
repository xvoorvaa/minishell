/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_line.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 17:44:20 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/02/21 16:18:54 by xvoorvaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

//TODO: Error handeling
int	execute_line(t_vars *vars)
{
	int	i;

	i = 0;
	if (ft_strcmp(vars->prompt[i], "echo") == 0)
		exec_echo(*vars);
	else if (ft_strcmp(vars->prompt[i], "cd") == 0)
		exec_cd(vars);
	else if (ft_strcmp(vars->prompt[i], "pwd") == 0)
		exec_pwd(*vars);
	else
	{
		printf("%s\n", strerror(errno));
		exit(errno);
	}
	return (0);
}
