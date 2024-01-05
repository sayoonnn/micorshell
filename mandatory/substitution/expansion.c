/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:38:30 by sayoon            #+#    #+#             */
/*   Updated: 2024/01/04 15:38:31 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	join_str_to_lastnode(t_list *res, char *str)
{
	t_node	*lastnode;
	t_node	*newnode;
	char	*tmp;

	lastnode = res->tail;
	if (lastnode == NULL)
	{
		newnode = ft_lstnew(str);
		if (!newnode)
			exit(1);
		ft_lstadd_back(res, newnode);
		return ;
	}
	tmp = ft_strjoin(lastnode->content, str);
	free(str);
	free(lastnode->content);
	lastnode->content = tmp;
}

static void	split_n_add(t_list *ret, char *str)
{
	char	**splited;
	int		i;

	splited = ft_split_white(str);
	i = 0;
	if (ft_lstsize(ret) != 0 && ret->tail->content != NULL)
		join_str_to_lastnode(ret, splited[i++]);
	while (splited[i])
		ft_lstadd_back(ret, ft_lstnew(splited[i++]));
	ft_lstadd_back(ret, ft_lstnew(NULL));
	free(splited);
	free(str);
}

static void	trim_quote(t_list *ret, char *str)
{
	char	*tmp;
	int		is_quoted;

	is_quoted = false;
	if (is_quote(*str))
	{
		tmp = ft_substr(str, 1, ft_strlen(str) - 2);
		is_quoted = true;
	}
	else
		tmp = ft_strdup(str);
	if (is_there_white(tmp) && !is_quoted)
		split_n_add(ret, tmp);
	else
	{
		if (ft_lstsize(ret) != 0 && ret->tail->content == NULL)
			ft_lstadd_back(ret, ft_lstnew(tmp));
		else
			join_str_to_lastnode(ret, tmp);
	}
}

static t_list	*remove_null_node(t_list *lst)
{
	t_list	*tmp;
	t_node	*node;
	t_node	*t;

	tmp = ft_lstcreate();
	node = lst->head;
	while (node)
	{
		if (node->content != NULL)
		{
			ft_lstadd_back(tmp, node);
			node = node->next;
		}
		else
		{
			tmp->tail->next = node->next;
			t = node;
			node = node->next;
			free(t);
		}
	}
	free(lst);
	return (tmp);
}

t_list	*expansion(char *str, t_envtree *env)
{
	t_list	*word_split;
	t_list	*ret;
	t_node	*word;
	char	*refined;

	word_split = ft_lstcreate();
	ret = ft_lstcreate();
	add_to_lst(word_split, str);
	word = word_split->head;
	while (word != NULL)
	{
		refined = ft_strdup("");
		if (substitute_dollar(word->content, env, &refined))
			exit(1);
		if (*refined != 0)
			trim_quote(ret, refined);
		free(refined);
		word = word->next;
	}
	ret = remove_null_node(ret);
	ft_lstclear(word_split);
	free(word_split);
	return (ret);
}
