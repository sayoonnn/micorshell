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

void	sub_redir_exec_single(t_parsing *ps, t_envtree *env)
{
	t_tree_node	*node;

	node = ps->root;
	node->fd[0] = 0;
	node->fd[1] = 1;
	if (!handle_redir(ps, env, node->right, node->fd))
	{
		err_code = 1 << 8;
		return ;
	}
	substitute_words(ps, env, ps->root->left->contents);
	exec_single_cmd(node, env, ps->word_lst);
}

static void	reset_setting(int saved_fd[2])
{
	signal(SIGINT, SIG_IGN);
	while (wait(&err_code) != -1)
		;
	if (WIFSIGNALED(err_code))
	{
		if (WTERMSIG(err_code) == SIGQUIT)
			printf("Quit: 3");
		printf("\n");
		err_code = (128 + WTERMSIG(err_code)) << 8;
	}
	else
		err_code = err_code >> 8;
	set_signal();
	dup2(saved_fd[0], STDIN_FILENO);
	dup2(saved_fd[1], STDOUT_FILENO);
	saved_fd[0] = -1;
	saved_fd[1] = -1;
}

static void	exchange_lst(t_parsing *ps, t_tree_node *node, \
						t_envtree *env, int n)
{
	node->cmd_cnt = n;
	substitute_words(ps, env, node->left->contents);
	ft_lstclear(node->left->contents);
	node->left->contents->head = ps->word_lst->head;
	ps->word_lst->head = NULL;
	ps->word_lst->tail = NULL;
}

void	sub_redir_exec_pipe(t_parsing *ps, t_tree_node *node, \
							t_envtree *env, int n)
{
	static int	saved_fd[2] = {-1, -1};

	if (saved_fd[0] == -1 && saved_fd[1] == -1)
	{
		saved_fd[0] = dup(STDIN_FILENO);
		saved_fd[1] = dup(STDOUT_FILENO);
	}
	if (node->left->token_type == PIPE)
	{
		sub_redir_exec_pipe(ps, node->left, env, n + 1);
		exchange_lst(ps, node, env, n);
		exec_pipe_cmd(node->right, env, saved_fd);
	}
	else
	{
		exchange_lst(ps, node->left, env, n + 1);
		exec_pipe_cmd(node->left, env, saved_fd);
		exchange_lst(ps, node->right, env, n);
		exec_pipe_cmd(node->right, env, saved_fd);
	}
	if (n == 0)
		reset_setting(saved_fd);
}

void	excute_hub(t_parsing *ps, t_envtree *env)
{
	if (ps->root->token_type == CMD)
		sub_redir_exec_single(ps, env);
	else
	{
		trave_redir(ps, env, ps->root);
		sub_redir_exec_pipe(ps, ps->root, env, 0);
	}
}
