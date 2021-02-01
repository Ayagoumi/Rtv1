/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagoumi <ayagoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:05:37 by ayagoumi          #+#    #+#             */
/*   Updated: 2021/02/01 19:26:50 by ayagoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "../libft/libft.h"
# include "mlx.h"
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include "../SDL/SDL2.framework/Headers/SDL.h"
# include "../SDL/SDL2_ttf.framework/Headers/SDL_ttf.h"
# include "../SDL/SDL2_image.framework/Headers/SDL_image.h"
# define WIDTH 1300
# define HEIGHT 1300

typedef struct			s_sdl
{
	SDL_Window			*win;
	SDL_Renderer		*renderer;
	SDL_Texture			*texture;
	SDL_Event			event;
}						t_sdl;

typedef struct			s_rtv1
{
	t_sdl				sdl;
	int					*data;
    int                 still_running;
}						t_rtv1;

int			sdl_init_texture(t_rtv1	*rtv);
int         sdl_init_render(t_rtv1   *rtv);
int			sdl_init_win(t_rtv1	*rtv);

void	process_input(t_rtv1 *rtv);

#endif
