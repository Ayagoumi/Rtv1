/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagoumi <ayagoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:11:36 by ayagoumi          #+#    #+#             */
/*   Updated: 2021/03/06 15:57:49 by ayagoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

int			sdl_init_win(t_rtv1 *rtv)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	rtv->sdl.win = SDL_CreateWindow(
			"Wolf_3D",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			WIDTH,
			HEIGHT,
			SDL_WINDOW_OPENGL);
	if (!rtv->sdl.win)
		return (1);
	sdl_init_texture(rtv);
	return (0);
}

int			sdl_init_render(t_rtv1 *rtv)
{
	rtv->sdl.renderer = SDL_CreateRenderer(
			rtv->sdl.win,
			-1,
			0);
	if (!rtv->sdl.renderer)
		return (1);
	return (0);
}

int			sdl_init_texture(t_rtv1 *rtv)
{
	sdl_init_render(rtv);
	rtv->sdl.texture = SDL_CreateTexture(
			rtv->sdl.renderer,
			SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_STREAMING,
			WIDTH,
			HEIGHT);
	if (!rtv->sdl.texture)
		return (1);
	return (0);
}

void		sdl_quit(t_rtv1 *rtv)
{
	SDL_DestroyRenderer(rtv->sdl.renderer);
	SDL_DestroyWindow(rtv->sdl.win);
	free(rtv->data);
	free(rtv);
	SDL_Quit();
}
