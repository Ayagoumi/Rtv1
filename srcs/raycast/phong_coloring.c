/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_coloring.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagoumi <ayagoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 16:19:11 by ayagoumi          #+#    #+#             */
/*   Updated: 2021/03/05 16:19:33 by ayagoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

t_vec3		get_ambiant(t_hsno *hsno)
{
	t_vec3	f_color;

	hsno->ambcoef = 0.1;
	hsno->specoef = 0;
	hsno->difcoef = 0;
	f_color.x = hsno->object->color.x * hsno->ambcoef;
	if (f_color.x > 255)
		f_color.x = 255;
	f_color.y = hsno->object->color.y * hsno->ambcoef;
	if (f_color.y > 255)
		f_color.y = 255;
	f_color.z = hsno->object->color.z * hsno->ambcoef;
	if (f_color.z > 255)
		f_color.z = 255;
	return (f_color);
}

double		ft_get_diffuse(t_hsno *hsno, t_light *light)
{
	t_vec3	ldir;
	double	diffuse_coef;

	ldir = normalize(minus(light->pos, hsno->h));
	diffuse_coef = dot(ldir, hsno->surface_normal);
	if (diffuse_coef < 0)
		diffuse_coef = 0;
	return (diffuse_coef);
}

double		ft_get_specular(t_hsno *hsno, t_light *light)
{
	t_vec3	ldir;
	double	specular_coef;
	t_vec3	reflect;

	hsno->l_dir = normalize(minus(hsno->h, light->pos));
	ldir = hsno->l_dir;
	reflect = normalize(minus(mult2(2.0 * dot(hsno->surface_normal, ldir),\
					hsno->surface_normal), ldir));
	specular_coef = powf(fabs(dot(hsno->surface_normal, reflect) > 0 ? 0 :\
				dot(hsno->surface_normal, reflect)), 120);
	return (specular_coef);
}
