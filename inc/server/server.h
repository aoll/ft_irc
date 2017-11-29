/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 13:34:01 by aollivie          #+#    #+#             */
/*   Updated: 2017/11/29 08:37:40 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

#include <sys/types.h>
#include <sys/wait.h>
#include "ft_p.h"
#include "ft_irc.h"

# define GUEST					"guest"
# define NB_MAX_CHANNEL			42
# define MAX_LEN_CHANEL_NAME	9
# define MAX_LEN_LOGIN_NAME 	9

# define JOIN_CHANNEL			"/join"
# define NEW_CHANNEL			"/newchannel"
# define LEAVE_CHANNEL			"/leave"
# define NICKNAME				"/nick"
# define WHO					"/who"

typedef struct	s_buf
{
	size_t		size;
	char		*start_buf;
	char		*end_buf;
	char		*start_data;
	char		*end_data;
}	t_buf;

typedef struct	s_fd
{
	int			type;
	void		(*fct_read)();
	void		(*fct_write)();
	char		name[MAX_LEN_LOGIN_NAME];
	t_buf		*buf_write;
	t_buf		*buf_read;
	char		buf_read1[BUF_SIZE + 1];
	char		buf_write1[BUF_SIZE + 1];
	char		channel[MAX_LEN_CHANEL_NAME];
}	t_fd;

typedef struct	s_chanel
{
	char			*name;
	int				*fds;
	int				fdsize;
}	t_chanel;

typedef struct	s_chanels
{
	int			nb_chanel;
	int			nb_chanel_active;
	t_chanel	*l_chanel;
}	t_chanels;

typedef struct	s_env
{
	t_fd		*fds;
	t_chanels	*channels;
	int			port;
	int			maxfd;
	int			max;
	int			r;
	fd_set		fd_read;
	fd_set		fd_write;

}	t_env;

//ft_irc
int			start_server(int port);
int			create_server(int port, int nb_conn);

//env
int			init_env(t_env *e, int port);
void		clean_fd(t_fd *fd);
void		client_read(t_env *e, int cs);
void		client_write(t_env *e, int cs);

//buffer_circulaire
t_buf		*ft_buf_new(size_t size);
int			ft_buf_get_data(t_buf *buf_e, char *dest);
int			ft_buf_add_data(t_buf *buf_e, const char *s, size_t size);
void		ft_buf_clean(t_buf *buf_e);

//chanel
t_chanels	*ft_chanels_init(size_t nb_chanel);
int			ft_new_chanel(t_chanels *cha, const char *name, size_t nb_fd);
int			ft_join_chanel(t_chanels *cha, const char *name, int fd);
int			ft_leave_chanel(t_chanels *cha, const char *name, int fd);
int			ft_is_channel_exist(t_chanels *cha, const char *name);

//ft_p
int			fork_process_cmd(int fd, char **arg);
int			cd_requet(t_cs *cs, char **requet);
int			verify_dest(t_cs *cs, char *dest);
int			verify_multi_dest(t_cs *cs, char **requet);
int			new_process(int fd);
int			free_cs(t_cs *cs);
int			init_cs(t_cs *cs, int fd);
int			cmd_requet(t_cs *cs, char **requet);
int			quit_requet(t_cs *cs);
int			pwd_requet(t_cs *cs, char **requet);
int			put_requet(t_cs *cs, char **requet, char *requet_s);
int			get_requet_server(t_cs *cs, char **requet);

#endif
