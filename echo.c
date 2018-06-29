#include "includes/minishell.h"


char    *env_var(t_env_tools env, char *str, int size)
{
    int i;
    char *ret_var;
    int check_var;
    int size_env;
    
    i = 0;
    check_var = 0;
    
    
    while(env.env_cpy[i])
    {
        size_env = (int)(ft_strchr(env.env_cpy[i],'=') - env.env_cpy[i]);
        if (!ft_strncmp(env.env_cpy[i], str, size_env) && size == size_env)
        {
            ret_var = ft_strsub(ft_strchr(env.env_cpy[i],'='), 1, ft_strlen(ft_strchr(env.env_cpy[i],'='))  - 1 );
            check_var = 1;
        }
        i++;
    }
    if (check_var == 0)
        ret_var = NULL;
    return (ret_var);
}

int count_expansion(char *str,char c)
{
    int i;
    
    i = 0;
    while (str[i] == c)
    {
        i++;
    }
    return (i);
}

void check_echo(char **str, t_env_tools env)
{
    int i;
    int j;
    char **split_echo;
    char *var;
    i = 1;
    j = 0;
    while (str[i])
    {
        if (count_expansion(str[i], '$') == 1)
        {
            split_echo = ft_strsplit(str[i], '$');
            while (split_echo[j])
            {
                if (ft_strcmp(split_echo[j], "$")) {
                    var = env_var(env, split_echo[j], ft_strlen(split_echo[j]));
                    ft_putstr(var);
                    ft_putchar(' ');
                }
                j++;
            }
            j = 0;
        }
        else
        {
            ft_putstr(str[i]);
            ft_putchar(' ');
        }
        i++;
    }
    ft_putchar('\n');
}
