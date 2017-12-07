/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 05:07:02 by alex              #+#    #+#             */
/*   Updated: 2017/12/07 14:20:02 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# define PROMPT	"ft_p> "

# define INTERN_ERROR				"Intern error\n"
# include "ft_p.h"

int			new_connection(int sock, char *buf);
int			start_client(char *addr, char *port);
int			create_client(char *addr, char *port);
int			read_sock_stdin(int fd, char *buf);
int			read_sock_sock(int fd);
void		replace_char(char *s, int to_replace, int replace_with);

#endif
