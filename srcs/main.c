/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagoumi <ayagoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:04:59 by ayagoumi          #+#    #+#             */
/*   Updated: 2021/02/21 19:08:41 by ayagoumi         ###   ########.fr       */
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


t_sphere *setup_scene(t_ray *r, t_light *l)
{
    r->origin.x = 0;
    r->origin.y = 0;
    r->origin.z = -1;
	
    t_sphere *sphere;
    sphere = (t_sphere *)malloc(sizeof(t_sphere));
    sphere->pos.x = 0.2;
    sphere->pos.y = 0;
    sphere->pos.z = 0;
    sphere->r = 0.2;
    sphere->color.x = 255;
    sphere->color.y = 0;
    sphere->color.z = 0;
    sphere->next = NULL;
    
	t_sphere *tmp;
    tmp = (t_sphere *)malloc(sizeof(t_sphere));
    tmp->pos.x = 0;
    tmp->pos.y = 0;
    tmp->pos.z = 0;
    tmp->r = 0.2;
    tmp->color.x = 0;
    tmp->color.y = 255;
    tmp->color.z = 255;

    tmp->next = NULL;
    sphere->next = tmp;
	tmp->next = (t_sphere *)malloc(sizeof(t_sphere));
	tmp = tmp->next;
    tmp->pos.x = -0.2;
    tmp->pos.y = 0;
    tmp->pos.z = 0;
    tmp->r = 0.2;
    tmp->color.x = 0;
    tmp->color.y = 255;
    tmp->color.z = 0;
	tmp->next = NULL;

    l->pos.x = 0;
    l->pos.y = 0;
    l->pos.z = -1;
    l->color.x = 255;
    l->color.z = 255;
    l->color.y = 255;
	l->next = NULL;
	
	t_light *head;
	head = l;
	l->next = (t_light *)malloc(sizeof(t_light));
	l = l->next;
	l->pos.x = 0;
    l->pos.y = -10;
    l->pos.z = -10;
    l->color.x = 255;
    l->color.y = 255;
    l->color.z = 255;
	l->next = NULL;
	l = head;
    return (sphere);
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
