/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagoumi <ayagoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:04:59 by ayagoumi          #+#    #+#             */
/*   Updated: 2021/02/18 17:56:01 by ayagoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

double	map(int position, int max_wh, double new_min_scope
		, double new_max_scope)
{
	double range;

	range = new_max_scope - new_min_scope;
	return (new_min_scope + position * (range / max_wh));
}

void setup_scene(t_ray *r, t_sphere *sphere)
{
	r->origin.x = 0;
	r->origin.y = 0;
	r->origin.z = -1;

	sphere->pos.x = 0;
	sphere->pos.y = 0;
	sphere->pos.z = 0;
	sphere->r = 0.5;
	sphere->color = 16711680;
}

double  intersect(t_ray *r, t_sphere *s)
{
    double A, B, C, discr;
    t_vec3 destenation;
    double t1, t2;

    A = dot(r->dir, r->dir);
    destenation = minus(r->origin, s->pos);
    B = 2 * dot(r->dir, destenation);
    C = dot(destenation, destenation) - (s->r * s->r);
    discr = B * B - (4 * A * C);
    if (discr < 0)
        return (-1);
    else
    {
        t1 = (-B - sqrt(discr)) / (2 * A);
        t2 = (-B + sqrt(discr)) / (2 * A);
        if (t1 > 0)
            return (t1);
        else
            return (t2);
    }
}

double	get_color(t_ray *r, double hit, t_sphere *sphere)
{
	t_vec3	h;
	t_vec3	n;
	double	diffuse_coef;

	h = plus(r->origin, mult2(hit,r->dir));
	n = normalize(minus(h, sphere->pos));
	diffuse_coef = dot(minus((t_vec3){0,0,0},r->dir), n);
	return (diffuse_coef);
}

void cast_rays(t_rtv1 *rtv)
{
	int i;
	int j;
	t_sphere sphere;
	t_ray r;
	double u, v;
	double hit;
	double	bsbs;
	t_vec3 color;

	setup_scene(&r, &sphere);
	i = 0;
	while (i < WIDTH) 
	{
		j = 0;
		while (j < HEIGHT) 
		{
			u = map(i , WIDTH, -1, 1);
			v = map(j , HEIGHT, -1, 1);
			r.dir.x = u;
			r.dir.y = v;
			r.dir.z = 1;
			r.dir = normalize(r.dir);
			hit = intersect(&r, &sphere);
			bsbs = get_color(&r, hit, &sphere);
			color = (t_vec3){255 * bsbs, 0, 0};
			
			sphere.color = (((int)color.x << 16) | ((int)color.y << 8) | (int)color.z);
			if (hit > 0)
				rtv->data[(WIDTH * i) + j] = sphere.color;
			else
				rtv->data[(WIDTH * i) + j] = 0;
			j++;
		}
		i++;
	}
}

int main()
{
	t_rtv1 *rtv;

	rtv = malloc(sizeof(t_rtv1));
	rtv->still_running = sdl_init_win(rtv);
	rtv->data = malloc(sizeof(int) * (WIDTH * HEIGHT));
	while (rtv->still_running == 0)
	{
		cast_rays(rtv);
		SDL_UpdateTexture(rtv->sdl.texture, NULL, rtv->data, HEIGHT * sizeof(int));
		SDL_RenderCopy(rtv->sdl.renderer, rtv->sdl.texture, NULL, NULL);
		process_input(rtv);
		SDL_RenderPresent(rtv->sdl.renderer);
	}
	return (0);
}
