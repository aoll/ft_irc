/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   who.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 00:23:49 by alex              #+#    #+#             */
/*   Updated: 2017/12/01 01:41:58 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int	buf_send_error(t_buf *buf, const char *err_mess, size_t size)
{
	if (ft_buf_add_data(buf, err_mess, size))
	{
		ft_buf_clean(buf);
		printf("ERROR: buf full\n");
		return (buf_send_error(buf, INTERN_ERROR, ft_strlen(INTERN_ERROR)));
	}
	return (EXIT_SUCCESS);
}


static int	who_add_list(t_env *e, int cs, int index_channel)
{
	int		i;
	int tmp;

	i = 0;
	while (i < e->maxfd)
	{
		tmp = e->channels->l_chanel[index_channel].fds[i];
		if (tmp == 1)
		{
			if (ft_buf_set_data(e->fds[cs].buf_write, e->fds[i].name,
				ft_strlen(e->fds[i].name), BUFFER_FULL))
				return (EXIT_FAILLURE);
			if (ft_buf_set_data(
				e->fds[cs].buf_write, " ", 1, BUFFER_FULL))
				return (EXIT_FAILLURE);
		}
		i++;
	}
	if (ft_buf_set_data(e->fds[cs].buf_write, "\n", 1, BUFFER_FULL))
		return (EXIT_FAILLURE);
	return (EXIT_SUCCESS);
}

int			who(t_env *e, int cs, char *cmd)
{
	int		index_channel;

	if (ft_strcmp(cmd, WHO))
	{
		return (buf_send_error(e->fds[cs].buf_write,
			WHO_NEED_NO_ARGS, ft_strlen(WHO_NEED_NO_ARGS)));
		return (EXIT_FAILLURE);
	}
	index_channel = ft_is_channel_exist(e->channels, e->fds[cs].channel);
	if (index_channel < 0)
	{
		printf("%s\n", WHO_NEED_CHANNEL);
		return (buf_send_error(e->fds[cs].buf_write,
			WHO_NEED_CHANNEL, ft_strlen(WHO_NEED_CHANNEL)));
	}
	return (who_add_list(e, cs, index_channel));
}
