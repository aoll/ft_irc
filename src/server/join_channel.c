/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_channel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 00:50:42 by alex              #+#    #+#             */
/*   Updated: 2017/12/01 01:14:15 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static int	ret_err(const char *err_mess)
{
	printf("%s\n", err_mess);
	return (EXIT_FAILLURE);
}

int	join_channel(t_env *e, int cs, char *cmd, int cmdsize)
{
	int		ret;
	char	*trim;

	if (!(trim = ft_strtrim(cmd + ft_strlen(JOIN_CHANNEL))))
		return (ret_err("ERROR: new_channel: intern error"));
	if ((ret = ft_join_chanel(e->channels, trim, cs)))
	{
		printf("ERROR: join_channel: channel [%s] not exist\n", trim);
		free(trim);
		return (EXIT_FAILLURE);
	}
	ft_leave_chanel(e->channels, e->fds[cs].channel, cs);
	ft_bzero(e->fds[cs].channel, MAX_LEN_CHANEL_NAME);
	ft_strcpy(e->fds[cs].channel, trim);
	free(trim);
	return (EXIT_SUCCESS);
}
