/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derey <derey@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 10:01:25 by derey             #+#    #+#             */
/*   Updated: 2024/08/12 15:43:00 by derey            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_exp_dir(t_init *init_shell, char *src)
{
	int		i;
	int		x;
	char	*tmp;

	i = 1;
	x = 0;
	tmp = ft_calloc(ft_strlen(src), sizeof(char));
	while (src[i] != '\0' && src[i] != ' ')
		tmp[x++] = src[i++];
	i = 0;
	while (init_shell->cpy_env[i] != NULL)
	{
		if (ft_find_export(init_shell->cpy_env[i], tmp, '='))
		{
			free(tmp);
			return (1);
		}
		i++;
	}
	free(tmp);
	return (0);
}

int	acces_dirnocd(char *result, t_init *init_shell)
{
	if (access(result, F_OK) == -1)
	{
		ft_putstr_fd(" No such file or directory\n", 2);
		init_shell->exit_code = 1;
		return (0);
	}
	if (access(result, R_OK) == -1)
	{
		ft_putstr_fd(" Permission denied\n", 2);
		init_shell->exit_code = 126;
		return (0);
	}
	return (1);
}

void	ft_dir_nocd(t_init *init_shell, char *src)
{
	if (access(src, F_OK) == -1)
	{
		ft_putstr_fd(" No such file or directory\n", 2);
		init_shell->exit_code = 127;
		return ;
	}
	if (access(src, F_OK | R_OK) != 0)
	{
		ft_putstr_fd(" Permission denied\n", 2);
		init_shell->exit_code = 126;
		return ;
	}
	ft_putstr_fd(" Is a directory\n", 2);
}

void	ft_dir_base(t_init *init_shell, char *src)
{
	if (access(src, F_OK) == -1)
	{
		ft_putstr_fd(" No such file or directory\n", 2);
		init_shell->exit_code = 127;
		return ;
	}
	if (access(src, F_OK | R_OK) != 0)
	{
		ft_putstr_fd(" Permission denied\n", 2);
		init_shell->exit_code = 126;
		return ;
	}
	ft_putstr_fd(" Is a directory\n", 2);
	init_shell->exit_code = 126;
}
