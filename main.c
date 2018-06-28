#include "includes/minishell.h"

char **input()
{
    char *str;
    char **ret_str;
    ft_putstr("$>");
    if (get_next_line(0, &str))
    {
        ret_str = ft_strsplit(str, ' ');
        free(str);
    }
    return(ret_str);
}
int exec(char *path, char**str, t_env_tools env)

{
    pid_t pid;
    if ((pid = fork()))
    {
        if (pid == -1)
        {
            printf("error pid");
            return (-1);
        }
        waitpid(pid, NULL, 0);
    }
    else
    {
        execve(path, str,  env.env_cpy);
        free(path);
        exit(EXIT_FAILURE);
    }
    return(0);
}
int main(int argc, char **argv, char  **environ)
{
    char **str;
    t_env_tools env;
    char *path;
    int n;

    n = size_str(environ);
    env.env_cpy = copy_env(environ, n);
    path_str(&env);
    while (1)
    {
        str = input();
        if (ft_strcmp(*str, "exit") == 0)
        {
            free(*str);
            ft_putstr("exit\n");
            break;
        }
        if (ft_strcmp(*str, "echo") == 0)
        {
            check_echo(str, env);
        }
        /*  if (check_path(env, &path, str) == 0)
          {
              ft_putstr_fd("minishell : command not found : ", 2);
              ft_putstr_fd(*str,2);
              ft_putchar('\n');
              free(path);
          }
          else
          {
             exec(path, str, env);
          }*/
        free_str(str);
    }
    free_str(env.env_cpy);
    free_str(env.paths);
    return (0);
}