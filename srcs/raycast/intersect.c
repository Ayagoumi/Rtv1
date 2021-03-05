/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagoumi <ayagoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 16:07:36 by ayagoumi          #+#    #+#             */
/*   Updated: 2021/03/05 16:07:57 by ayagoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

double		intersect_sphere(t_ray r, t_object *sphere)
{
	t_intersect		inter;

	inter.a = dot(r.dir, r.dir);
	inter.x = minus(r.origin, sphere->position);
	inter.b = 2 * dot(r.dir, inter.x);
	inter.c = dot(inter.x, inter.x) - (sphere->raduis * sphere->raduis);
	inter.delta = inter.b * inter.b - (4 * inter.a * inter.c);
	if (inter.delta < 0)
		return (-1);
	inter.t1 = (-inter.b - sqrt(inter.delta)) / (2 * inter.a);
	inter.t2 = (-inter.b + sqrt(inter.delta)) / (2 * inter.a);
	if ((inter.t1 <= inter.t2 && inter.t1 >= 0.0) ||\
			(inter.t1 >= 0.0 && inter.t2 < 0.0))
		return (inter.t1);
	if ((inter.t2 <= inter.t1 && inter.t2 >= 0.0) ||\
			(inter.t2 >= 0.0 && inter.t1 < 0.0))
		return (inter.t2);
	return (-1);
}

double		intersect_plane(t_ray r, t_object *plane)
{
	t_intersect		inter;

	inter.x = minus(r.origin, plane->position);
	inter.a = dot(r.dir, plane->orientation);
	inter.b = dot(inter.x, plane->orientation);
	if (inter.a == 0 || (inter.a > 0 && inter.b > 0) ||\
			(inter.a < 0 && inter.b < 0))
		return (-1);
	inter.t1 = -inter.b / inter.a;
	if (inter.t1 < 0)
		return (-1);
	return (inter.t1);
}

double		intersect_cylinder(t_ray r, t_object *cyl)
{
	t_intersect		inter;

	inter.a = dot(r.dir, r.dir) - (dot(r.dir, cyl->orientation) *\
			dot(r.dir, cyl->orientation));
	inter.x = minus(r.origin, cyl->position);
	inter.b = 2 * (dot(r.dir, inter.x) - (dot(r.dir, cyl->orientation) *\
				dot(inter.x, cyl->orientation)));
	inter.c = dot(inter.x, inter.x) - (dot(inter.x, cyl->orientation) *\
			dot(inter.x, cyl->orientation)) - (cyl->raduis * cyl->raduis);
	inter.delta = inter.b * inter.b - (4 * inter.a * inter.c);
	if (inter.delta < 0)
		return (-1);
	inter.t1 = (-inter.b - sqrt(inter.delta)) / (2 * inter.a);
	inter.t2 = (-inter.b + sqrt(inter.delta)) / (2 * inter.a);
	if ((inter.t1 <= inter.t2 && inter.t1 >= 0.0) ||\
			(inter.t1 >= 0.0 && inter.t2 < 0.0))
		return (inter.t1);
	if ((inter.t2 <= inter.t1 && inter.t2 >= 0.0) ||\
			(inter.t2 >= 0.0 && inter.t1 < 0.0))
		return (inter.t2);
	return (-1);
}

double		intersect_cone(t_ray r, t_object *cone)
{
	t_intersect		inter;

	inter.k = tan(cone->angle * 180.0 / M_PI);
	inter.k = 1.0 + inter.k * inter.k;
	inter.a = dot(r.dir, r.dir) - inter.k * (dot(r.dir, cone->orientation)\
		* dot(r.dir, cone->orientation));
	inter.x = minus(r.origin, cone->position);
	inter.b = 2 * (dot(r.dir, inter.x) - inter.k \
		* (dot(r.dir, cone->orientation) * dot(inter.x, cone->orientation)));
	inter.c = dot(inter.x, inter.x) - inter.k \
		* (dot(inter.x, cone->orientation) * dot(inter.x, cone->orientation));
	inter.delta = inter.b * inter.b - (4 * inter.a * inter.c);
	if (inter.delta < 0)
		return (-1);
	inter.t1 = (-inter.b - sqrt(inter.delta)) / (2 * inter.a);
	inter.t2 = (-inter.b + sqrt(inter.delta)) / (2 * inter.a);
	if ((inter.t1 <= inter.t2 && inter.t1 >= 0.0) ||\
			(inter.t1 >= 0.0 && inter.t2 < 0.0))
		return (inter.t1);
	if ((inter.t2 <= inter.t1 && inter.t2 >= 0.0) ||\
			(inter.t2 >= 0.0 && inter.t1 < 0.0))
		return (inter.t2);
	return (-1);
}

double		calc_intersect(t_ray r, t_object *object)
{
	if (object->type == 0)
		return (intersect_plane(r, object));
	if (object->type == 1)
		return (intersect_sphere(r, object));
	if (object->type == 2)
		return (intersect_cylinder(r, object));
	else
		return (intersect_cone(r, object));
	return (0.0);
}
