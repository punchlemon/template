/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slice.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 13:42:58 by retanaka          #+#    #+#             */
/*   Updated: 2024/08/23 13:42:59 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slice.h"

int	update_cap(uint64_t len, uint64_t *cap)
{
	if (!cap)
		return (-1);
	if (*cap >= len)
		return (0);
	if (*cap == 0)
		*cap = 1;
	while (1)
	{
		if (*cap >= len)
			return (1);
		if (*cap < 1024)
			*cap *= 2;
		else
			*cap *= 1.25;
	}
}

t_slice	*create_byte_slice(uint64_t len)
{
	t_slice	*s;

	s = malloc(sizeof(t_slice));
	if (!s)
		return (NULL);
	s->l = len;
	s->c = 1;
	update_cap(s->l, &s->c);
	s->p = malloc(s->c);
	if (!s->p)
		return (free(s), NULL);
	return (s);
}

void	delete_byte_slice(t_slice *s)
{
	if (!s)
		return ;
	if (s->p)
		free(s->p);
	return (free(s));
}
