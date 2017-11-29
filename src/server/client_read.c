/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 03:15:21 by alex              #+#    #+#             */
/*   Updated: 2017/11/29 09:15:36 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	send_dada(t_env *e, int cs, char *buf, int r)
{
	int i;

	printf("read: %d, %s\n",r, buf);
	i = -1;
	while (++i < e->maxfd)
	{
		if ((e->fds[i].type == FD_CLIENT) &&
			(i != cs))
		{
			if (ft_buf_add_data(
				e->fds[i].buf_write, e->fds[cs].name, ft_strlen(e->fds[cs].name)))
			{
				ft_buf_clean(e->fds[i].buf_write);
				printf("%s\n", "ERROR: too much data");
				return ;
			}
			if (ft_buf_add_data(e->fds[i].buf_write, ": ", 2))
			{
				ft_buf_clean(e->fds[i].buf_write);
				printf("%s\n", "ERROR: too much data");
				return ;
			}
			if (ft_buf_add_data(e->fds[i].buf_write, buf, r))
			{
				ft_buf_clean(e->fds[i].buf_write);
				printf("%s\n", "ERROR: too much data");
				return ;
			}
		}
	}
	return;
}

int	set_name(t_env *e, int cs, char *cmd, int cmdsize)
{
	int	i;
	char	*trim;

	i = -1;
	cmd += ft_strlen(NICKNAME);
	if (!(trim = ft_strtrim(cmd)))
	{
		printf("%s\n", "ERROR: set_name");
		return (EXIT_FAILURE);
	}
	if (ft_strlen(trim) > MAX_LEN_LOGIN_NAME)
	{
		free(trim);
		printf("%s\n", "ERROR: set_name name to long");
		return (EXIT_FAILURE);
	}
	ft_bzero(e->fds[cs].name, MAX_LEN_LOGIN_NAME);
	ft_strcpy(e->fds[cs].name, trim);
	return (EXIT_SUCCESS);

}

/*
** create new channel
*/

int	new_channel(t_env *e, int cs, char *cmd, int cmdsize)
{
	char	**split;
	int		ret;
	char	*trim;

	if (!(split = ft_strsplit(cmd, ' ')))
	{
		printf("%s\n", "ERROR: new_channel: split fail");
		return (EXIT_FAILLURE);
	}
	if (!split[1] || split[2])
	{
		printf("%s\n", "ERROR: new_channel: too much args");
		return (EXIT_FAILURE);
	}
	if (!(trim = ft_strtrim(split[1])))
	{
		printf("%s\n", "ERROR: new_channel: intern error");
		return (EXIT_FAILLURE);
	}
	if ((ret = ft_new_chanel(e->channels, trim, e->maxfd)))
	{
		free(trim);
		if (ret == -1)
		{
			printf("ERROR: join_channel: channel [%s] already exist\n", split[1]);
			return (EXIT_FAILLURE);
		}
		printf("%s\n", "ERROR: new_channel: intern error");
		return (EXIT_FAILLURE);
	}
	free(trim);
	return (EXIT_SUCCESS);
}

int	join_channel(t_env *e, int cs, char *cmd, int cmdsize)
{
	char	**split;
	int		ret;
	char	*trim;

	if (!(split = ft_strsplit(cmd, ' ')))
	{
		printf("%s\n", "ERROR: join_channel: split fail");
		return (EXIT_FAILLURE);
	}
	if (!split[1] || split[2])
	{
		printf("%s\n", "ERROR: join_channel: too much args");
		return (EXIT_FAILURE);
	}
	if (!(trim = ft_strtrim(split[1])))
	{
		printf("%s\n", "ERROR: new_channel: intern error");
		return (EXIT_FAILLURE);
	}
	if ((ret = ft_join_chanel(e->channels, trim, cs)))
	{
		free(trim);
		printf("ERROR: join_channel: channel [%s] not exist\n", split[1]);
		return (EXIT_FAILLURE);
	}
	ft_leave_chanel(e->channels, e->fds[cs].channel, cs);
	ft_bzero(e->fds[cs].channel, MAX_LEN_CHANEL_NAME);
	ft_strcpy(e->fds[cs].channel, trim);
	free(trim);
	return (EXIT_SUCCESS);
}

int	who(t_env *e, int cs, char *cmd, int cmdsize)
{
	char	**split;
	int		index_channel;
	int		i;
	char	*trim;

	if (!(split = ft_strsplit(cmd, ' ')))
	{
		printf("%s\n", "ERROR: who: split fail");
		return (EXIT_FAILLURE);
	}
	if (split[2])
	{
		if (!(trim = ft_strtrim(split[2])))
		{
			printf("%s\n", "ERROR: who: intern error");
			return (EXIT_FAILLURE);
		}
		index_channel = ft_is_channel_exist(e->channels, trim);
		free(trim);
	}
	else
	{
		index_channel = ft_is_channel_exist(e->channels, e->fds[cs].channel);
	}
	printf("INDEX: %d\n", index_channel);
	if (index_channel < 0)
	{
		printf("%s\n", "ERROR: who ");
		return (EXIT_FAILLURE);
	}
	i = 0;
	int tmp;

	while (i < e->maxfd)
	{
		tmp = e->channels->l_chanel[index_channel].fds[i];
		if (tmp == 1)
		{
			if (ft_buf_add_data(e->fds[cs].buf_write, e->fds[i].name, ft_strlen(e->fds[i].name)))
			{
				ft_buf_clean(e->fds[i].buf_write);
				printf("%s\n", "ERROR: too much data");
					return (EXIT_FAILLURE);

			}
			if (ft_buf_add_data(e->fds[cs].buf_write, " ", 1))
			{
				ft_buf_clean(e->fds[cs].buf_write);
				printf("%s\n", "ERROR: too much data");
				return (EXIT_FAILLURE);
			}
		}
		i++;
	}
	if (ft_buf_add_data(e->fds[cs].buf_write, "\n", 1))
	{
		ft_buf_clean(e->fds[cs].buf_write);
		printf("%s\n", "ERROR: too much data");
		return (EXIT_FAILLURE);
	}
	return (EXIT_SUCCESS);
}

int	switch_requete(t_env *e, int cs, char *command, int cmdsize)
{
	char *cmd;

	if (!(cmd = ft_strtrim(command)))
		exit(EXIT_FAILLURE);
	if (!ft_strncmp(cmd, NICKNAME, ft_strlen(NICKNAME)))
	{
		set_name(e, cs, cmd, cmdsize);
	}
	else if (!ft_strncmp(cmd, NEW_CHANNEL, ft_strlen(NEW_CHANNEL)))
	{
		new_channel(e, cs, cmd, cmdsize);
	}
	else if (!ft_strncmp(cmd, JOIN_CHANNEL, ft_strlen(JOIN_CHANNEL)))
	{
		join_channel(e, cs, cmd, cmdsize);
	}
	else if (!ft_strncmp(cmd, WHO, ft_strlen(WHO)))
	{
		who(e, cs, cmd, cmdsize);
	}
	else
	{
		send_dada(e, cs, cmd, cmdsize);
	}
	return (EXIT_SUCCESS);
}

void	recv_data(t_env *e, int cs, char *buf, int r)
{
	char data[BUF_SIZE + 1];
	int	buf_size;

	printf("BUF: %s\n", buf);
	ft_bzero(data, BUF_SIZE + 1);
	if (ft_buf_add_data(e->fds[cs].buf_read, buf, r))
	{
		ft_buf_clean(e->fds[cs].buf_read);
		printf("%s\n", "ERROR: too much data");
		return ;
	}
	if (e->fds[cs].buf_read->start_data == e->fds[cs].buf_read->end_data
		|| buf[r - 1] == 10)
	{
		buf_size = ft_buf_get_data(e->fds[cs].buf_read, data);
		if (data[buf_size - 1] != 10)
		{
			ft_buf_clean(e->fds[cs].buf_read);
			printf("%s\n", "ERROR: too much data");
			return ;
		}
		printf("buf_size: %d\n", buf_size);
		switch_requete(e, cs, data, buf_size);
		// send_dada(e, cs, data, buf_size);
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
