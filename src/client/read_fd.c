/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 12:00:36 by aollivie          #+#    #+#             */
/*   Updated: 2017/12/07 12:01:02 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int	read_sock_stdin(int fd, char *buf)
{
	int r;

	r = read(fd, buf, BUF_SIZE);
	if (r <= 0)
	{
		close(fd);
		exit(EXIT_SUCCESS);
	}
	if (!ft_strncmp(buf, "/connect", 8))
	{
		return (2);
	}
	return (EXIT_SUCCESS);
}

int	read_sock_sock(int fd)
{
	int		r;
	char	buf[BUF_SIZE + 1];

	ft_bzero(buf, BUF_SIZE + 1);
	r = read(fd, buf, BUF_SIZE);
	if (r <= 0)
	{
		close(fd);
		exit(EXIT_SUCCESS);
	}
	printf("%s", buf);
	return (EXIT_SUCCESS);
}
