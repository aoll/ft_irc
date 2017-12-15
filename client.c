/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 12:54:52 by alex              #+#    #+#             */
/*   Updated: 2017/12/09 17:12:46 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static void	usage(const char *name)
{
	printf("Usage %s <machine> <port> || [machine [port]]\n", name);
	exit(EXIT_SUCCESS);
}

int			main(int ac, char **av)
{
	if (ac > 3)
		usage(av[0]);
	if (ac == 1)
		return (listen_client(-1, STDIN));
	if (av[2])
		return (start_client(av[1], av[2]));
	else
		return (new_connection(0, av[1]));
	return (EXIT_SUCCESS);
}
