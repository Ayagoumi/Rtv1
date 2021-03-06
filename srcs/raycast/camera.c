/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagoumi <ayagoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 16:15:18 by ayagoumi          #+#    #+#             */
/*   Updated: 2021/03/05 19:10:54 by ayagoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

void		declare_camera(t_ray *r, t_scene *scene, t_hsno *hsno, t_point *p)
{
	r->origin.x = scene->camera->pos.x;
	r->origin.y = scene->camera->pos.y;
	r->origin.z = scene->camera->pos.z + 0.00005;
	hsno->wv = normalize(minus(scene->camera->dir, scene->camera->pos));
	hsno->uv = normalize(cross((t_vec3){0.005, 1, 0}, hsno->wv));
	hsno->vv = cross(hsno->wv, hsno->uv);
	p->x = tanf((scene->camera->zoom * M_PI / 180.0) / 2);
	p->y = (double)(WIDTH / HEIGHT) * p->x;
}
