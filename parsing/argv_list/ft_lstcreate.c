/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcreate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 16:34:30 by jonghopa          #+#    #+#             */
/*   Updated: 2023/12/13 21:09:18 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argv_list.h"

t_list	*ft_lstcreate(void)
{
	t_list	*lst;

	lst = (t_list *)malloc(sizeof(t_list));
	if (lst == NULL)
		return (NULL);
	lst->head = NULL;
	lst->tail = NULL;
	return (lst);
}
