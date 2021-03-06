/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   function_unset.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/22 16:48:33 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/04/05 16:56:06 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h" /* strcmp */
#include "ft_printf.h" /* ft_dprintf */

#include <stdlib.h> /* Free */
#include <unistd.h> /* STD */

/*
	UNSET:
	Unsets an env variable or usr variable.

	Keys are unique and needs to be overwriten
*/

static void	nonfatal_error(char *argv)
{
	ft_dprintf(STDERR_FILENO,
		"minishell: unset: '%s': not a valid identifier\n", argv);
}

static int	check_usr_vars(char *argv, t_vars *vars)
{
	t_envlist	*prev;
	t_envlist	*temp_env;

	prev = NULL;
	temp_env = vars->var_list;
	if (temp_env != NULL && ft_strcmp(temp_env->variable, argv) == 0)
	{
		vars->var_list = temp_env->next;
		free(temp_env->variable);
		free(temp_env->content);
		free(temp_env);
		return (SUCCESS);
	}
	while (temp_env != NULL && ft_strcmp(temp_env->variable, argv) != 0)
	{
		prev = temp_env;
		temp_env = temp_env->next;
	}
	if (temp_env == NULL)
		return (-1);
	prev->next = temp_env->next;
	free(temp_env->variable);
	free(temp_env->content);
	free(temp_env);
	return (SUCCESS);
}

static void	moves_lines_up(t_vars *vars, char *temp_var, int i)
{
	free(vars->environ[i]);
	while (vars->environ[i + 1] != NULL)
	{
		vars->environ[i] = vars->environ[i + 1];
		i++;
	}
	free(temp_var);
	vars->environ[i] = NULL;
}

static int	check_sys_vars(char *argv, t_vars *vars)
{
	int		i;
	char	*temp_var;

	i = 0;
	temp_var = ft_strjoin(argv, "=");
	if (temp_var == NULL)
		malloc_fail();
	while (vars->environ[i] != NULL)
	{
		if (ft_strncmp(temp_var, vars->environ[i], \
				ft_strlen(temp_var)) == 0)
		{
			moves_lines_up(vars, temp_var, i);
			return (SUCCESS);
		}
		i++;
	}
	free(temp_var);
	return (-1);
}

int	exec_unset(char *argv[], t_vars *vars)
{
	int	i;
	int	ret;

	i = 0;
	vars->exit_code = 0;
	if (argv[1] == NULL)
		return (SUCCESS);
	while (argv[i] != NULL)
	{
		if (ft_is_valid_unsetarg(argv[i]) == false)
		{
			nonfatal_error(argv[i]);
			vars->exit_code = ERROR;
		}
		else
		{
			ret = check_sys_vars(argv[i], vars);
			if (ret != 0)
				check_usr_vars(argv[i], vars);
		}
		i++;
	}
	return (vars->exit_code);
}
