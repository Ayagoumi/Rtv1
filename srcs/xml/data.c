/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoouali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 15:41:25 by yoouali           #+#    #+#             */
/*   Updated: 2021/03/04 16:00:09 by yoouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/xml.h"

char	*get_string_data(t_xmlpar *xmlpar)
{
	char	*str;
	int		len;

	str = NULL;
	while (1)
	{
		len = 0;
		while (xmlpar->line[xmlpar->ind + len] && (xmlpar->line[xmlpar->ind +\
				len] == ' ' || xmlpar->line[xmlpar->ind + len] == '\t'))
			len++;
		if (xmlpar->line[xmlpar->ind + len])
			break ;
		if (!xmlpar->line[xmlpar->ind + len])
			if (get_line(xmlpar, NULL, &len) != 1)
				return (NULL);
	}
	len = 0;
	while (xmlpar->line[xmlpar->ind + len] &&\
			xmlpar->line[xmlpar->ind + len] != '<')
		len++;
	str = ft_strsub(xmlpar->line, xmlpar->ind, len);
	xmlpar->ind = xmlpar->ind + len;
	return (str);
}

int		get_camera_data(t_xmlpar *xmlpar, int rule_num, char *str)
{
	t_vec3	vec3;

	if (rule_num == 18 && xmlpar->scene->camera->tab[2] == 0)
	{
		xmlpar->scene->camera->tab[2] = 1;
		xmlpar->scene->camera->zoom = (double)ft_atoi(str);
		return (1);
	}
	if (!(get_pos(str, &vec3)))
		return (0);
	if (rule_num == 8 && xmlpar->scene->camera->tab[0] == 0)
	{
		xmlpar->scene->camera->tab[0] = 1;
		xmlpar->scene->camera->pos = vec3;
		return (1);
	}
	if (rule_num == 9 && xmlpar->scene->camera->tab[1] == 0)
	{
		xmlpar->scene->camera->tab[1] = 1;
		xmlpar->scene->camera->dir = vec3;
		return (1);
	}
	return (0);
}

int		read_data(t_xmlpar *xmlpar, int rule_num, int parent)
{
	char	*str;

	str = NULL;
	if (!(str = get_string_data(xmlpar)))
		return (0);
	if (parent == 2)
		return (get_camera_data(xmlpar, rule_num, str));
	if (parent == 3)
		return (get_light_data(xmlpar, rule_num, str));
	else
		return (get_object_data(xmlpar, rule_num, str));
	return (0);
}
