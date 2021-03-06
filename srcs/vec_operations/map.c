/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagoumi <ayagoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 12:50:50 by ayagoumi          #+#    #+#             */
/*   Updated: 2021/03/06 12:51:11 by ayagoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

double	map(int position, int max_wh,
			double new_min_scope, double new_max_scope)
{
	double range;

	range = new_max_scope - new_min_scope;
	return (new_min_scope + position * (range / max_wh));
}
