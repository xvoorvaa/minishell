/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_getargc.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/15 17:54:59 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/03/30 15:37:22 by xvoorvaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h> /* NULL */

/* returns the length(i.e. argc) of a char **argv */
int	ft_getargc(char *argv[])
{
	int	argc;

	argc = 0;
	while (argv[argc] != NULL)
		argc++;
	return (argc);
}
