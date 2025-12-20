/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfirmin <edfirmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 12:46:59 by edfirmin          #+#    #+#             */
/*   Updated: 2025/12/20 14:30:21 by edfirmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef struct {
	int p;
    int q;
    int r;
	int s;
} t_flag;

extern t_flag flg;

//----------UTILS----------//
void    mess_error(int k, char *c);
// int     ft_strlen(char *str);
// char	*ft_strjoin(char *s1, char *s2);
// char	*ft_strdup(char *s1);
int     check_com(char *str);
void 	check_opt(char **input);
int make_opt(char **av, int w_fonc, int *i);
void maj_s(int **i, char **av, int w_fonc);
void maj_r(int **i, char **av, int w_fonc);
void maj_q(int **i, char **av, int w_fonc);
void maj_p(int **i, char **av, int w_fonc);
// void	*tab_free(char **tab);
// void	*ft_calloc(size_t count, size_t size);
// void	ft_bzero(void *s, size_t n);

void    md5(const __uint8_t *msg, int len, __uint8_t outp[16]);
void 	main_md5(char *src, int is_str);
void 	print_all_md5(__uint8_t hash[16], char *input, int is_string);
void 	handle_stdin_md5(void);

void    sha256(const __uint8_t *msg, int len, __uint8_t outp[32]);
void 	main_sha256(char *src, int is_str);
void 	print_all_sha256(__uint8_t hash[32], char *input, int is_string);
void 	handle_stdin_sha256(void);


#endif
