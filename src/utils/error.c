/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumarque <lumarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 00:11:51 by lumarque          #+#    #+#             */
/*   Updated: 2024/10/30 00:16:28 by lumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	print_error_syntax(t_shell *sh, char *msg, int exit)
{
	int	len;

	len = ft_strlen(msg);
	ft_putstr_fd(ERROR_HEAD, STDERR_FILENO);
	ft_putstr_fd(ERROR_SYNTAX, STDERR_FILENO);
	if (!*msg)
		ft_putstr_fd("newline", STDERR_FILENO);
	else if (len > 1 && (*(msg + 1) == *msg || *(msg - 1) == *msg) && \
			*msg != '(' && *msg != ')')
	{
		ft_putchar_fd(*msg, STDERR_FILENO);
		ft_putchar_fd(*msg, STDERR_FILENO);
	}
	else
		ft_putchar_fd(*msg, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
	sh->status = RESTORE;
	g_exit = exit;
	return (TRUE);
}

int	print_error_unsupport(t_shell *sh, char *msg, int exit)
{
	ft_putstr_fd(ERROR_HEAD, STDERR_FILENO);
	ft_putstr_fd("no support for operator `", STDERR_FILENO);
	ft_putchar_fd(*msg, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
	sh->status = RESTORE;
	g_exit = exit;
	return (TRUE);
}
