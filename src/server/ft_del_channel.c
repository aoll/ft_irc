/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_channel.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 12:46:49 by aollivie          #+#    #+#             */
/*   Updated: 2017/12/07 12:47:07 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int			ft_del_chanel(t_chanels *cha, const char *name)
{
	int	i;

	i = 0;
	while (i < cha->nb_chanel)
	{
		if (cha->l_chanel[i].fdsize &&
			!ft_strcmp(cha->l_chanel[i].name, name))
		{
			free(cha->l_chanel[i].name);
			free(cha->l_chanel[i].fds);
			ft_bzero(&cha->l_chanel[i], sizeof(cha->l_chanel[i]));
			cha->nb_chanel_active--;
			return (EXIT_SUCCESS);
		}
		i++;
	}
	return (EXIT_FAILURE);
}
