/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_buffer_circulaire.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 12:50:49 by aollivie          #+#    #+#             */
/*   Updated: 2017/12/07 12:51:46 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int		ft_buf_set_data(
	t_buf *buf, const char *data, size_t size, char *err_mess)
{
	if (ft_buf_add_data(buf, data, size))
	{
		ft_buf_clean(buf);
		printf("%s\n", err_mess);
		buf_send_error(buf, INTERN_ERROR, ft_strlen(INTERN_ERROR));
		return (EXIT_FAILLURE);
	}
	return (EXIT_SUCCESS);
}

void	ft_buf_clean(t_buf *buf_e)
{
	buf_e->size = 0;
	buf_e->start_data = buf_e->start_buf;
	buf_e->end_data = buf_e->start_buf;
	return ;
}
