//#include "../../minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>

void    ft_chdir(char *destination_path, char **old_pwd, char **pwd, char *old_path);
char    *ft_first_operator(char  *s);
int ft_back_slash(char *s);
char    *ft_get_parent_dir(char *path);
char    *ft_generative_path(char *operand, char *path);
void    ft_set_old_new_pwd_value(char **old_pwd, char **pwd, char **old_path, char **new_path);

int ft_cd_2(char **argv, char **old_pwd_value, char **pwd_value)
{
    struct stat st;
    char    *path;
    char    *old_path;
    char    *operand;
    int i;

    /*if (!*(++argv))
        return (err->cd = 1);*/
    i = 0;
    operand = *++argv;
    old_path = getcwd(NULL, 0);
    path = old_path;
    printf("OPERAND: %s\n", operand);
    if (!stat(operand, &st) && !ft_strncmp(operand, "/", 1))
    {
        printf("ABSOLUTE PATH: %s\n", operand);
        ft_chdir(operand, old_pwd_value, pwd_value, old_path);
    }
    else
    {
        if (!ft_strncmp(operand, ".", 2) || !ft_strncmp(operand, "./", 3))
        {
            printf(".   ||  ./\n");
            ft_set_old_new_pwd_value(old_pwd_value, pwd_value, &old_path, &old_path);
        }
        printf("Before path\n");
        path = ft_generative_path(operand, path);
        ft_set_old_new_pwd_value(old_pwd_value, pwd_value, &old_path, &path);
    }
    return (0);
}

int	main(int argc, char *argv[])
{
	int	lol;
	char	*old_pwd_value = "/nfs/homes/mstawski/github/minishell_10_11/cd";
	char	*pwd_value = "/nfs/homes/mstawski/github/minishell_10_11/cd";

    printf("OLDPWD before: %s\n", old_pwd_value);
    printf("PWD before: %s\n", pwd_value);
	lol = ft_cd_2(argv, &old_pwd_value, &pwd_value);
    printf("OLDPWD: %s\n", old_pwd_value);
    printf("PWD: %s\n", pwd_value);
}