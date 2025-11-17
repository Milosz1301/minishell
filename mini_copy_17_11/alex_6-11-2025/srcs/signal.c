#include "../minishell.h"

void    ft_sa_handler(int signal)
{
    g_received_signal = signal;
    if (signal == SIGINT)
    {
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay(); 
    }
}

void    ft_signals(int signal)
{
    struct sigaction sa;

    sa.sa_handler = ft_sa_handler;
    sigemptyset(&sa.sa_mask);
    if (signal == SIGINT)
        sigaddset(&sa.sa_mask, SIGQUIT);
    else if (signal == SIGQUIT)
    {
        sigaddset(&sa.sa_mask, SIGINT);
        sigaddset(&sa.sa_mask, SIGQUIT)
    }
    sa.sa_flags = 0;
    if (sigaction(signal, &sa, NULL))
	    exit(2);
}
