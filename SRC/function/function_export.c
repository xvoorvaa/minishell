/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   function_export.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: xander <xander@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/21 21:34:06 by xander        #+#    #+#                 */
/*   Updated: 2022/03/30 17:04:10 by xvoorvaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h" /* Several functions */
#include "ft_printf.h" /* ft_dprintf */

#include <stdlib.h> /* free */
#include <unistd.h> /* STD */

static int	nonfatal_error(char *argv)
{
	ft_dprintf(STDERR_FILENO, \
		"minishell: export: %s: not a valid identifier\n", argv);
	return (ERROR);
}

static int	print_export(t_vars *vars)
{
	t_envlist	*temp;

	temp = vars->var_list;
	order_sys_env(*vars);
	order_usr_env(temp);
	return (SUCCESS);
}

static void	allocate_var(char *argv, char **content, char **variable)
{
	*content = ft_strchr(argv, '=');
	if (*content != NULL)
	{
		*content = ft_substr(*content, 1, ft_strlen(*content));
		if (*content == NULL)
			malloc_fail();
	}
	*variable = ft_substr(argv, 0, ft_strequel(argv));
	if (*variable == NULL)
		malloc_fail();
}

int	exec_export(char *argv[], t_vars *vars)
{
	int			i;
	char		*variable;
	char		*content;

	if (argv[1] == NULL)
		return (print_export(vars));
	i = 1;
	while (argv[i] != NULL)
	{
		if (ft_strlen(argv[i]) > 0 && ft_valued_chars(argv[i]) == true)
		{
			allocate_var(argv[i], &content, &variable);
			if (check_dup_env(*vars, variable) == true)
			{
				replace_dup_env(vars, variable, content);
				free(variable);
			}
			else
				new_node(&vars->var_list, variable, content);
		}
		else
			return (nonfatal_error(argv[i]));
		i++;
	}
	return (SUCCESS);
}
