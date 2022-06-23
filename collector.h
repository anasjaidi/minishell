/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collector.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaidi <ajaidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 17:01:30 by ajaidi            #+#    #+#             */
/*   Updated: 2022/06/23 20:33:02 by ajaidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLLECTOR_H
# define COLLECTOR_H

// start including libs

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

// end including 

// start linked list methode
typedef struct collector
{
	void				*adr;
	struct collector	*next;
}	t_collector;

t_collector	*new_node(void *adr);
t_collector	**append_adr(t_collector **root, void *adr);
void		*ft_col_ft_malloc(t_collector **root, size_t size);
void		ft_collect(t_collector **root, t_collector *node);

// end linked list methode

// strat array methode

int			lst_size(void **lst);
void		*ft_ft_malloc_array(void ***lst, size_t size);
void		append_array(void ***list, void *adr);
void		lst_free(void **lst);
int			lst_size(void **lst);

// end array methode

#endif