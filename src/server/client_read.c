/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 03:15:21 by alex              #+#    #+#             */
/*   Updated: 2017/11/29 04:17:26 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

/*
**
*/

void	send_dada(t_env *e, int cs, char *buf, int r)
{
	int i;

	printf("read: %d, %s\n",r, buf);
	i = 0;
	while (i < e->maxfd)
	{
		if ((e->fds[i].type == FD_CLIENT) &&
			(i != cs))
		send(i, buf, r, 0);
		i++;
	}
	return;
}

/*
**
*/

void	recv_data(t_env *e, int cs, char *buf, int r)
{
	char data[BUF_SIZE + 1];
	int	buf_size;

	printf("BUF: %s\n", buf);
	ft_bzero(data, BUF_SIZE + 1);
	if (ft_buf_add_data(e->fds[cs].buf_read, buf, r))
	{
		printf("%s\n", "ERROR: too much data");
		return ;
	}
	if (e->fds[cs].buf_read->start_data == e->fds[cs].buf_read->end_data
		|| buf[r - 1] == 10)
	{
		printf("%s\n", "getdata");
		buf_size = ft_buf_get_data(e->fds[cs].buf_read, data,
			e->fds[cs].buf_read->start_data == e->fds[cs].buf_read->end_data);
		// if ()
		// {
		// }
		printf("buf_size: %d\n", buf_size);
		send_dada(e, cs, data, buf_size);
	}
	return;
}

void	client_read(t_env *e, int cs)
{
	int	r;
	char buf[BUF_SIZE + 1];

	ft_bzero(buf, BUF_SIZE + 1);
	r = recv(cs, buf, BUF_SIZE, 0);
	if (r <= 0)
	{
		close(cs);
		clean_fd(&e->fds[cs]);
		printf("client #%d gone away\n", cs);
	}
	else
	{
		recv_data(e, cs, buf, r);
	}
}
