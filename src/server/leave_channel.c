/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leave_channel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 02:47:05 by alex              #+#    #+#             */
/*   Updated: 2017/12/07 13:20:24 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int	leave_channel(t_env *e, int cs, char *cmd)
{
	char *trim;

	if (!(trim = ft_strtrim(cmd)))
	{
		buf_send_error(e->fds[cs].buf_write,
			"ERROR: error intern\n", ft_strlen("ERROR: error intern\n"));
		return (EXIT_FAILLURE);
	}
	if (ft_strcmp(LEAVE_CHANNEL, trim))
	{
		free(trim);
		buf_send_error(e->fds[cs].buf_write,
			LEAVE_CHANNEL_NO_ARGS, ft_strlen(LEAVE_CHANNEL_NO_ARGS));
		return (EXIT_FAILLURE);
	}
	free(trim);
	ft_leave_chanel(e->channels, e->fds[cs].channel, cs);
	ft_bzero(e->fds[cs].channel, MAX_LEN_CHANEL_NAME);
	return (EXIT_SUCCESS);
}
