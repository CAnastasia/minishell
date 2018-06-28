#include "includes/minishell.h"
void  path_str(t_env_tools *env)
{
    int i;
    char *str;

    i = 0;
    while(env->env_cpy[i])
    {
        if(ft_strncmp(env->env_cpy[i], "PATH=", 5) == 0)
        {
            str = ft_strnew(ft_strlen(env->env_cpy[i]) - 5);
            int j;
            int k;

            j = 5;
            k = 0;
            while (j < ft_strlen(env->env_cpy[i]))
            {
                str[k] = env->env_cpy[i][j];
                k++;
                j++;
            }
        }
        i++;
    }
    env->paths = ft_strsplit(str, ':');
    free(str);
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
        ft_strdel(&str[i]);
        i++;
    }
    free(str);
}

int check_path(t_env_tools env, char **path, char **str)
{
    int j;
    int res;
    char *join_slash;
    char *join_cmd;

    j = 0;
    res = 0;
    while(env.paths[j])
    {
        join_slash = ft_strjoin(env.paths[j], "/");
        join_cmd = ft_strjoin(join_slash, *str);
        free(join_slash);
        if (access(join_cmd, F_OK) == 0)
        {
            *path = ft_strdup(join_cmd);
            free(join_cmd);
            res = 1;
        }
        j++;
    }
    return (res);
}