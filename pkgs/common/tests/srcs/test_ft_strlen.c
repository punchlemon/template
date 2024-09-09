/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_strlen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 15:12:12 by retanaka          #+#    #+#             */
/*   Updated: 2024/09/09 22:19:04 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_common.h"

void	test_ft_strlen(void)
{
	if (ft_strlen("") == 0)
		put("0\n");
	else
		put("1\n");
	if (ft_strlen(NULL) == 0)
		put("0\n");
	else
		put("1\n");
	if (ft_strlen("Hello world!") == 12)
		put("12\n");
	else
		put("1\n");
}
