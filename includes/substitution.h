/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitution.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devpark <devpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 22:37:01 by sayoon            #+#    #+#             */
/*   Updated: 2024/01/02 12:43:25 by devpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SUBSTITUTION_H
# define SUBSTITUTION_H
# include "parse_tree.h"
# include "env_tree.h"
# include "types.h"

extern int	g_errcode;

char	**ft_split_white(char const *s);
void	free_perfectly_split(char **strs);
int		ft_strjoin_in_depend(char **s1, char *content, size_t *s, size_t *idx);
int		remove_all_quotes(t_list *res, char **ref);
t_list	*interprete_words(t_list *contents, t_envtree *env);
char	**convert_word_lst_to_array(t_list *contents, t_envtree *env);

#endif
