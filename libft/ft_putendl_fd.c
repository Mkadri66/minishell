/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkadri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 20:05:15 by mkadri            #+#    #+#             */
/*   Updated: 2023/10/25 14:07:04 by mkadri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	write(fd, "\n", 1);
}

/*
int	main()
{
	FILE	*fichier;

	fichier = fopen("monfichier.txt", "r");
	
	char buffer[100];
    while (fgets(buffer, sizeof(buffer), fichier) != NULL) {
        printf("%s", buffer);
    }

    // Fermer le fichier en lecture
    fclose(fichier);
}
*/