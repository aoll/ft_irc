/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 14:17:21 by aollivie          #+#    #+#             */
/*   Updated: 2017/12/07 14:19:53 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	replace_char(char *s, int to_replace, int replace_with)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == to_replace)
			s[i] = replace_with;
		i++;
	}
	return ;
}
