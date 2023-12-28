/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devpark <devpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:31:08 by sayoon            #+#    #+#             */
/*   Updated: 2023/12/26 17:28:07 by devpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int parse_line(char *line, t_parsing *parsing)
{
	int			flag;

	if (*line == 0)
		return (false);
	if (tokenize(line, parsing))
		exit(1);
	flag = analyze_syntax(parsing);
	if (flag == 1)
		exit(1);
	if (flag == 258)
	{
		clean_parsing_tools(parsing);
		return (false);
	}
	parsing->detach = 0;
	return (true);
}
