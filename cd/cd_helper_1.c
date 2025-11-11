#include "../minishell.h"

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
    while (*s && *s != '/')
        *str++ = *s++;
    if (*s)
        *++str = '\0';
    else
        *str = '\0';
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
    while (ref != path && b != 2)
    {
        if (*ref == '/')
            b++;
        ref--;
    }
    return (ft_substr(path, 0, ref - path));
}

void    ft_set_pwd(char *old_pwd, char *pwd, char *operand, char *path)
{

}