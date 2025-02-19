/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derey <derey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:37:06 by maxouvra          #+#    #+#             */
/*   Updated: 2024/08/12 10:40:36 by derey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_init(t_init *init_shell, t_execute *process, char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	init_shell->cpy_env = ft_calloc(sizeof(char *), (i + 1));
	i = 0;
	while (env[i])
	{
		init_shell->cpy_env[i] = ft_strdup(env[i]);
		i++;
	}
	init_shell->pathearly = NULL;
	init_shell->cpy_env[i] = NULL;
	getcwd(init_shell->actual_dir, 128);
	process->n_pipe = 0;
	init_shell->on = 1;
	init_shell->exit_code = 0;
	init_shell->sig.sa_handler = &handle_signal;
	init_shell->ignore.sa_handler = SIG_IGN;
}

void	init_split(t_exp *expa, t_input *line)
{
	int	i;

	i = 0;
	while (line->input[i] != '\0')
	{
		if (line->input[i] == '"')
			expa->dquot++;
		if (line->input[i] == '\'')
			expa->squot++;
		if (line->input[i] == '$')
			expa->expan++;
		i++;
	}
}

void	init_exp(t_exp *expa, t_input *line)
{
	expa->squot = 0;
	expa->expan = 0;
	expa->dquot = 0;
	expa->len = 0;
	expa->idx = 0;
	expa->space = 0;
	expa->pipe = 0;
	expa->x = 0;
	expa->q = 0;
	expa->tmp_exp = NULL;
	expa->word_env = NULL;
	expa->end_str = NULL;
	expa->exp = NULL;
	init_split(expa, line);
}

void	path_early(t_init *init_shell)
{
	char	c[PATH_MAX];
	int		i;
	int		x;

	getcwd(c, sizeof(c));
	i = find_homes(init_shell);
	free(init_shell->pathearly);
	x = (int)ft_strlen(c);
	if (i <= x)
	{
		if (i < x)
			init_shell->pathearly = ft_calloc(x - i + 5, sizeof(char *));
		else
			init_shell->pathearly = ft_calloc(5, sizeof(char *));
		if (init_shell->pathearly == NULL)
			return ;
		x = 0;
		init_shell->pathearly[x++] = '~';
		while (i <= (int)ft_strlen(c) && c[i] != '\0')
			init_shell->pathearly[x++] = c[i++];
		init_shell->pathearly[x++] = '$';
		init_shell->pathearly[x++] = ' ';
	}
	else
		init_shell->pathearly = ft_strjoin(c, "$ ");
}
