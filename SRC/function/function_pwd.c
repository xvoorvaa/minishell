/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   function_pwd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/21 12:17:10 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/03/30 15:32:28 by xvoorvaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h" /* ft_strcmp */
#include "ft_printf.h"

#include <stdlib.h> /* Free */
#include <stdio.h> /* perror */
#include <unistd.h> /* getcwd */

/*
	PWD: Print Working Directory
	It prints the directory you are in right now.
*/

static int	find_env_pwd(t_vars *vars)
{
	int	i;

	i = 0;
	while (vars->environ[i] != NULL)
	{
		if (ft_strncmp(vars->environ[i], "PWD=", 4) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	change_env_pwd(t_vars *vars)
{
	int		i;
	char	*temp;

	i = find_env_pwd(vars);
	if (i < 0)
		return (-1);
	temp = getcwd(NULL, 0);
	if (temp == NULL)
	{
		perror("getcwd");
		return (0);
	}
	free(vars->environ[i]);
	vars->environ[i] = ft_strjoin("PWD=", temp);
	free(temp);
	return (SUCCESS);
}

int	exec_pwd(char *argv[], t_vars *vars)
{
	if (argv != NULL)
	{
		if (vars->pwd != NULL)
			free(vars->pwd);
		vars->pwd = getcwd(NULL, 0);
		if (vars->pwd == NULL)
			vars->pwd = ft_getenv("PWD", vars->environ);
		ft_printf("%s\n", vars->pwd);
	}
	return (SUCCESS);
}
