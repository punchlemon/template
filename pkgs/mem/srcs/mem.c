/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 13:42:58 by retanaka          #+#    #+#             */
/*   Updated: 2024/09/05 20:32:30 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"
#include "slice.h"

t_slice	*create_node_slice(uint64_t len)
{
	t_slice	*s;

	s = malloc(sizeof(t_slice));
	if (!s)
		return (NULL);
	s->l = len;
	s->c = 1;
	update_cap(s->l, &s->c);
	s->p = malloc(sizeof(t_node *) * s->c);
	if (!s->p)
		return (free(s), NULL);
	return (s);
}
