/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boris <boris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 11:45:00 by boris             #+#    #+#             */
/*   Updated: 2026/05/07 11:56:11 by boris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

volatile sig_atomic_t	g_signal = 0;

/*
@brief PARENT SIGINT FULL
** Full signal handler for SIGINT when inside readline context.
@param sig Signal number (SIGINT = 2 when Ctrl+C is pressed).
@return void
*/
static void	parent_sa(int sig)
{
	(void)sig;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

/*
@brief PARENT SIGINT SIMPLE
** Simplified signal handler for SIGINT when waiting for child.
@param sig Signal number (SIGINT = 2 when Ctrl+C is pressed).
@return void
*/
static void	child_sa(int sig)
{
	(void)sig;
	printf("\n");
}

/*
@brief HEREDOC SIGINT
** Signal handler for SIGINT during heredoc input.
@param sig Signal number (SIGINT = 2 when Ctrl+C is pressed).
@return void
*/
static void	heredoc_sa(int sig)
{
	(void)sig;
	g_signal = 1;
	printf("\n");
	rl_replace_line("", 0);
	close(0);
}

/*
@brief SETUP SIGNAL
** Configures signal handlers for the shell based on operation mode.
@param mode Operation mode (0=parent, 1=ignore, 2=child, 3=heredoc).
@return void
*/
void	setup_signal(int mode)
{
	struct sigaction	sig_int;
	struct sigaction	sig_quit;

	ft_memset(&sig_int, 0, sizeof(struct sigaction));
	ft_memset(&sig_quit, 0, sizeof(struct sigaction));
	sig_quit.sa_handler = SIG_IGN;
	if (mode == 0)
		sig_int.sa_handler = &parent_sa;
	else if (mode == 1)
		sig_int.sa_handler = SIG_IGN;
	else if (mode == 2)
	{
		sig_int.sa_handler = &child_sa;
	}
	else if (mode == 3)
		sig_int.sa_handler = &heredoc_sa;
	sigaction(SIGINT, &sig_int, NULL);
	sigaction(SIGQUIT, &sig_quit, NULL);
}
