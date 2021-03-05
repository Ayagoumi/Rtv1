/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surface_normal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagoumi <ayagoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 16:17:13 by ayagoumi          #+#    #+#             */
/*   Updated: 2021/03/05 16:17:28 by ayagoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

void		calc_surface_normal(t_ray r, t_object *object, t_hsno *hsno)
{
	hsno->h = plus(r.origin, mult2(hsno->hit, r.dir));
	if (object->type == 0)
	{
		if (dot(r.dir, object->orientation) < 0)
			hsno->surface_normal = object->orientation;
		else
			hsno->surface_normal = mult2(-1, object->orientation);
	}
	if (object->type == 1)
		hsno->surface_normal = normalize(minus(hsno->h, object->position));
	calc_surface_normal2(r, object, hsno);
}

void		calc_surface_normal2(t_ray r, t_object *object, t_hsno *hsno)
{
	double	m;
	double	k;

	if (object->type == 2)
	{
		m = dot(r.dir, mult2(hsno->hit, object->orientation))\
			+ dot(minus(r.origin, object->position), object->orientation);
		hsno->surface_normal = normalize(minus(minus(hsno->h,\
						object->position), mult2(m, object->orientation)));
	}
	if (object->type == 3)
	{
		k = tan(object->angle * 180 / M_PI);
		k = 1.0 + k * k;
		m = dot(r.dir, mult2(hsno->hit, object->orientation))\
			+ dot(minus(r.origin, object->position), object->orientation);
		hsno->surface_normal = normalize(minus(minus(hsno->h,\
			object->position), mult2(k, mult2(m, object->orientation))));
	}
}
