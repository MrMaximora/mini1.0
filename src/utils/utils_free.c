/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derey <derey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 09:19:16 by derey             #+#    #+#             */
/*   Updated: 2024/08/13 10:48:33 by derey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_next_line(t_lexer_tab *lexer_tab, t_input *line)
{
	t_lexer_tab	*current;
	t_lexer_tab	*tmp;

	current = lexer_tab;
	while (current)
	{
		tmp = current;
		current = current->next;
		free(tmp);
	}
	ft_free(line->all_tokens);
	line->all_tokens = NULL;
	free(line->input);
	line->input = NULL;
}

void	ft_free(char **all_tokens)
{
	int	i;

	i = 0;
	if (!all_tokens)
		return ;
	if (!all_tokens[i])
	{
		free(all_tokens);
		all_tokens = NULL;
		return ;
	}
	while (all_tokens[i])
	{
		free(all_tokens[i]);
		all_tokens[i] = NULL;
		i++;
	}
	free(all_tokens);
	all_tokens = NULL;
}

void	all_unlink(char *str)
{
	char	nb;
	int		i;
	char	*tmp;
	char	*t;

	i = ft_strlen(str);
	nb = str[i - 1];
	i = ft_atoi(&nb);
	tmp = NULL;
	while (i >= 0)
	{
		if (tmp)
			free(tmp);
		t = ft_itoa(i);
		tmp = ft_strjoin("obj/.heredoc_", t);
		unlink(tmp);
		i--;
		free(t);
	}
	if (tmp)
		free(tmp);
}
