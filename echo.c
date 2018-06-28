#include "includes/minishell.h"


char    *env_var(t_env_tools env, char *str)
{
    int i;
    char *ret_var;
    i = 0;
    while(env.env_cpy[i])
    {
        if (!ft_strncmp(env.env_cpy[i], str,(int)(ft_strchr(env.env_cpy[i],'=') - env.env_cpy[i])))
        {
            ret_var = ft_strsub(ft_strchr(env.env_cpy[i],'='), 1, ft_strlen(ft_strchr(env.env_cpy[i],'='))  - 1 );
        }
        i++;
    }
    return (ret_var);
}

int count_expension(char *str)
{
    int i;

    i = 0;
    while (str[i] == '$')
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
        printf("%s\n", str[i]);
        if (count_expension(str[i]) == 1)
        {
            split_echo = ft_strsplit(str[i], '$');
            while (split_echo[j])
            {
                if (ft_strcmp(split_echo[j],"$"))
                {
                    var = env_var(env, split_echo[j]);
                    ft_putstr(var);
                    ft_putchar('\n');
                }
                j++;
            }
        }
        else
        {
            ft_putstr(NULL);
        }
        i++;
    }
}