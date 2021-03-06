/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 13:19:41 by rzukale           #+#    #+#             */
/*   Updated: 2021/01/18 13:50:43 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_abs(int x)
{
	return (((x) < 0) ? -(x) : (x));
}
