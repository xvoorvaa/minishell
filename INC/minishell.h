#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include "libft.h"

// TODO
# define T_DEFAULT_TOKEN (T_LITERAL_EXPANDING)

// TODO: maybe after the literals have been expanded,
// set to a more sane T_LITERAL so we don't have to if/else as much etc.
// TODO: >> <<
enum e_token {
	T_UNKNOWN,
	T_LITERAL,
	T_LITERAL_EXPANDING,
	T_LITERAL_NONEXPANDING,
	T_PIPE,
	T_REDIRECT_STDOUT_TO_FILE, /* > */
	T_REDIRECT_STDOUT_TO_FILE_APPEND, /* >> */
	T_REDIRECT_FILE_TO_STDIN, /* < */
	T_HEREDOC /* << */
};

typedef struct s_envlist
{
	char				*variable;
	char				*content;
	struct s_envlist	*next;
}	t_envlist;

typedef struct s_token
{
	char			*content;
	int				separated_from_previous;
	enum e_token	token;
	struct s_token	*next;
}	t_token;

typedef struct s_vars
{
	unsigned char	exit_code;
	char			*old_pwd;
	char			*pwd;
	char			**environ;
	t_token			*token_list;
	t_envlist		*var_list;
}	t_vars;

/*
	MINISHELL
*/

int		init_vars(const char *line, t_vars *vars);

int		execute_line(t_vars *vars);

/*
	FUNCTIONS
*/

int		exec_echo(t_vars *vars);

int		exec_cd(t_vars *vars);

int		change_env_pwd(t_vars *vars);

int		exec_pwd(t_vars *vars);

int		exec_export(t_vars *vars);

int		exec_unset(t_vars *vars);

int		exec_env(t_vars *vars);

int		exec_exit(t_vars *vars);

int		exec_command(t_vars *vars);

/*
	LINKED LIST
*/

void	new_node(t_envlist **head, char *variable, char *content);

void	print_list(t_envlist *head);

void	print_token(t_token *head);

t_token	*token_new(char *content, const enum e_token type);

t_token	*token_li_last(t_token *lst);

void	token_li_push_back(t_token **lst, t_token *new);

t_token	*token_li_pop_back(t_token **tlst);

void	token_free(t_token *token);

void	token_free_list(t_token **lst);

/*
	LEXER
*/
void	lex(t_token **tlst, const char *line);

void	expand_token(t_token *el, const t_vars *vars);

/*
	CHECK_CHAR
*/

int		check_delimiter(char *prompt);

int		check_redirect_stdin(char *prompt);

int		check_redirect_stdout_append(char *prompt);

int		check_redirect_stdout(char *prompt);

int		check_pipes(char *prompt);

/*
	ERRORS
*/

void	fatal_error(const char *msg, unsigned char err_number);

/*
	ACCESS
*/

char	**find_dir(char *envp[]);

char	*path_check(char *func, char **path);

#endif
