/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_split_p3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derey <derey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 09:45:09 by derey             #+#    #+#             */
/*   Updated: 2024/08/12 09:46:05 by derey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	sub_split(char const *s, t_exp *expa, t_input *line, int i)
{
	if (expa->pipe == 0 || s[expa->pipe - 1] == ' ')
		expa->len = expa->pipe + 1;
	else
	{
		expa->len = expa->pipe;
		line->all_tokens[expa->x] = ft_substr_exp(s, i, expa->len);
		i = expa->len;
		expa->x++;
		expa->len++;
	}
	line->all_tokens[expa->x] = ft_substr_exp(s, i, expa->len);
	expa->pipe = -1;
}

int	sub_slit(char const *s, t_exp *expa, t_input *line, int i)
{
	if (expa->q == 1)
	{
		expa->len = expa->space;
		line->all_tokens[expa->x] = ft_substr_exp(s, i, expa->len);
		expa->space = -1;
	}
	else if (expa->q == 2)
	{
		expa->len = expa->dquot + 1;
		line->all_tokens[expa->x] = ft_substr_exp(s, i, expa->len);
		expa->dquot = -1;
	}
	else if (expa->q == 3)
	{
		expa->len = expa->squot + 1;
		line->all_tokens[expa->x] = ft_substr_exp(s, i, expa->len);
		expa->squot = -1;
	}
	else if (expa->q == 4)
		sub_split(s, expa, line, i);
	expa->x++;
	return (expa->len);
}
