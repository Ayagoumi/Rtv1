/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagoumi <ayagoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 12:07:03 by ayagoumi          #+#    #+#             */
/*   Updated: 2021/03/04 15:41:43 by ayagoumi         ###   ########.fr       */
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

int			ft_get_full_color(t_hsno *hsno, t_light *light\
				, t_scene *scene, t_ray *ray)
{
	int		color;
	int		sh;
	double	intensity;
	t_vec3	f_color;

	hsno->light = light;
	f_color = get_ambiant(hsno);
	while (hsno->light)
	{
		intensity = map(hsno->light->intensity, 100, 0, 1);
		hsno->difcoef = ft_get_diffuse(hsno, hsno->light) * intensity;
		hsno->specoef = ft_get_specular(hsno, hsno->light) * intensity;
		sh = shadow(ray, hsno, hsno->light, scene->object);
		f_color = ft_color(hsno, light->color, sh, f_color);
		hsno->light = hsno->light->next;
	}
	color = rgb_to_int(f_color);
	return (color);
}

void		declare_camera(t_ray *r, t_scene *scene, t_hsno *hsno, t_point *p)
{
	r->origin.x = scene->camera->pos.x;
	r->origin.y = scene->camera->pos.y;
	r->origin.z = scene->camera->pos.z + 0.0005;
	hsno->wv = normalize(minus(scene->camera->dir, scene->camera->pos));
	hsno->uv = normalize(cross((t_vec3){0.005, 1, 0}, hsno->wv));
	hsno->vv = cross(hsno->wv, hsno->uv);
	p->x = tanf((scene->camera->zoom * M_PI / 180.0) / 2);
	p->y = (double)(WIDTH / HEIGHT) * p->x;
}

void		ft_cast_rays(t_rtv1 *rtv, t_scene *scene)
{
	int i;
	int j;
	t_ray r;
	double u;
	double v;
	t_hsno hsno;
	t_point p;

	declare_camera(&r, scene, &hsno, &p);
	i = 0;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
		{
			u = map(i, WIDTH, -1, 1) * p.y;
			v = map(j, HEIGHT, 1, -1) * p.x;
			r.dir = plus(hsno.wv, plus(mult2(v, hsno.vv), mult2(u, hsno.uv)));
			r.dir = normalize(r.dir);
			hsno.object = raycast_object(r, &hsno, scene);
			if (hsno.object)
			{
				if (scene->light)
					rtv->data[(WIDTH * j) + i] = ft_get_full_color(&hsno, scene->light, scene, &r);
				else
					rtv->data[(WIDTH * j) + i] = rgb_to_int(hsno.object->color);
			}
			else
				rtv->data[(WIDTH * j) + i] = 0;
			j++;
		}
		i++;
	}
}
