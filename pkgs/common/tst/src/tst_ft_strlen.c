/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tst_ft_strlen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 15:12:12 by retanaka          #+#    #+#             */
/*   Updated: 2024/09/01 15:12:13 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tst_common.h"

void	tst_ft_strlen(char *s, size_t len)
{
	if (ft_strlen(s) == len)
		write(1, "OK\n", 3);
	else
		write(1, "KO!\n", 4);
}
