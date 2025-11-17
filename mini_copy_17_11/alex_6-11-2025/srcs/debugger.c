#include "../minishell.h"

void    print_token_chain(t_token *chain, int token_amount)
{
	int i;

	i = 0;
	while (i < token_amount)
	{
		s_token_dgb(chain);
		chain = chain->next;
		i++;
	}
}

void	print_redir_chain(t_redirect *red_chain)
{
	ft_printf("\n		REDIRECTION-------------\n");
	while (red_chain)
	{
		ft_printf("			-------------------------\n");
		ft_printf("				TYPE:	%d\n", red_chain->type);
		ft_printf("				TARGET:	%s\n", red_chain->target);
		ft_printf("				Q_TYPE:	%d\n", red_chain->q_type);
		ft_printf("				NEXT:	%p\n", red_chain->next);
		ft_printf("			-------------------------\n");
		red_chain = red_chain->next;
	}
}

void    print_pipeline(t_pipe *pipeline)
{
	ft_printf("PIPELINE-----------------\n");
	while (pipeline)
	{
		ft_printf("----------------------------------------\n");
		print_token_chain(pipeline->command->cmd_chain, ft_chainlen(pipeline->command->cmd_chain) + 1);
		ft_printf("     ARGV:\n");
		ft_print_arr(pipeline->command->argv);
		print_redir_chain(pipeline->command->red_chain);
		ft_printf("		CMD_AMOUNT: %d\n", pipeline->cmd_amount);
		ft_printf("		NEXT:		%p\n", pipeline->next);
		ft_printf("----------------------------------------\n");
		pipeline = pipeline->next;
	}
}

char    *s_token_type(int num)
{
	char *array[] = {"T_NONE", "T_WORD", "T_REDIR", "T_PIPE_OP", "T_END"};

	return(array[num]);
}

char    *s_qtype(int num)
{
	char *array[] = {"Q_NONE", "Q_BOTH", "Q_DOUBLE", "Q_SINGLE"};
	
	return (array[num]);
}

void    s_token_dgb(t_token *token)
{ 
	printf("	TOKEN->STRING: %s\n", token->string);
	printf("	TOKEN->TYPE: %s\n", s_token_type(token->type));
	printf("	TOKEN->Q_TYPE: %s\n", s_qtype(token->q_type));
	printf("	TOKEN->NEXT: %p\n", token->next);
}

char    *s_redir_type(int num)
{
	char    *array[] = {"RE_NONE", "RE_IN", "RE_OUT", "RE_APPEND", "RE_HEREDOC"};

	return (array[num]);
}

void    s_redirect_dgb(t_redirect *redir)
{
	printf("REDIRECT->TYPE: %s\n", s_redir_type(redir->type));
	printf("REDIRECT->TARGET: %s\n", redir->target);
	printf("REDIRECT->Q_TYPE: %s\n", s_qtype(redir->q_type));
}

void    s_cmd(t_cmd *command)
{
	int i;

	i = 0;
	while (command->argv[i])
	{
		printf("CMD->ARGV[%i]: %s\n", i , command->argv[i]);
		i++;
	}
	printf("CMD->CMD_CHAIN->TOKEN->STRING: %s\n", command->cmd_chain->string);
	printf("CMD->CMD_CHAIN->TOKEN->TYPE: %s\n", s_token_type(command->cmd_chain->type));
	printf("CMD->CMD_CHAIN->TOKEN->Q_TYPE: %s\n", s_qtype(command->cmd_chain->q_type));
	printf("CMD->CMD_CHAIN->TOKEN->NEXT: %p\n", command->cmd_chain->next);

	printf("CMD->RED_CHAIN->TYPE: %s\n", s_redir_type(command->red_chain->type));
	printf("CMD->RED_CHAIN->TARGET: %s\n", command->red_chain->target);
	printf("CMD->RED_CHAIN->Q_TYPE: %s\n", s_qtype(command->red_chain->q_type));
}

void    s_pipe(t_pipe *pipeline)
{
	int i;

	i = 0;
	while (pipeline->command->argv[i])
	{
		printf("PIPE->COMMAND->ARG[%i]: %s\n", i , pipeline->command->argv[i]);
		i++;
	}
	printf("PIPE->CMD->CMD_CHAIN->TOKEN->STRING: %s\n", pipeline->command->cmd_chain->string);
	printf("PIPE->CMD->CMD_CHAIN->TOKEN->TYPE: %s\n", s_token_type(pipeline->command->cmd_chain->type));
	printf("PIPE->CMD->CMD_CHAIN->TOKEN->Q_TYPE: %s\n", s_qtype(pipeline->command->cmd_chain->q_type));
	printf("PIPE->CMD->CMD_CHAIN->TOKEN->NEXT: %p\n", pipeline->command->cmd_chain->next);

	printf("PIPE->CMD_AMOUNT: %i\n", pipeline->cmd_amount);
	printf("PIPE->NEXT: %p\n", pipeline->next);
}

void    ft_print_envc(t_envar *envc)
{
	while (envc)
	{
		ft_printf("ENVC----------------------------------\n");
		ft_printf("		KEY: 		%s\n", envc->key);
		ft_printf("		VALUES: 	%s\n", envc->value);
		ft_printf("		EXP_STATUS:	%d\n", envc->is_exported);
		ft_printf("		NEXT:		%p\n", envc->next);
		ft_printf("--------------------------------------\n");
		envc = envc->next;
	}
}

void	ft_print_envp(char	**envp)
{
	ft_printf("ENVP ARRAY---------------------\n");
	ft_print_arr(envp);
	ft_printf("-------------------------------\n");
}
