/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagoumi <ayagoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:04:59 by ayagoumi          #+#    #+#             */
/*   Updated: 2021/03/06 16:00:35 by ayagoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

void	show_error(t_rtv1 *rtv)
{
	free(rtv);
	ft_putstr("\033[1;31m");
	ft_putstr("ヽ(｀⌒´メ)ノ Error : the program need one argument. ヽ(｀⌒´メ)ノ");
	ft_putstr("\033[0m");
	ft_putchar('\n');
	exit(1);
}

int		initialize_variables(t_rtv1 **rtv, t_scene **scene, char **av)
{
	if (!((*rtv) = malloc(sizeof(t_rtv1))))
		return (0);
	(*scene) = NULL;
	(*rtv)->still_running = sdl_init_win(*rtv);
	if (!((*rtv)->data = malloc(sizeof(int) * (WIDTH * HEIGHT))))
		return (0);
	if (!((*scene) = xml_parsser(av[1])))
	{
		free((*rtv)->data);
		return (0);
	}
	return (1);
}

int		main(int ac, char **av)
{
	t_rtv1	*rtv;
	t_scene	*scene;

	if (initialize_variables(&rtv, &scene, av) == 0)
		return (0);
	if (ac != 2)
		show_error(rtv);
	ft_cast_rays(rtv, scene);
	while (rtv->still_running == 0)
	{
		if (SDL_PollEvent(&rtv->sdl.event))
		{
			SDL_UpdateTexture(rtv->sdl.texture, NULL,
						rtv->data, HEIGHT * sizeof(int));
			SDL_RenderCopy(rtv->sdl.renderer, rtv->sdl.texture, NULL, NULL);
			SDL_DestroyTexture(rtv->sdl.texture);
			process_input(rtv, scene);
			SDL_RenderPresent(rtv->sdl.renderer);
		}
	}
	sdl_quit(rtv);
	return (0);
}
