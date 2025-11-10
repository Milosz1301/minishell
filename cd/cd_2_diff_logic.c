#include "../../minishell.h"

int ft_cd_2(char **argv, char **old_pwd_value, char **pwd_value, t_error *err)
{
    struct stat st;
    char    *path;
    char    *old_path;
    char    *buffer; 
    char    *buffer2;
    char    *operand;
    char    *temp;

    if (!*(++argv))
        return (err->cd = 1);
    operand = *argv;
    buffer = malloc(_PC_PATH_MAX);
    buffer2 = malloc(_PC_PATH_MAX);
    old_path = getcwd(buffer2, _PC_PATH_MAX);
    path =  ft_strjoin(getcwd(buffer, _PC_PATH_MAX), "/");
    if (!stat(operand, &st))                // ABSOLUTE PATH
            if (st.st_mode == __S_IFDIR)
                if (!access(operand, F_OK && X_OK))
                {
                    *old_pwd_value = old_path;
                    *pwd_value = operand;
                    chdir(operand);
                }
    else
    {
        if (!ft_strncmp(operand, ".", 2) || !ft_strncmp(operand, "./", 3))
        {
            *old_pwd_value = old_path;      // SAME DIR (cd . OR  cd ./)
            *pwd_value = old_path;
        }
        while (*operand)
        {
            temp = ft_first_operator(operand);
            if (!ft_strncmp(temp, "..", 3) || !ft_strncmp(temp, "../", 4))
                path = ft_get_parent_dir(path);
            else if (!ft_strncmp(temp, ".", 1) || !ft_strncmp(temp, "./", 2))
            {
                operand += ft_strlen(temp);
                continue;                   // ALL OTHER PATHS
            }
            else
                path = strjoin(path, temp);
            operand += ft_strlen(temp);
        }
         if (!stat(path, &st))
            if (st.st_mode == __S_IFDIR)
                if (!access(path, F_OK && X_OK))
                {
                    *old_pwd_value = old_path;
                    *pwd_value = path;
                    chdir(path);
                }
    }
    return (err->cd = 0);
}