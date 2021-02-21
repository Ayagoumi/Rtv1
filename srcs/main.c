/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagoumi <ayagoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:04:59 by ayagoumi          #+#    #+#             */
/*   Updated: 2021/02/21 11:29:51 by ayagoumi         ###   ########.fr       */
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


void setup_scene(t_ray *r, t_sphere *sphere, t_light *l)
{
	r->origin.x = 0;
	r->origin.y = 0;
	r->origin.z = -1;

	sphere->pos.x = 0;
	sphere->pos.y = 0;
	sphere->pos.z = 1;
	sphere->r = 0.9;
	sphere->color.x = 255;
	sphere->color.y = 16;
	sphere->color.z = 256;

	l->pos.x = 0;
	l->pos.y = 6;
	l->pos.z = -10;

	l->color.x = 255;
	l->color.z = 255;
	l->color.y = 255;
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
