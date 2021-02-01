/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagoumi <ayagoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:04:59 by ayagoumi          #+#    #+#             */
/*   Updated: 2021/02/01 19:41:45 by ayagoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

void    cast_rays(t_rtv1 *rtv)
{
    int i;
    int j;

    i = 0;
    while (i < HEIGHT)
    {
        j = 0;
        while (j < WIDTH)
        {
            rtv->data[(HEIGHT * i) + j] = ((1 << 24 ) + ((int)(255.999 * (i / WIDTH)) << 16) + ((int)(255.999 * (i / HEIGHT)) << 8) + (0.25));
            // printf("%d\n",rtv->data[HEIGHT * i + j]);
            j++;
        }
        // printf("\n");
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