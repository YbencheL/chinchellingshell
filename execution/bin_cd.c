/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenzaho <abenzaho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:24:08 by abenzaho          #+#    #+#             */
/*   Updated: 2025/04/29 15:03:37 by abenzaho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_file_name_len(char *s)
{
	int	i;
	int	c;

	i = 0;
	while (s[i])
	{
		if (s[i] == '/')
		{
			i++;
			c = 0;
			while (s[i] && s[i] != '/')
			{
				c++;
				i++;
			}
			if (c > 255)
				return (1);
		}
		i++;
	}
	return (0);
}

void	cd(t_cmds *cmds)
{
	char	*path;
	char	*last_path;
	// int		i;
	// error hundle of the main program
	if (!cmds->cmds[1])
	{
		path = getenv("HOME");
		if (!path)
		{
			write(2, "minishell cd: HOME not set\n", 26);
			//exit(1);
		}
		chdir(path);
		//exit(0);
	}
	else if (cmds->cmds[2])
	{
		write(2, "minishell cd: too many arguments", 32);
		//exit (1);
	}
	else if (ft_strncmp(cmds->cmds[1], "-", ft_strlen(cmds->cmds[1])) == 0)
	{
		last_path = getenv("OLDPWD");
		if (!last_path)
		{
			write(2, "minishell cd: OLDPWD not set\n", 26);
			//exit(1);
		}
		printf("%s\n", last_path);
		chdir(last_path);
		//exit (1);
	}
	else if (ft_strlen(cmds->cmds[1]) > 4094)
	{
		write(2, "minishell cd: Pathname too long", 31);
		//exit (1);
	}
	else if (check_file_name_len(cmds->cmds[1]))
	{
		write(2, "minishell cd: File name too long", 31);
		//exit (1);
	}
	else
	{
		if (!chdir(cmds->cmds[1]))
		{
			cmds->cmds[1] = NULL;
			//return exit number
		}
		else
		{
			perror("minishell cd : ");
			//exit (1);
		}
	}
}
