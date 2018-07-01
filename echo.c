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
void    home(char *str, t_env_tools env)
{
    char my_home[5] = "HOME\0";

    char *var;

    var = env_var(env, my_home, ft_strlen(my_home));
    ft_putstr(var);
    ft_putchar(' ');
}
void print_splited(char **str)
{
    int i;

    i = 1;
    while(str[i])
    {
        ft_putstr(str[i]);
        i++;
    }
    ft_putchar('\n');
}
int count_str(char **str)
{
    int count;
    int i;

    i = 1;
    count = 0;
    while (str[i])
    {
        printf("str: %s\n", str[i]);
        if (ft_strchr(str[i], ' ') == NULL)
            count++;
        count += ft_strlen(str[i]);

        i++;
    }
    return (count);

}
char *quotation_str(char **str)
{
    //char *ret = ft_strnew(count_str(str));

    char *ret;
    char *tmp;

    ret = "";
    int i = 1;
    while (str[i])
    {
        if (ft_strchr(str[i], ' ') != NULL)
        {
            ret = ft_strjoin(ret, " ");
            printf("ceao\n");
        }
       // tmp = ft_strdup(str[i]);
        ret = ft_strjoin(ret, tmp);
        //free(tmp);
        i++;

    }
    return ret;
}
void quotation_split(char *str)
{
    char **split_echo;
    int i;
    int j;
    char *var;


    split_echo = ft_strsplit(str, '"');
    print_splited(split_echo);


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
        if (!ft_strcmp(str[i], "~"))
        {
            home(str[i], env);
        }
        else if (count_expansion(str[i], '$') == 1)
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