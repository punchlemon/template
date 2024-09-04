/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tst_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 16:19:09 by retanaka          #+#    #+#             */
/*   Updated: 2024/09/01 16:19:09 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tst_mini_printf.h"

int	main(void)
{
	tst_put_d();
	tst_put_u();
	tst_put_ld();
	tst_put_lu();
	tst_put();
	tst_put_char();
	tst_print_count();
	tst_put_arg();
	tst_mini_printf();
	return (0);
}
