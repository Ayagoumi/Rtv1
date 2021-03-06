/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagoumi <ayagoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 16:01:21 by yoouali           #+#    #+#             */
/*   Updated: 2021/03/06 16:01:00 by ayagoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/xml.h"

int		free_pos(char **tab, char *str, int rus)
{
	int		i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	free(str);
	return (rus);
}

int		get_pos(char *str, t_vec3 *vec3)
{
	char	**tab;
	int		len;

	tab = NULL;
	if (!(tab = ft_strsplit(str, ',')))
		return (0);
	len = 0;
	while (tab[len])
		len++;
	if (len != 3)
		return (free_pos(tab, str, 0));
	vec3->x = (double)ft_atoi(tab[0]);
	vec3->y = (double)ft_atoi(tab[1]);
	vec3->z = (double)ft_atoi(tab[2]);
	return (free_pos(tab, str, 1));
}

void	get_light_data2(t_light *light, int color)
{
	light->color.x = (color >> 16) & 255;
	light->color.y = (color >> 8) & 255;
	light->color.z = color & 255;
}

int		get_light_data(t_xmlpar *xmlpar, int rule_num, char *str)
{
	t_vec3	vec3;
	t_light	*light;
	int		color;

	light = (t_light *)xmlpar->addr;
	if (rule_num == 12 && light->tab[2] == 0)
	{
		light->tab[2] = 1;
		light->intensity = ft_atoi(str) < 0 ? 0 : (double)ft_atoi(str);
		return (1);
	}
	if (rule_num == 11 && light->tab[1] == 0)
	{
		color = get_color_data(str);
		light->tab[1] = 1;
		get_light_data2(light, color);
		return (1);
	}
	if (rule_num == 10 && light->tab[0] == 0 && get_pos(str, &vec3))
	{
		light->tab[0] = 1;
		light->pos = vec3;
		return (1);
	}
	return (0);
}
