/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cd_tools.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: canastas <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/17 19:21:09 by canastas     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/17 19:23:05 by canastas    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		search_position(t_env_tools env, char *str, int size)
{
	int	i;
	int	ret_var;
	int	size_env;

	i = 0;
	ret_var = -1;
	while (env.env_cpy[i])
	{
		size_env = (int)(ft_strchr(env.env_cpy[i], '=') - env.env_cpy[i]);
		if (!ft_strncmp(env.env_cpy[i], str, size_env) && size == size_env)
		{
			ret_var = i;
		}
		i++;
	}
	return (ret_var);
}

void	change_pwd(t_env_tools *env, char *cwd)
{
	int		index_pwd;
	int		index_oldpwd;
	char	new_cwd[256];

	index_oldpwd = search_position(*env, "OLDPWD", 6);
	if (index_oldpwd != -1)
	{
		free(env->env_cpy[index_oldpwd]);
		env->env_cpy[index_oldpwd] = ft_strjoin("OLDPWD=", cwd);
	}
	getcwd(new_cwd, sizeof(new_cwd));
	index_pwd = search_position(*env, "PWD", 3);
	if (index_pwd != -1)
	{
		free(env->env_cpy[index_pwd]);
		env->env_cpy[index_pwd] = ft_strjoin("PWD=", new_cwd);
	}
}
