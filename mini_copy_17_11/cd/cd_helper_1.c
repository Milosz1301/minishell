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
#include "libft.h"

char    *ft_first_operator(char  *s)
{
    char    *str;
    char    *ref;

    ref = s;
    while (*ref && *ref != '/')
        ref++;
    str = malloc(ref - s + 1);
    if (!str)
        return (NULL);
    ref = str;
    while (*s && *s != '/')
        *ref++ = *s++;
    if (*s)
    {
        *ref = '/';
        *++ref = '\0';
    }
    else
        *ref = '\0';
    return (str);
}

int ft_back_slash(char *s)
{
    while (*s)
    {
        if (*s == '/')
            return (1);
        s++;
    }
    return (0);
}

char    *ft_get_parent_dir(char *path)
{
    char    *ref;
    int b;

    b = 0;
    ref = path;
    while (*ref)
        ref++;
    if (*--ref == '/')
    {
        while (ref != path && b != 2)
        {
            if (*ref == '/')
                b++;
            ref--;
        }
    }
    else
        while (ref != path && *ref != '/')
            ref--;
    return (ft_substr(path, 1, ref - path));
}

char    *ft_generative_path(char *operand, char *path)
{
    char    *temp;
    int i;

    temp = NULL;
    i = 0;
    while (*operand)
    {
        printf("LOOP PATH[%d]: %s\n", i++, path);
        temp = ft_first_operator(operand);
        if (!ft_strncmp(temp, "..", 3) || !ft_strncmp(temp, "../", 4))
            path = ft_get_parent_dir(path);
        else if (!ft_strncmp(temp, ".", 1) || !ft_strncmp(temp, "./", 2))
        {
            operand += ft_strlen(temp);
            continue;
        }
        else
            path = ft_strjoin(path, temp);
        operand += ft_strlen(temp);
    }
    return (path);
}

void    ft_set_old_new_pwd_value(char **old_pwd, char **pwd, char **old_path, char **new_path)
{
    *old_pwd = *old_path;
    *pwd = *new_path;
}

void    ft_chdir(char *destination_path, char **old_pwd, char **pwd, char *old_path)
{
    struct stat st;

    printf("DEST PATH: %s\n", destination_path); 
    if (!stat(destination_path, &st))
        if (S_ISDIR(st.st_mode))
            if (!access(destination_path, X_OK))
            {
                printf("PASSED ACCESS\n");
                ft_set_old_new_pwd_value(old_pwd, pwd, &old_path, &destination_path);
                chdir(destination_path);
            }
    
}
