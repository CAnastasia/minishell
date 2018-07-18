/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cd.c                                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: canastas <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/17 19:11:45 by canastas     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/17 19:21:01 by canastas    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*check_env_var(char **str, t_env_tools env)
{
	char	*path_cd;
	char	*res;

	res = NULL;
	path_cd = ft_strsub(str[1], 1, ft_strlen(str[1]));
	if ((res = env_var(env, path_cd, ft_strlen(path_cd))) == NULL)
		res = ft_strdup(str[1]);
	free(path_cd);
	return (res);
}

char	*path_cd_val(char **str, t_env_tools env)
{
	char	*path_cd;
	char	*res;

	res = NULL;
	path_cd = NULL;
	if (str[1][0] == '$')
		res = check_env_var(str, env);
	else if (str[1][0] == '\"' && count_char(str[1], '\"') % 2 == 0)
	{
		if (str[1][1] == '$')
		{
			path_cd = ft_strsub(str[1], 2, ft_strlen(str[1]) - 3);
			if ((res = env_var(env, path_cd, ft_strlen(path_cd))) == NULL)
				res = ft_strdup(str[1]);
			free(path_cd);
		}
		else
			res = ft_strsub(str[1], 1, ft_strlen(str[1]) - 2);
	}
	else if (count_char(str[1], '\"') % 2 != 0)
		res = ft_strdup("\n");
	else
		res = ft_strdup(str[1]);
	return (res);
}

void	old_path(t_env_tools *env, char cwd[256], char *var)
{
	char	*res_pwd;
	int		cd_ret;

	cd_ret = 0;
	if ((res_pwd = env_var(*env, var, ft_strlen(var))) == NULL)
	{
		ft_putstr_fd("cd : ", 2);
		ft_putstr_fd(var, 2);
		ft_putendl_fd(" not set.", 2);
	}
	else
	{
		if ((cd_ret = chdir(res_pwd)) == 0)
		{
			change_pwd(env, cwd);
			free(res_pwd);
		}
		else
			ft_putendl_fd("cd: Permission denied or file do not exists.", 2);
	}
}

void	print_error(char **str)
{
	ft_putstr_fd(str[1], 2);
	ft_putstr_fd(" : ", 2);
	ft_putendl_fd("No such file or directory.", 2);
}

void	cd_function(char **str, t_env_tools *env)
{
	int		cd_ret;
	char	cwd[256];
	char	*val_path;

	cd_ret = 0;
	val_path = NULL;
	if (size_str(str) == 2)
		val_path = path_cd_val(str, *env);
	if (size_str(str) > 2 && !ft_strchr(str[1], '\"'))
		ft_putendl_fd("cd: Too many arguments.", 2);
	else
	{
		getcwd(cwd, sizeof(cwd));
		if (str[1] && !ft_strcmp(str[1], "-"))
			old_path(env, cwd, "OLDPWD");
		else if ((str[1] && !ft_strcmp(str[1], "~")) || size_str(str) == 1)
			old_path(env, cwd, "HOME");
		else if (str[1] && (cd_ret = chdir(val_path)) == 0)
			change_pwd(env, cwd);
		else
			print_error(str);
	}
	if (val_path != NULL)
		free(val_path);
}
