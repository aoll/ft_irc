/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_client.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 13:23:45 by alex              #+#    #+#             */
/*   Updated: 2017/12/04 14:50:40 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int	init_fd_client(fd_set *fd_read, fd_set *fd_write, int sock, int stdin)
{
	FD_ZERO(fd_read);
	FD_ZERO(fd_write);
	FD_SET(sock, fd_read);
	FD_SET(stdin, fd_read);
	// FD_SET(sock, fd_write);
	return (EXIT_SUCCESS);
}

int	read_sock(int fd, int sock_ref, fd_set *fd_write)
{
	int	r;
	char buf[BUF_SIZE + 1];

	ft_bzero(buf, BUF_SIZE + 1);
	r = read(fd, buf, BUF_SIZE);
	if (r <= 0)
	{
		close(fd);
		exit (EXIT_SUCCESS);
	}
	if (fd == sock_ref)
		printf("%s", buf);
	else
	{
		if (send(sock_ref, buf, r, 0) == -1)
			exit(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	check_fd_client(fd_set *fd_read, fd_set *fd_write, int sock, int stdin)
{
	if (FD_ISSET(sock, fd_read))
	{
		read_sock(sock, sock, fd_write);
	}
	if (FD_ISSET(stdin, fd_read))
		read_sock(stdin, sock, fd_write);
	return (EXIT_SUCCESS);
}

int	listen_client(int sock, int stdin)
{
	fd_set		fd_read;
	fd_set		fd_write;
	int			r;

	while (42)
	{
		init_fd_client(&fd_read, &fd_write, sock, stdin);
		r = select(sock + 1, &fd_read, &fd_write, NULL, NULL);
		if (!r)
			continue ;
		check_fd_client(&fd_read, &fd_write, sock, stdin);
	}
}

int	start_client(char *addr, char *port)
{
	int		sock;
	char	*trim_addr;
	char	*trim_port;

	if (!(trim_addr = ft_strtrim(addr)))
		exit (EXIT_FAILURE);
	if (!(trim_port = ft_strtrim(port)))
	{
		free(trim_addr);
		exit (EXIT_FAILURE);
	}
	if (!(sock = create_client(trim_addr, trim_port)))
		return (EXIT_FAILURE);
	free(trim_addr);
	free(trim_port);
	listen_client(sock, STDIN);
	return (EXIT_SUCCESS);
}
