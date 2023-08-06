/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklingsh <nklingsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 16:00:25 by nklingsh          #+#    #+#             */
/*   Updated: 2023/08/03 17:57:22 by nklingsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_status_exit_code = 0;

void	sig_process(int sig_num)
{
	if (sig_num == SIGQUIT)
		g_status_exit_code = 131;
	else if (sig_num == SIGINT)
		g_status_exit_code = 130;
}

int	parsing(t_init *init, char *read_line)
{
	t_token_list *head;
	init->lst_mal = NULL;
	lstaddback_malloc(init, lstnew_malloc(read_line));
	init->lst_lex = lexer_lexing(read_line, init);
	// if (check_error(init->lst_lex))
		// return (printf("\nfais ta fonction free connard \n\n\n"), 0);
	expander_expanding(init);
	print_lst_env(init->lst_env);
	init->lst_token = get_all_token(init);
	head = init->lst_token;
	// printf("---> token size %d \n", ft_size_token(init->lst_token));
	
	return (0);
}

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	t_init init;

	init.lst_env = init_env_list(env);
	signal(SIGINT, routine_start);
	while(1)
		{
			init.read_line = readline("minishell :");
			parsing(&init, init.read_line);
			if (ft_strcmp(init.read_line, "exit") == 0)
				return (free(init.read_line), 0);
			exec(&init);
			free(init.read_line);
			
		}
	free(init.read_line);
	return (printf("finito bizarre"), 0);
}