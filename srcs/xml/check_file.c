/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoouali <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 14:27:32 by yoouali           #+#    #+#             */
/*   Updated: 2021/03/05 08:41:40 by yoouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/xml.h"

int		get_line(t_xmlpar *xmlpar, char *rule, int *rule_num)
{
	free(xmlpar->line);
	xmlpar->line = NULL;
	if (get_next_line(xmlpar->fd, &xmlpar->line) < 1)
	{
		if (rule)
			*rule_num = -1;
		else
			*rule_num = 0;
		return (0);
	}
	xmlpar->nline += 1;
	xmlpar->ind = 0;
	return (1);
}

int		free_parrser(char *rule, int ret, int parent, t_xmlpar *xml)
{
	if (parent == 0)
	{
		if (ret == -1)
		{
			write(1, "Rtv1 Error : syntax error in line ", 34);
			ft_putnbr(xml->nline);
			write(1, "\n", 1);
		}
		close(xml->fd);
	}
	free(rule);
	return (ret);
}

int		check_file(t_xmlpar *xmlpar, int parent)
{
	int		rule_num;
	char	*rule;

	rule = NULL;
	while (1)
	{
		if (!xmlpar->line || !xmlpar->line[xmlpar->ind])
			if (get_line(xmlpar, rule, &rule_num) == 0)
				return (free_parrser(rule, rule_num, parent, xmlpar));
		while (xmlpar->line[xmlpar->ind] == '\t' ||\
				xmlpar->line[xmlpar->ind] == ' ')
			xmlpar->ind = xmlpar->ind + 1;
		if (xmlpar->line[xmlpar->ind] && xmlpar->line[xmlpar->ind] != '<')
			return (free_parrser(rule, -1, parent, xmlpar));
		if (xmlpar->line[xmlpar->ind] && xmlpar->line[xmlpar->ind] == '<'\
				&& xmlpar->line[xmlpar->ind + 1] != '/')
			if (parrs_rule(xmlpar, &rule, &rule_num, parent) == 0)
				return (free_parrser(rule, -1, parent, xmlpar));
		if (xmlpar->line[xmlpar->ind] && xmlpar->line[xmlpar->ind] == '<'\
				&& xmlpar->line[xmlpar->ind + 1] == '/')
			return (free_parrser(rule, parrs_rule_end(xmlpar, &rule),\
						parent, xmlpar));
	}
	return (0);
}
