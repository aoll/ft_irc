/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 12:19:15 by alex              #+#    #+#             */
/*   Updated: 2017/12/07 12:47:04 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int			ft_is_channel_exist(t_chanels *cha, const char *name)
{
	int	i;

	i = 0;
	while (i < cha->nb_chanel)
	{
		if (cha->l_chanel[i].fdsize)
		{
			if (ft_strcmp(cha->l_chanel[i].name, name) == 0)
			{
				return (i);
			}
		}
		i++;
	}
	return (-1);
}

int			ft_join_chanel(t_chanels *cha, const char *name, int fd)
{
	int i;

	if ((i = ft_is_channel_exist(cha, name)) == -1)
		return (EXIT_FAILURE);
	cha->l_chanel[i].fds[fd] = 1;
	return (EXIT_SUCCESS);
}

int			ft_leave_chanel(t_chanels *cha, const char *name, int fd)
{
	int i;

	if ((i = ft_is_channel_exist(cha, name)) == -1)
		return (EXIT_FAILURE);
	cha->l_chanel[i].fds[fd] = 0;
	return (EXIT_SUCCESS);
}

int			ft_new_chanel(t_chanels *cha, const char *name, size_t nb_fd)
{
	int	i;

	if (ft_strlen(name) > MAX_LEN_CHANEL_NAME)
		return (EXIT_FAILURE);
	if (cha->nb_chanel_active == cha->nb_chanel)
		return (EXIT_FAILURE);
	if (ft_is_channel_exist(cha, name) != -1)
		return (-1);
	i = -1;
	while (++i < cha->nb_chanel)
		if (!cha->l_chanel[i].fdsize)
		{
			if (!(cha->l_chanel[i].name = ft_strdup(name)))
				return (EXIT_FAILURE);
			if (!(cha->l_chanel[i].fds = malloc(sizeof(int) * nb_fd)))
			{
				free(cha->l_chanel[i].name);
				return (EXIT_FAILURE);
			}
			ft_bzero((void *)cha->l_chanel[i].fds, sizeof(int) * nb_fd);
			cha->l_chanel[i].fdsize = nb_fd;
			cha->nb_chanel_active++;
			return (EXIT_SUCCESS);
		}
	return (EXIT_FAILURE);
}

t_chanels	*ft_chanels_init(size_t nb_chanel)
{
	t_chanels	*cha;

	if (!(cha = malloc(sizeof(*cha))))
		return (NULL);
	cha->nb_chanel_active = 0;
	cha->nb_chanel = nb_chanel;
	if (!(cha->l_chanel = malloc(sizeof(*cha->l_chanel) * nb_chanel)))
	{
		free(cha);
		return (NULL);
	}
	ft_bzero((void *)cha->l_chanel, sizeof(*cha->l_chanel) * nb_chanel);
	return (cha);
}
