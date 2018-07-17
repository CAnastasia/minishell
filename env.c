#include "includes/minishell.h"

void set_path(char *str, char ***paths)
{
    if (str != NULL)
        {
            *paths = ft_strsplit(str, ':');
            free(str);
        }
        else
            *paths = NULL;
}
void  path_str(char **envs, char ***paths)
{
    int i;
    char *str;
    int j;
    int k;

    i = 0;
    str = NULL;
    while(envs[i])
    {
        if(ft_strncmp(envs[i], "PATH=", 5) == 0)
        {
            str = ft_strnew(ft_strlen(envs[i]) - 5);
            j = 5;
            k = 0;
            while (j < ft_strlen(envs[i]))
            {
                str[k] = envs[i][j];
                k++;
                j++;
            }
        }
        i++;
    }
    set_path(str, paths);
}

int size_str(char **environ)
{
    int i;

    i = 0;
    while(environ[i] != NULL)
    {
        i++;
    }
    return (i);
}

char **copy_env(char **environ, int size)
{
    char **env;
    int i = 0;

    if (!(env = (char**)malloc(sizeof(*env) * (size + 1))))
        return (NULL);
    env[size] = NULL;
    while(environ[i] != NULL)
    {
        env[i] = ft_strdup(environ[i]);
        i++;
    }
    return (env);
}

void free_str(char **str)
{
    int i;

    i = 0;
    while(str[i])
    {
        free(str[i]);
        i++;
    }
    free(str);
    str = NULL;
}

void free_str_2(char **str, int size)
{
    int i;

    i = 0;
    while(i < size)
    {
        if (str[i] != NULL)
            free(str[i]);
        i++;
    }
    free(str);
    str = NULL;
}

void check_path_loop(char **path_env, char **path, char **str, int *count)
{
 int j;
    char *join_slash;
    char *join_cmd;

    j = 0;

     while(path_env[j])
            {
                join_slash = ft_strjoin(path_env[j], "/");
                join_cmd = ft_strjoin(join_slash, *str);
                free(join_slash);
                if (access(join_cmd, F_OK) == 0)
                {
                    if (*count >= 1)
                        free(*path);
                    *path = ft_strdup(join_cmd);
                    (*count)++;
                }
                j++;
                free(join_cmd);
            }
}
int check_path(char **path_env, char **path, char **str)
{
    int count;


    count = 0;
    if (path_env != NULL)
    {
        check_path_loop(path_env, path, str, &count);
       /* while(path_env[j])
        {
            join_slash = ft_strjoin(path_env[j], "/");
            join_cmd = ft_strjoin(join_slash, *str);
            free(join_slash);
            if (access(join_cmd, F_OK) == 0)
            {
                if (count >= 1)
                    free(*path);
                *path = ft_strdup(join_cmd);
                count++;
            }
            j++;
            free(join_cmd);
        }*/
    }
    return (count);
}
int check_zero(char *str)
{
    int i;
    int verif;

    i = 0;
    verif = 0;
    while (str[i])
    {
        if (str[i] == '\0')
            verif++;
        i++;
    }
    if (verif == ft_strlen(str))
        return (1);
    return (0);
}
void print_array_of_string(char **env)
{
    int i;

    i = 0;
    if (env[i])
    {
        while (env[i])
            {
                if (!check_zero(env[i]))
                    ft_putendl(env[i]);
                i++;
            }
    }
}