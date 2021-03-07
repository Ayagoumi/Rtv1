/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagoumi <ayagoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 19:23:56 by ayagoumi          #+#    #+#             */
/*   Updated: 2021/03/06 15:08:48 by ayagoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

void	process_input(t_rtv1 *rtv, t_scene *scene)
{
	const Uint8		*keystates;

	keystates = SDL_GetKeyboardState(NULL);
	SDL_PollEvent(&rtv->sdl.event);
	if (rtv->sdl.event.type == SDL_QUIT)
	{
		rtv->still_running = 1;
		free_structer(scene);
	}
	else if (keystates[SDL_SCANCODE_ESCAPE])
	{
		rtv->still_running = 1;
		free_structer(scene);
	}
}
