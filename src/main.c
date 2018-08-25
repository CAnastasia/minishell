/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: canastas <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/17 19:23:29 by canastas     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/18 19:22:12 by canastas    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*input(void)
{
	char	*str;
	char	*ret_str;

	ret_str = NULL;
	ft_putstr("$>");
	if ((get_next_line(0, &str)))
	{
		ret_str = ft_strdup(str);
		free(str);
	}
	return (ret_str);
}

void	initialitation(char **inp_cmd, char ***str, t_env_tools *env)
{
	env->inp = input();
	if (env->inp == NULL)
		exit(1);
	*inp_cmd = ft_strsub(mi_strchr(env->inp, ' ', '\t'), 1,
			ft_strlen(env->inp) - 1);
	*str = quot_mark_split(env->inp);
	env->str_input = search_for_var(*str, *env);
}

void	exec_instructions(t_env_tools *env, char *inp_cmd)
{
	char	*path;

	path = NULL;
	if (*env->str_input == NULL)
		;
	else if (ft_strcmp(*env->str_input, "exit") == 0 || env->inp == NULL)
	{
		if (env->str_input != NULL)
			free_str(env->str_input);
		ft_putstr("exit\n");
		exit(1);
	}
	else
		cmds(env->str_input, env, path, inp_cmd);
}

void	instructions_loop(char **str, char *inp_cmd, t_env_tools env)
{
	int	size;

	size = 0;
	while (1)
	{
		initialitation(&inp_cmd, &str, &env);
		if (str != NULL)
		{
			size = size_str(str);
			free_str(str);
		}
		if (env.str_input)
			exec_instructions(&env, inp_cmd);
		if (env.str_input != NULL)
			free_str_2(env.str_input, size);
		if (env.inp != NULL)
			free(env.inp);
		if (inp_cmd != NULL)
			free(inp_cmd);
	}
}

int		main(int argc, char **argv, char **environ)
{
	char		**str;
	t_env_tools	env;
	char		*inp_cmd;

	(void)argc;
	(void)argv;
	env.paths = NULL;
	g_sig_check = 0;
	inp_cmd = NULL;
	str = NULL;
	signal(SIGINT, sighandler);
	env.env_cpy = copy_env(environ, size_str(environ));
	instructions_loop(str, inp_cmd, env);
	if (env.env_cpy != NULL)
		free_str(env.env_cpy);
	if (env.inp != NULL)
		free(env.inp);
	return (0);
}
