/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excute_hub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:00:10 by sayoon            #+#    #+#             */
/*   Updated: 2023/12/05 16:00:10 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	excute_hub(t_tree_node *pt, t_envtree *env)
{
	static is_pipe = 0;
	int io_fd[2] = {0, 1};

	if (pt == NULL)
		return ;
	if (pt->token_type == PIPELINE)
	{
		excute_hub(pt->right, env);
		excute_hub(pt->left, env);
		return ;
	}
	if (pt->token_type == CMD)
	{
		// $ 치환
		handle_redir(pt->right, io_fd);
		exec_single_cmd(pt->left->contents, env, io_fd);
	}
}
