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

void	tst_ft_strlen(void)
{
	if (ft_strlen("") == 0)
		write(1, "0\n", 2);
	else
		write(1, "1\n", 2);
	if (ft_strlen(NULL) == 0)
		write(1, "0\n", 2);
	else
		write(1, "1\n", 2);
	if (ft_strlen("Hello world!") == 12)
		write(1, "12\n", 3);
	else
		write(1, "1\n", 2);
}
