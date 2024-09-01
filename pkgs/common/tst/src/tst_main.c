/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tst_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 15:36:21 by retanaka          #+#    #+#             */
/*   Updated: 2024/09/01 15:36:23 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tst_common.h"

int	main(void)
{
	tst_ft_strlen("", 0);
	tst_ft_strlen(NULL, 0);
	tst_ft_strlen("Hello world!", 12);
}
