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
			ret_var = ft_strsub(ft_strchr(env.env_cpy[i],'='), 1, ft_strlen(ft_strchr(env.env_cpy[i],'='))  - 1);
			check_var = 1;
		}
		i++;
	}
	if (check_var == 0)
		ret_var = NULL;
	return (ret_var);
}

int count_expansion(char *str, char c)
{
	int i;
	char *str_chr;

	i = 0;
	if ((str_chr = ft_strchr(str, c)) == NULL)
		return 0;
	while (str_chr[i] == c)
	{
		i++;
	}
	return (i);
}
void    home(t_env_tools env)
{
	char my_home[5] = "HOME\0";

	char *var;

	var = env_var(env, my_home, ft_strlen(my_home));
	ft_putstr(var);
	ft_putchar(' ');
}

int count_str(char **str)
{
	int count;
	int i;

	i = 1;
	count = 0;
	while (str[i])
	{
		if (ft_strchr(str[i], ' ') == NULL)
			count++;
		count += ft_strlen(str[i]);

		i++;
	}
	return (count);

}

void 	split_dollar_exp(char *str, t_env_tools env)
{
	int j;
	char **split_echo;
	char *var;

	j = 0;
	split_echo = ft_strsplit(str, '$');
	while (split_echo[j])
	{
		if (ft_strcmp(split_echo[j], "$"))
		{
			var = env_var(env, split_echo[j], ft_strlen(split_echo[j]));
			ft_putstr(var);
			free(var);
		}
		j++;
	}
	ft_putchar(' ');
	if (split_echo != NULL)
		free_str(split_echo);
}
char *dol_var_ret(char *str, t_env_tools env,  int j)
{
	char *var;
	int size;
	char *tmp;

	size  = 0;
	tmp = str;
	if ((str[j] == '$' && count_expansion(str, '$') == 1))
	{
		if (str[j] == '$' && str[j + 1] == '\0')
			ft_putchar('$');
		size = ft_strlen(ft_strchr(str, '$'));
		tmp = ft_strsub(ft_strchr(str, '$'), 1 , size);
		var = env_var(env, tmp, ft_strlen(tmp));
		free(tmp);
		ft_putstr(var);
		return var;
	}
	else
		return (NULL);
}
char *dollar_expention(char *str, t_env_tools env)
{
	int j;
	char *split_echo;
	char *var;

	j = 0;
	var = NULL;
	split_echo =  ft_strsub(str, 0, ft_strlen(str) - ft_strlen(ft_strchr(str,'$')));
	ft_putstr(split_echo);
	free(split_echo);
	if (count_char(str, '$') > 1)
		split_dollar_exp(str, env);
	else
	{
		while (str[j])
		{
			if (!(var = dol_var_ret(str, env ,j)))
				j++;
			else
				return var;
		}
	}
	return NULL;
}

void echo_tools(char **str, t_env_tools env)
{
	int i;
	char *var;

	i = 1;
	while (str[i])
	{
		if (!ft_strcmp(str[i], "~"))
			home(env);
		else if (count_expansion(str[i], '$') == 1)
		{
			var = dollar_expention(str[i], env);
			if (var != NULL)
			{
				ft_putchar(' ');
				free(var);
			}
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
int  var_env(int i, char *str)
{
	int count;

	count = 0;
	while ((str[i] != '\0' && str[i] != ' ' && str[i] != '\t' && str[i] != '\"' && str[i] != '\'') && i< ft_strlen(str))
	{
		i++;
		count++;
	}
	return (count);
}

char  *var_env_char(int j, char *str)
{
	int i;
	char *ret;

	i = 0;
	ret =  ft_strnew(var_env(j, str));
	while ((str[j] != '\0' && str[j] != ' ' && str[j] != '\t' && str[j] != '\"' && str[j] != '\'') && j< ft_strlen(str))
	{
		ret[i] = str[j];
		j++;
		i++;
	}
	return (ret);
}
void  dollar_in_quote(t_env_tools env, int *i, char *inp, char **tmp)
{
	char *var;

	var = var_env_char(*i, inp);
	*tmp = dollar_expention(var, env);
	if(*tmp != NULL)
        ft_putchar(' ');
	free(var);
	free(*tmp);
	*i += var_env(*i, inp);
}
void out_of_quote(char *inp, t_env_tools env, int *i, char *tmp)
{
	if (inp[*i] == ' ' || inp[*i] == '\t')
	{
		if (inp[*i + 1] > 32 && inp[*i+1] != '\0')
		{
			if(tmp != NULL)
				write(1, " ", 1);
		}
	}
	else if ((inp[*i] == '$' && count_expansion(inp, '$') == 1))
		dollar_in_quote(env, i, inp, &tmp);
	else if (inp[*i] == '~')
		home(env);
	else if (inp[*i] != ' ' && inp[*i] != '\t')
	{
		tmp = inp;
		write(1, &inp[*i], 1);
	}
}

void    between_quote(int *i, char *inp, t_env_tools env, char *tmp)
{
	(*i)++;
	while((inp[*i] != '\"' && inp[*i] != '\'') && inp[*i] != '\0')
	{
		if ( (inp[*i] == '$' && count_expansion(inp, '$') == 1))
			dollar_in_quote(env, i, inp, &tmp);
		else
		{
			tmp = inp;
			ft_putchar(inp[*i]);
			(*i)++;
		}
	}
}
void check_echo(char **str, t_env_tools env, char *inp)
{
	int i;
	char *tmp;

	i = 0;
	if (inp == NULL)
		ft_putchar('\n');
	else if ((count_char(inp,'\"') % 2 == 0 && ft_strchr(inp, '\"') != NULL) ||
			(count_char(inp,'\'') % 2 == 0 && ft_strchr(inp, '\'') != NULL))
	{
		while (inp[i] == ' ' || inp[i] == '\t')
			i++;
		while (inp[i])
		{
			if (inp[i] != '\"' && inp[i] != '\'')
				out_of_quote(inp, env, &i, tmp);
			else
				between_quote(&i, inp, env, tmp);
			i++;
		}
	ft_putchar('\n');
	}
	else if (ft_strchr(inp, '\"') == NULL && ft_strchr(inp, '\'') == NULL)
		echo_tools(str, env);
}
