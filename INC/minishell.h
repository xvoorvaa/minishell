/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: xvoorvaa <xvoorvaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/01 14:09:18 by xvoorvaa      #+#    #+#                 */
/*   Updated: 2022/02/16 16:45:19 by xvoorvaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include "libft.h"

enum e_token {
	tok_unknown,
	tok_literal,
	tok_pipe,
	tok_redirect,
	tok_redirect_file_to_stdin
};

typedef struct s_token
{
	char			*content;
	struct s_token	*next;
	enum e_token	token;
}			t_token;

typedef struct s_parsing
{
	char	**prompt;
	int		flag_check;
	int		pipe_check;
	t_token	*tokenizer;
}	t_parsing;

t_token	*token_new(char *content, const enum e_token type);
t_token	*token_li_last(t_token *lst);
void	token_li_push_back(t_token **lst, t_token *new);

/*
	MINISHELL
*/

int		init_parsing(t_parsing *parsing);


/*
	LINKED LIST
*/

void	new_node(t_token **head, char *content);

void	print_list(t_token *head);

#endif
