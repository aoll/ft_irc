/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_name.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 01:06:37 by alex              #+#    #+#             */
/*   Updated: 2017/12/01 01:06:59 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int	set_name(t_env *e, int cs, char *cmd, int cmdsize)
{
	int	i;
	char	*trim;

	i = -1;
	cmd += ft_strlen(NICKNAME);
	if (!(trim = ft_strtrim(cmd)))
	{
		printf("%s\n", "ERROR: set_name");
		return (EXIT_FAILURE);
	}
	if (ft_strlen(trim) > MAX_LEN_LOGIN_NAME)
	{
		free(trim);
		printf("%s\n", "ERROR: set_name name to long");
		return (EXIT_FAILURE);
	}
	ft_bzero(e->fds[cs].name, MAX_LEN_LOGIN_NAME);
	ft_strcpy(e->fds[cs].name, trim);
	return (EXIT_SUCCESS);
}
