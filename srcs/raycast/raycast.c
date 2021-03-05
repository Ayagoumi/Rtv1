/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagoumi <ayagoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 12:07:03 by ayagoumi          #+#    #+#             */
/*   Updated: 2021/03/05 16:19:53 by ayagoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

t_object	*raycast_object(t_ray r, t_hsno *hsno, t_scene *scene)
{
	t_object	*object;
	t_object	*tmp;
	double		het;

	object = scene->object;
	hsno->hit = calc_intersect(r, object);
	tmp = object->next;
	while (tmp)
	{
		het = calc_intersect(r, tmp);
		if (het >= 0.0001 && (het < hsno->hit || hsno->hit == -1))
		{
			hsno->hit = het;
			object = tmp;
		}
		tmp = tmp->next;
	}
	if (hsno->hit < 0.0001)
		return (NULL);
	calc_surface_normal(r, object, hsno);
	return (object);
}

void		trace(t_rtv1 *rtv, t_hsno *hsno, t_scene *scene, t_pixel pixel)
{
	if (hsno->object)
	{
		if (scene->light)
			rtv->data[(WIDTH * pixel.j) + pixel.i] =\
				ft_get_full_color(hsno, scene, &(hsno->r));
		else
			rtv->data[(WIDTH * pixel.j) + pixel.i] =\
				rgb_to_int(hsno->object->color);
	}
	else
		rtv->data[(WIDTH * pixel.j) + pixel.i] = 0;
}

void		ft_cast_rays(t_rtv1 *rtv, t_scene *scene)
{
	t_pixel	pixel;
	double	u;
	double	v;
	t_hsno	hsno;
	t_point	p;

	declare_camera(&hsno.r, scene, &hsno, &p);
	pixel.i = 0;
	while (pixel.i < WIDTH)
	{
		pixel.j = 0;
		while (pixel.j < HEIGHT)
		{
			u = map(pixel.i, WIDTH, -1, 1) * p.y;
			v = map(pixel.j, HEIGHT, 1, -1) * p.x;
			hsno.r.dir = plus(hsno.wv, plus(mult2(v, hsno.vv),\
				mult2(u, hsno.uv)));
			hsno.r.dir = normalize(hsno.r.dir);
			hsno.object = raycast_object(hsno.r, &hsno, scene);
			trace(rtv, &hsno, scene, pixel);
			pixel.j++;
		}
		pixel.i++;
	}
}
