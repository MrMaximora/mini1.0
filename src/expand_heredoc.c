/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derey <derey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:05:48 by derey             #+#    #+#             */
/*   Updated: 2024/08/13 14:06:48 by derey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	text_e(t_exp *expa, t_init *init_shell, char *str, int a)
{
	char	*tmp;
	int		st;

	tmp = NULL;
	st = 0;
	if (a == 0 && str[expa->idx + 1] == '?')
	{
		expa->exp = ft_itoa(init_shell->exit_code);
		st = ft_strexit(str);
	}
	else
		expa->exp = ft_expcpy(init_shell->cpy_env[a],
				'=', ft_strlen_exp(init_shell->cpy_env[a], '=') + 1);
	tmp = ft_joinlen(expa->end_str, expa->exp, ft_strlenback(str) + st);
	if (tmp == NULL)
		return ;
	free(expa->end_str);
	expa->end_str = tmp;
	if (a == 0 && str[expa->idx + 1] == '?')
	{
		expa->idx = expa->idx + 2;
		expa->len = expa->len + ft_strlen(expa->exp);
	}
	free(expa->exp);
}

void	loop_e(t_exp *expa, t_init *init_shell, char *str, int a)
{
	int	i;

	i = 0;
	if (init_shell->cpy_env[a] == NULL || expa->word_env == NULL )
		return ;
	while (init_shell->cpy_env[a][i] == expa->word_env[i]
		&& expa->word_env[i] != '\0')
	{
		if (init_shell->cpy_env[a][i + 1] == '='
			&& (expa->word_env[i + 1] == '\0' || expa->word_env[i + 1] == '$'))
		{
			text_e(expa, init_shell, str, a);
			expa->len = expa->len
				+ ft_strlen_exp(init_shell->cpy_env[a], '=');
			break ;
		}
		i++;
	}
}

void	word_expa(t_exp *expa, char *str)
{
	int	i;
	int	a;

	a = 0;
	i = expa->idx;
	while (str[i] != '\0' && end_word(str[i]) == 0)
	{
		i++;
		a++;
	}
	expa->word_env = ft_calloc(a + 2, sizeof(char));
	if (expa->word_env == NULL)
		return ;
	expa->idx++;
	i = 0;
	while (str[expa->idx] != '\0' && end_word(str[expa->idx]) == 0 && str[expa->idx] != '$')
	{
		expa->word_env[i] = str[expa->idx];
		i++;
		expa->idx++;
	}
}

void	write_hd(t_exp *expa, char *str, t_init *init_shell)
{
	int	a;

	while (str[expa->idx] != '\0' && str[expa->idx] == '$')
	{
		if (str[expa->idx] == '$' && str[expa->idx + 1] == '\0')
			return ;
		if (str[expa->idx] == '$' && str[expa->idx + 1] == '?')
			text_e(expa, init_shell, str, 0);
		else
			word_expa(expa, str);
		a = 0;
		while (init_shell->cpy_env[a] != NULL)
			loop_e(expa, init_shell, str, a++);
		free(expa->word_env);
	}
}

char	*hd_expand(char *str, t_init *init_shell)
{
	t_exp	*expa;

	expa = ft_calloc(1, sizeof(t_exp));
	expa->expan = 0;
	expa->len = 0;
	expa->idx = 0;
	expa->word_env = NULL;
	expa->end_str = NULL;
	expa->exp = NULL;
	expa->end_str = ft_calloc(ft_strlen(str) + 2, sizeof(char));
	while (str[expa->idx] != '\0')
	{
		if (str[expa->idx] == '$' && end_word(str[expa->idx + 1]) == 0)
			write_hd(expa, str, init_shell);
		if (str[expa->idx] == '\0')
			break ;
		expa->end_str[expa->len++] = str[expa->idx];
		expa->idx++;
	}
	free(str);
	str = ft_strdup(expa->end_str);
	free(expa->end_str);
	free(expa);
	return (str);
}