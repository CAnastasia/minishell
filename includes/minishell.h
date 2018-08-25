/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   minishell.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: canastas <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/17 20:07:17 by canastas     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/19 14:30:02 by canastas    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include "../libft/includes/libft.h"

typedef struct		s_env_tools
{
	char			**env_cpy;
	char			**paths;
	char			**tmp_env;
	char			**str_input;
	char			*inp;
}					t_env_tools;

int					g_sig_check;
char				*env_var(t_env_tools env, char *str, int size);
void				path_str(char **envs, char ***path);
int					size_str(char **environ);
char				**copy_env(char **environ, int size);
void				free_str(char **str);
void				free_str_2(char **str, int size);
int					check_path(char **env, char **path, char **str);
void				check_echo(char **str, t_env_tools env, char *inp);
int					count_char(char *str, char c);
void				quotation_split(char *str, t_env_tools env);
char				*dollar_expention(char *str, t_env_tools env);
void				echo_tools(char **str, t_env_tools env);
char				**mi_strsplit(char const *s, char c, char d);
char				*mi_strchr(const char *s, int c, int d);
void				env_var_setenv(t_env_tools *env, char *str, int size,
					char **inp);
char				**copy_var_env(char **environ, int size, char **inp);
void				print_array_of_string(char **env);
void				error_exec_or_exec(char **paths, char *path, char **str,
					char **env);
void				env_exec(char **str, t_env_tools *env, char *path);
char				**copy_env(char **environ, int size);
void				modify_env(char ***env_tab, char *str, char **inp,
					int index_size[2]);
char				**copy_var_env_cmd(char **environ, int size, char **inp,
					int j);
int					size_env_add(char **inp);
void				unset(char ***env_tab, char *str, int size);
void				cmds(char **str, t_env_tools *env, char *path,
					char *inp_cmd);
void				cd_function(char **str, t_env_tools *env);
char				*dol_var_ret(char *str, t_env_tools env, int j);
int					count_expansion(char *str, char c);
char				**quot_mark_split(char *inp);
char				**search_for_var(char **str, t_env_tools env);
void				home(t_env_tools env);
void				dollar_in_quote(t_env_tools env, int *i, char *inp,
					char **tmp);
void				split_dollar_exp(char *str, t_env_tools env);
void				change_pwd(t_env_tools *env, char *cwd);
void				sighandler(int signum);
void				error_command(char **str);
void				print_error(char **str);
void				free_path_cd(char *hm, char *val_path);

#endif
