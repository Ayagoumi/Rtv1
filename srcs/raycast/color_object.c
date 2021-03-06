/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagoumi <ayagoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 16:10:10 by ayagoumi          #+#    #+#             */
/*   Updated: 2021/03/06 10:56:58 by ayagoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

int			shadow(t_ray *r, t_hsno *hsno, t_light *l, t_object *objects)
{
	t_ray		shadow_ray;
	double		dis_light;
	double		hit;
	t_vec3		old_hit;
	t_object	*tmp;

	shadow_ray.origin = l->pos;
	shadow_ray.dir = hsno->l_dir;
	old_hit = plus(r->origin, mult2(hsno->hit, r->dir));
	dis_light = sqrt(dot(minus(l->pos, old_hit), minus(l->pos, old_hit)));
	tmp = objects;
	while (tmp)
	{
		if (tmp != hsno->object)
		{
			hit = calc_intersect(shadow_ray, tmp);
			if (hit >= 0.0001 && (dis_light > hit && dis_light - hit > 0.0001))
				return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

int			rgb_to_int(t_vec3 rgb)
{
	int		color;

	color = ((int)(rgb.x) << 16 | (int)(rgb.y) << 8 | (int)(rgb.z));
	return (color);
}

t_vec3		ft_color(t_hsno *hsno, t_vec3 l_color, int sh, t_vec3 f_color)
{
	f_color.x += (int)(hsno->object->color.x * hsno->difcoef\
			+ l_color.x * hsno->specoef) * sh;
	if (f_color.x > 255)
		f_color.x = 255;
	f_color.y += (int)(hsno->object->color.y * hsno->difcoef\
			+ l_color.y * hsno->specoef) * sh;
	if (f_color.y > 255)
		f_color.y = 255;
	f_color.z += (int)(hsno->object->color.z * hsno->difcoef\
			+ l_color.z * hsno->specoef) * sh;
	if (f_color.z > 255)
		f_color.z = 255;
	return (f_color);
}

int			ft_get_full_color(t_hsno *hsno\
		, t_scene *scene, t_ray *ray)
{
	int		color;
	int		sh;
	double	intensity;
	t_vec3	f_color;

	hsno->light = scene->light;
	f_color = get_ambiant(hsno);
	while (hsno->light)
	{
		intensity = map(hsno->light->intensity, 100, 0, 1);
		hsno->difcoef = ft_get_diffuse(hsno, hsno->light) * intensity;
		hsno->specoef = ft_get_specular(hsno, hsno->light) * intensity;
		sh = shadow(ray, hsno, hsno->light, scene->object);
		f_color = ft_color(hsno, scene->light->color, sh, f_color);
		hsno->light = hsno->light->next;
	}
	color = rgb_to_int(f_color);
	return (color);
}
