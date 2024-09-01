/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tst_slice.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 19:12:32 by retanaka          #+#    #+#             */
/*   Updated: 2024/08/28 19:12:34 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tst_slice.h"

void	tst_create_byte_slice(void)
{
	t_slice	*s;

	s = create_byte_slice(42);
	if (!s)
		return ;
	if (s->l == 42)
		put("OK");
	else
		put("KO!");
}
