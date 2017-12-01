/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_channel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 00:58:46 by alex              #+#    #+#             */
/*   Updated: 2017/12/01 01:05:56 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static int	ret_err(const char *err_mess)
{
	printf("%s\n", err_mess);
	return (EXIT_FAILLURE);
}

/*
** create new channel
*/

int			new_channel(t_env *e, int cs, char *cmd)
{
	char	**split;
	int		ret;
	char	*trim;

	if (!(split = ft_strsplit(cmd, ' ')))
		return (ret_err("ERROR: new_channel: split fail"));
	if (!split[1] || split[2])
		return (ret_err("ERROR: new_channel: too much args"));
	if (!(trim = ft_strtrim(split[1])))
		return (ret_err("ERROR: new_channel: intern error"));
	if ((ret = ft_new_chanel(e->channels, trim, e->maxfd)))
	{
		free(trim);
		if (ret == -1)
		{
			printf("ERROR: /join: channel [%s] already exist\n", split[1]);
			return (EXIT_FAILLURE);
		}
		return (ret_err("ERROR: new_channel: intern error"));
	}
	free(trim);
	return (EXIT_SUCCESS);
}
