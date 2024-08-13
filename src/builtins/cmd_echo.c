/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derey <derey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 09:08:22 by derey             #+#    #+#             */
/*   Updated: 2024/08/12 13:05:15 by derey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	echo_n(char *str)
{
	int	i;

	i = 1;
	while (str[i] == 'n')
		i++;
	if (str[i] == '\0' && str[i - 1] == 'n')
		return (1);
	else
		return (0);
}

static int	print_redir(t_input *line, int i)
{
	int	a;
	int	result;

	a = 0;
	result = i;
	while (line->input[a] != '\0')
	{
		if ((line->input[a] == '"' || line->input[a] == '\''))
		{
			if (line->input[a + 1] == '>' || line->input[a + 1] == '<' || line->input[a + 1] == '.')
				break ;
		}
		a++;
	}
	return (result);
}

static void	print_echo(t_input *line, int i, int fd, int n)
{
	int	q;

	q = 0;
	if (n == 1)
		i++;
	while (line->all_tokens[i] != NULL && line->all_tokens[i][0] != '|')
	{
		if (line->all_tokens[i][0] == '-' && echo_n(line->all_tokens[i]) == 1
			&& q == 0)
		{
			i++;
			continue ;
		}
		if (line->all_tokens[i][0] == '>' || line->all_tokens[i][0] == '<' || line->all_tokens[i][0] == '.')
		{
			i = print_redir(line, i);
		}
		else if (line->all_tokens[i][0] == '|')
			return ;
		else
			ft_putstr_fd(line->all_tokens[i], fd);
		if (line->all_tokens[i + 1] != NULL
			&& line->all_tokens[i + 1][0] != '|' 
			&& line->all_tokens[i + 1][0] != '<' 
			&& line->all_tokens[i + 1][0] != '>'  
			&& line->all_tokens[i][0] != '<' 
			&& line->all_tokens[i][0] != '>')
			ft_putstr_fd(" ", fd);
		q++;
		i++;
	}
}

void	cmd_echo(t_input *line, int i, int fd, t_init *init_shell)
{
	if (line->all_tokens[i] == NULL)
		ft_putstr_fd("\n", fd);
	else if (ft_strnstr(line->all_tokens[i], "-n", 2)
		&& echo_n(line->all_tokens[i]) == 1)
		print_echo(line, i, fd, 1);
	else
	{
		print_echo(line, i, fd, 0);
		ft_putstr_fd("\n", fd);
	}
	init_shell->exit_code = 0;
}
