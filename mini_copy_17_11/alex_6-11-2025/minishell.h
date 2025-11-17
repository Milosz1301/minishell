/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akonstan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 18:49:31 by akonstan          #+#    #+#             */
/*   Updated: 2025/11/13 18:43:33 by mstawski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdbool.h>
# include "libft_extended/libft.h"
# include <sys/stat.h>
# include <sys/types.h>

//Enum with quotation type
//We have the Q_NONE type because ft_bzero will set the enum var to 0
//which is the first member of the enum group 
typedef enum s_quote_type
{
	Q_NONE,
	Q_BOTH,
	Q_DOUBLE,
	Q_SINGLE
} t_quote_type;

//Enum with all the redirection types
typedef enum s_redir_type
{
	RE_NONE,
	RE_IN,
	RE_OUT,
	RE_APPEND,
	RE_HEREDOC
} t_redir_type;

//Enum with all the token types. Quotes should not be their own tokens
//We filter them in the lexer out and we set squotesd or dquoted flags
//on the token
//T_END will be signaling the end of a token chain
typedef enum s_token_type
{
	T_NONE,
	T_WORD,
	T_REDIR,
	T_PIPE_OP,
	T_END
} t_token_type;

//Enum with all the built in types. We will check the argv passed to execution
//and see if we have a matching built-in
typedef enum s_built_in
{
	B_NONE,
	B_CD,
	B_ECHO,
	B_ENV,
	B_EXIT,
	B_EXPORT,
	B_PWD,
	B_UNSET
} t_built_in;

//Token structure which the lexer will give as output
//We will work on a single linked list of tokens called CHAIN
typedef struct s_token
{
	char			*string;
	t_token_type	type;
	t_quote_type	q_type;
	struct s_token	*next;
} t_token;

//Redirections structure, shows what kind of redirection we have and
//where it should target
//The two bools describe the filename
typedef struct s_redirect
{
	t_redir_type		type;
	char				*target;
	t_quote_type		q_type;
	struct s_redirect	*next;
} t_redirect;

//Command struct that holds the actuall command to execute and any 
//redirections (if they exist)
//the token array will be holding the tokens during parsing and the expander
//will use them to create the argv array to pass to the executor
typedef struct s_cmd
{
	char			**argv;
	t_token			*cmd_chain;
	t_redirect		*red_chain;
} t_cmd;

//Pipe structure that holds the command on the current pipe and
//a pointer pointing to the next pipe
typedef struct s_pipe
{
	t_cmd			*command;
	unsigned int	cmd_amount;
	struct s_pipe	*next;
} t_pipe;

//Envar structure will be holding lal the necessary information about 
//environmental variables
typedef struct s_envar
{
	char			*key;
	char			*value;
	int				is_exported;
	struct s_envar	*next;
} t_envar;

//This is an error holding struct. We will pass t_error variables as
//arguments so that functions will assign the value to the specific 
//error type
typedef struct s_error
{
	int	del_shell;
	int	del_token;
	int	del_token_chain;
	int	del_redir_chain;
	int	del_cmd;
	int	del_pipeline;
	int get_last_pipe;
	int	new_pipe;
	int	add_pipe;
	int	purify_cmd_chain;
	int	get_cmd_chain;
	int	get_red_chain;
	int	check_token_chain;
	int	parser;
	int	env_len;
	int	get_start;
	int	get_dollar;
	int	expand_dollar;
	int	expand_str;
	int	expand_redir;
	int	expand_cmd;
	int	rmquotes;
	int	set_cmd_argv;
	int	expander;
	int	get_last_envar;
	int	new_envar;
	int	add_envar;
	int	del_envar;
	int	get_envar;
	int	valid_env;
	int	envar_amount;
	int	set_envp;
	int	word_amount;
	int	echo;
	int	lexer;
	int	check_for_built_in;
	int	extract_key;
	int	extract_value;
	int	set_envc;
	int	check_file_access;
	int	append;
	int	infile;
	int	outfile;
	int	handle_redir;
	int	redirector;
	int	del_envc;
	int	pathfinder;
	int	env;
	int	ft_export;
	int	forking_check;
	int	run_in_child;
	int	executor;
	int	exec_built_in;
	int	pathseter;
	int	exec_cmd;
	int	run_first_built_in;
	int	cd;
} t_error;

//This structure holds information about the shell state, like the exit status
//of the last executed command
typedef struct s_shell
{
	char		*input;
	char		**envp;
	char		**path_arr;
	t_envar		*envc;
	t_error		*err;
	t_token		*chain;
	int			last_exit;
	int			env_amount;
} t_shell;

//-----------------------------------------------------------------------------
//PARSER (1)
//-----------------------------------------------------------------------------
t_pipe			*ft_parser(t_token **chain, t_error *err);
//-----------------------------------------------------------------------------
//PARSER HELPER 1 (4)
//-----------------------------------------------------------------------------
size_t			ft_pipelen(t_token *chain);
t_pipe			*ft_get_last_pipe(t_pipe *pipeline, t_error *err);
t_pipe			*ft_new_pipe(t_token **chain, t_error *err);
int				ft_add_pipe(t_pipe **pipeline, t_token **chain, t_error *err);
//-----------------------------------------------------------------------------
//PARSER HELPER 2 (5)
//-----------------------------------------------------------------------------
t_redirect		*ft_get_red_chain(t_token *cmd_chain, t_error *err);
int				ft_purify_cmd_chain(t_token **cmd_chain, t_error *err);
t_token			*ft_get_cmd_chain(t_token **chain, t_error *err);
int				ft_check_token_chain(t_token *chain, t_error *err);
//-----------------------------------------------------------------------------
//EXECUTOR (1)
//-----------------------------------------------------------------------------
void			ft_refresh_rl(void);
int				ft_executor(t_pipe  *pipeline, t_shell *shell, t_error *err);
//-----------------------------------------------------------------------------
//EXECUTOR HELPER (2)
//-----------------------------------------------------------------------------
t_built_in		ft_check_for_built_in(char *string, t_error *err);
int				ft_exec_built_in(t_built_in built_in, t_shell *shell,
					char **argv, t_pipe *pipeline);
int				ft_pathseter(t_envar *envc, t_shell *shell);
char			*ft_pathfinder(char *command, t_shell *shell);
int				ft_exec_cmd(t_pipe *pipe, t_shell *shell, t_error *err);
//-----------------------------------------------------------------------------
//EXPANDER (4)
//-----------------------------------------------------------------------------
int				ft_expand_str(char **str, t_shell *shell, t_error *err);
int				ft_expander(t_pipe *pipeline, t_shell *shell, t_error *err);
//-----------------------------------------------------------------------------
//EXPANDER HELPER 1 (5)
//-----------------------------------------------------------------------------
char			*ft_get_dollar(char *str, t_error *err);
int				ft_expand_dollar(char **str, char *dollar,
					t_shell *shell, t_error *err);
//-----------------------------------------------------------------------------
//EXPANDER HELPER 2 (5)
//-----------------------------------------------------------------------------
char			*ft_rmchar(char **s, char *c);
int         	ft_rmquotes(char **s, t_error *err);
//-----------------------------------------------------------------------------
//EXPANDER HELPER 3 (3)
//-----------------------------------------------------------------------------
int				ft_isenvchar(int c);
int				ft_set_cmd_argv(t_pipe *pipe, t_shell *shell, t_error *err);
int				ft_handle_qumark(char **target, char **result,
					char *start, t_shell *shell);
//-----------------------------------------------------------------------------
//REDIR STRUCT HELPER (4)
//-----------------------------------------------------------------------------
t_redirect		*ft_new_redir(t_redir_type type, char *target, t_quote_type q_type);
t_redirect		*ft_get_last_redir(t_redirect *red_chain);
void			ft_add_redir(t_redirect **red_chain, t_redirect *redirect);
size_t			ft_redirlen(t_redirect *red_chain);
//-----------------------------------------------------------------------------
//REDIRECTOR HELPER (5)
//-----------------------------------------------------------------------------
int				ft_append(char *filepath, t_error *err);
int				ft_infile(char *filepath, t_error *err);
int				ft_outfile(char *filepath, t_error *err);
int				ft_heredoc(char *delimeter, t_quote_type q_type,
					t_shell *shell);
//-----------------------------------------------------------------------------
//REDIRECTOR (2)
//-----------------------------------------------------------------------------
int				ft_redirector(t_redirect *red_chain,
					t_shell *shell, t_error *err);
//-----------------------------------------------------------------------------
//TOKENS HELPER (4)
//-----------------------------------------------------------------------------
t_token			*ft_new_token(t_token_type type, char *str,
					t_quote_type q_type);
t_token			*ft_get_last_token(t_token *chain);
void			ft_add_token(t_token **chain, t_token *token);
size_t			ft_chainlen(t_token *chain);
//-----------------------------------------------------------------------------
//CLEANER (5)
//-----------------------------------------------------------------------------
int				ft_del_token(t_token **chain, t_token *token, t_error *err);
int				ft_del_token_chain(t_token **chain, t_error *err);
int				ft_del_redir_chain(t_redirect **red_chain, t_error *err);
int				ft_del_cmd(t_cmd **command, t_error *err);
int				ft_del_pipeline(t_pipe **pipeline, t_error *err);
//-----------------------------------------------------------------------------
//CLEANER HELPER 1 (1)
//-----------------------------------------------------------------------------
void			ft_del_string(char *string);
size_t			ft_count_arr(char **arr);
void			ft_freearr(char **arr, size_t index);
int				ft_del_shell(t_shell *shell);
int				ft_del_envc(t_envar **envc, t_error *err);
//-----------------------------------------------------------------------------
//ERROR CHECKER (2)
//-----------------------------------------------------------------------------
int				ft_error_check_parser(t_error *err);
int				ft_error_check_expander(t_error *err);
//-----------------------------------------------------------------------------
//ENVAR HELPER 1 (5)
//-----------------------------------------------------------------------------
t_envar			*ft_get_last_envar(t_envar *envc, t_error *err);
t_envar			*ft_new_envar(char *key, char *value,
					int is_exported, t_error *err);
int				ft_add_envar(t_envar **envc, t_envar *var, t_error *err);
int				ft_del_envar(t_envar **envc, t_envar *var, t_error *err);
t_envar			*ft_get_envar(t_envar *envc, char *key, t_error *err);
//-----------------------------------------------------------------------------
//ENVAR HELPER 2 (5)
//-----------------------------------------------------------------------------
char			**ft_set_envp(t_envar *envc, t_error *err);
char			*ft_extract_key(char *str, t_error *err);
char			*ft_extract_value(char *str, t_error *err);
t_envar			*ft_set_envc(char **envp, t_error *err);
//-----------------------------------------------------------------------------
//ENVAR HELPER 3 (2)
//-----------------------------------------------------------------------------
int				ft_valid_env(char *key, t_error *err);
size_t			ft_envar_amount(t_envar *envc, t_error *err);
//-----------------------------------------------------------------------------
//LEXER (1)
//-----------------------------------------------------------------------------
t_token			*lexer(char *input, t_error *err);
//-----------------------------------------------------------------------------
//LEXER HELPER 1 (5)
//-----------------------------------------------------------------------------
bool			ft_squote_check(char **s);
bool			ft_dquote_check(char **s);
t_quote_type	ft_set_qtype(char *str);
t_token_type	ft_set_token_type(char *string);
void			ft_create_chain(t_token **chain, char **input_arr);
//-----------------------------------------------------------------------------
//LEXER HELPER 2 (8)
//-----------------------------------------------------------------------------
char			**ft_split_mini(char *s, char c, t_error *err);
int				ft_split_logic(char **str_arr, char *s, char c);
//-----------------------------------------------------------------------------
//LEXER HELPER 3 (4)
//-----------------------------------------------------------------------------
int				ft_handle_quotes(char **s);
int				ft_ww_redir(char **s);
void			ft_inquote(char c, int *s_quote, int *d_quote);
void			ft_wa_handle_word(int in_arr[], size_t *words, char *s);
size_t			ft_word_amount(char *s, char c, t_error *err);
//-----------------------------------------------------------------------------
//BUILT-INS
//>>
//-----------------------------------------------------------------------------
//	 CD (2)
//-----------------------------------------------------------------------------
int			ft_cd(char **argv, t_shell *shell);
void			ft_cd_operation(char *operand, char **pwd_value, char **old_pwd_value);
//-----------------------------------------------------------------------------
//	 ECHO (3)
//-----------------------------------------------------------------------------
int 			ft_echo(char **argv, t_shell *shell, t_error *err);
//-----------------------------------------------------------------------------
//	 ENV (1)
//-----------------------------------------------------------------------------
void		    ft_print_arr(char **arr);
int				ft_env(char **argv, t_shell *shell);
//-----------------------------------------------------------------------------
//	 EXIT (1)
//-----------------------------------------------------------------------------
void			ft_exit(t_pipe *pipeline, t_shell *shell);
//-----------------------------------------------------------------------------
//	 EXPORT (3)
//-----------------------------------------------------------------------------
int				ft_export(char **argv, t_shell *shell);
//-----------------------------------------------------------------------------
//	 PWD (1)
//-----------------------------------------------------------------------------
int				ft_pwd(char **argv, t_shell *shell);
//-----------------------------------------------------------------------------
//	 UNSET (3)
//-----------------------------------------------------------------------------
int				ft_unset(char **argv, t_shell *shell);
//>>
//-----------------------------------------------------------------------------
//DEBUGGER
//-----------------------------------------------------------------------------
void    print_token_chain(t_token *chain, int token_amount);
void	print_redir_chain(t_redirect *red_chain);
void    print_pipeline(t_pipe *pipeline);
char    *s_token_type(int num);
char    *s_qtype(int num);
void    s_token_dgb(t_token *token);
char    *s_redir_type(int num);
void    s_redirect_dgb(t_redirect *redir);
void    s_cmd(t_cmd *command);
void    s_pipe(t_pipe *pipeline);
void    ft_print_envc(t_envar *envc);
void	ft_print_envp(char	**envp);
#endif
