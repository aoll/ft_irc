/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_client.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 13:23:45 by alex              #+#    #+#             */
/*   Updated: 2017/12/09 17:39:43 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static int	init_fd_client(
	fd_set *fd_read, fd_set *fd_write, int sock, int stdin)
{
	FD_ZERO(fd_read);
	FD_ZERO(fd_write);
	if (sock > 0)
	{
		FD_SET(sock, fd_read);
		FD_SET(sock, fd_write);
	}
	FD_SET(stdin, fd_read);
	return (EXIT_SUCCESS);
}

static int	write_sock(int sock, char *buf, size_t size)
{
	if (send(sock, buf, size, 0) == -1)
		exit(EXIT_FAILURE);
	ft_bzero(buf, BUF_SIZE + 1);
	return (EXIT_SUCCESS);
}

int			new_connection(int sock, char *buf)
{
	char	addr[BUF_SIZE];
	char	port[BUF_SIZE];
	char	**split;
	char	*trim;

	printf("%s\n", "hello new connection");
	replace_char(buf, '\t', ' ');
	replace_char(buf, ':', ' ');
	if (!(trim = ft_strtrim(buf)))
		return (listen_client(sock, STDIN));
	if (*trim == '"' || *trim == '\'')
		*trim = ' ';
	if (trim[ft_strlen(trim) - 1] == '"' || trim[ft_strlen(trim) - 1] == '\'')
		trim[ft_strlen(trim) - 1] = ' ';
	if (!(split = ft_strsplit(trim, ' ')))
		return (listen_client(sock, STDIN));
	if (!split[0] || !split[1])
		return (listen_client(sock, STDIN));
	ft_strcpy(addr, split[0]);
	ft_strcpy(port, split[1]);
	if (sock > 0)
	{
		close(sock);
	}
	ft_array_free(&split);
	printf("%s\n", "before start client");
	return (start_client(addr, port));
}

int			listen_client(int sock, int stdin)
{
	fd_set		fd_read;
	fd_set		fd_write;
	int			r;
	char		buf[BUF_SIZE + 1];

	// printf("sock : %d\n", sock);
	while (42)
	{
		ft_bzero(buf, BUF_SIZE + 1);
		init_fd_client(&fd_read, &fd_write, sock, stdin);
		// if (sock > 0 && ft_strlen(buf))
		// 	FD_SET(sock, &fd_write);
		r = select(sock > 0 ? sock + 1 : 2,
			&fd_read, &fd_write, NULL, NULL);
		if (!r)
			continue ;
		if (FD_ISSET(stdin, &fd_read))
			if (read_sock_stdin(stdin, buf) == 2)
				return (new_connection(sock, buf + 8));
		if (sock <= 0)
			continue ;
		// printf("buf :%s\n", buf);
		if (FD_ISSET(sock, &fd_read))
				read_sock_sock(sock);
		if (FD_ISSET(sock, &fd_write) && ft_strlen(buf))
			write_sock(sock, buf, ft_strlen(buf));
	}
}

int			start_client(char *addr, char *port)
{
	int		sock;
	char	*trim_addr;
	char	*trim_port;

	if (!(trim_addr = ft_strtrim(addr)))
		exit(EXIT_FAILURE);
	if (!(trim_port = ft_strtrim(port)))
	{
		free(trim_addr);
		exit(EXIT_FAILURE);
	}
	if ((sock = create_client(trim_addr, trim_port)) <= 0)
		return (EXIT_FAILURE);
	free(trim_addr);
	free(trim_port);
	listen_client(sock, STDIN);
	return (EXIT_SUCCESS);
}
