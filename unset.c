#include "includes/minishell.h"

void unset(char ***env_tab, char *str, int size, char **inp)
{
        int i;
        char *ret_var;
        int size_env;

        i = 0;
        size_env = 0;
    	while(i < size_str(*env_tab))
    	{
    		size_env = (int)(ft_strchr(env_tab[0][i],'=') - env_tab[0][i]);
    		if (!ft_strncmp(env_tab[0][i], str, size_env) && size == size_env)
    		{
    			ft_bzero(env_tab[0][i], ft_strlen(env_tab[0][i]));
    	    	return ;
    		}
    		i++;
    	}
}