/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakbas <hakbas@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:21:11 by hakbas            #+#    #+#             */
/*   Updated: 2024/07/31 21:26:41 by hakbas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"
#include <fcntl.h>
#include <unistd.h>

static char	*tmp_filename(int hd_no)
{
	char	filename[30];
	char	*number_str;

	ft_bzero(filename, 30);
	number_str = ft_itoa(hd_no);
	if (!hd_no)
		return (NULL);
	ft_strlcat(filename, "/tmp/heredoc", 30);
	ft_strlcat(filename, number_str, 30);
	free(number_str);
	return (ft_strdup(filename));
}

void	redirect_heredoc(char *cmd, int hd_no)
{
	char	*f_name;
	int		tmp_fd;
	char	*hd_pos;

	f_name = tmp_filename(hd_no);
	if (!f_name)
		return ;
	tmp_fd = open(f_name, O_RDONLY);
	if (tmp_fd == -1)
	{
		print_perror_msg("open", f_name);
		free(f_name);
		return ;
	}
	free(f_name);
	redirect_fd(tmp_fd, STDIN_FILENO);
	hd_pos = get_redir_pos(cmd, hd_no);
	move_one_forward(hd_pos);
}
