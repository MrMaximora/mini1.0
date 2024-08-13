/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derey <derey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 08:40:49 by derey             #+#    #+#             */
/*   Updated: 2024/08/13 14:57:25 by derey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *heredoc_name(void)
{
	static int	i = 0;
	char		*nb;
	char		*name;

	nb = ft_itoa(i);
	name = ft_strjoin("obj/.heredoc_", nb);
	free(nb);
	i++;
	return (name);
}

char	*del_quote(char *str)
{
	int	i;
	int	x;
	char	*tmp;

	i = 0;
	x = 0;
	tmp = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	while (str[i] != '\0')
	{
		if (str[i] != '\'' && str[i] != '"')
		{
			tmp[x] = str[i];
			x++;
		}
		i++;
	}
	free(str);
	str = ft_strdup(tmp);
	free(tmp);
	return (str);
}

int	parse_heredoc(int qt, char *str, t_init *init_shell)
{
	int	fd;
	char	*line;

	fd = open(init_shell->heredoc_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	line = readline("> ");
	while (line)
	{
		if (qt == 0)
			line = hd_expand(line, init_shell);
		if (ft_strnstr(line, str, ft_strlen(str)))
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline("> ");
	}
	free(line);
	close(fd);
	return (0);
}

int	heredoc(t_lexer_tab *current, t_init *init_shell)
{
	int	qt;
	int	i;
	char	*str;

	i = 0;
	qt = 0;
	str = ft_strdup(current->next->arg);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			qt = 1;
		i++;
	}
	str = del_quote(str);
	if (parse_heredoc(qt, str, init_shell) == 1)
		return (1);
	free(str);
	return (0);
}