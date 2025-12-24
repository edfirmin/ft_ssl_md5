/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfirmin <edfirmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 12:26:54 by edfirmin          #+#    #+#             */
/*   Updated: 2025/12/24 09:05:47 by edfirmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	*tab_free(char **tab){
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
} 

void maj_p(int **i, char ** av, int w_fonc){
    void (*fonc[])() = {
        handle_stdin_md5,
        handle_stdin_sha256
    };
    flg.p = 1;
    fonc[w_fonc]();
}

void maj_q(int **i, char **av, int w_fonc){
    flg.q = 1;
}

void maj_r(int **i, char **av, int w_fonc){
    flg.r = 1;
}

void maj_s(int **i, char **av, int w_fonc){
    void (*fonc[])(char*, int) = {
        main_md5,
        main_sha256
    };
    if (!av[0])
        return;
    flg.s = 1;
    fonc[w_fonc](av[0], 1);
    (**i)++;
}

int make_opt(char **av, int w_fonc, int *i){
    char* flags[] = {
        "-p",
        "-q",
        "-r",
        "-s",
		NULL
    };
    void (*maj[])(int **,char **,int) = {
        maj_p,
        maj_q,
        maj_r,
        maj_s,
        NULL
    };
    int r = 0;
    while (flags[r]){
        if(!strcmp(av[0], flags[r])){
            break;
        }
        r++;
    }
    if (r != 4){
        maj[r](&i, &av[1], w_fonc);
        return 1;
    }
    return 0;
}

void mess_error(int k, char *c){
    if (c){
        printf("ft_ssl: Error: '%s' is an invalid command.\n\n", c);
        k = 1;
    }
    char* mess[] = {
        "usage: ft_ssl command [flags] [file/string]",
        "Commands:\nmd5\nsha256\n\nFlags:\n-p -q -r -s",
        ""
    };
    printf("%s\n", mess[k]);
}

int check_flag(char* str){
    char* flags[] = {
        "-p",
        "-q",
        "-r",
        "-s",
		NULL
    };
    for (int i = 0; flags[i]; i++){
        if (!strcmp(str, flags[i]))
            return 1;
        continue;
    }
    return 0;
}

void check_opt(char **input){
    int i = 0;
    int j = 0;

    while (input[i]){
        if(input[i][0] == '-' && !check_flag(input[i])){
			j = 667;
        	break;
		}
		i++;
    }
	if (j != 0){
		printf("Error : invalide options; valide options:\n-p\n-q\n-r\n-s\n");
		exit(1);
	}
}

int check_com(char *str){
    char* comms[] = {
        "md5",
        "sha256",
		NULL
    };
    for (int i = 0; i < 2; i++){
        if (!strcmp(str, comms[i]))
            return(i);
        continue;
    }
    return (2);
}




//----------------------------------------MD5---------------------------------------//
void main_md5(char *src, int is_str) {

    __uint8_t hash[16];
    struct stat status;

    if (!is_str && stat(src, &status) == 0 && S_ISREG(status.st_mode)) {

        int fd = open(src, O_RDONLY);
        if (fd < 0)
			return;

        __uint8_t *data = calloc(status.st_size, 1);
        if (!data) {
			close(fd);
			return; 
		}
        read(fd, data, status.st_size);
        close(fd);

        md5(data, status.st_size, hash);
		flg.s = 1;
        print_all_md5(hash, src, 0);
        free(data);

        return;
    }
    md5((__uint8_t *)src, strlen(src), hash);
    print_all_md5(hash, src, 1);
}

void print_md5(__uint8_t hash[16]) {
    for (int i = 0; i < 16; i++)
        printf("%02x", hash[i]);
}

void print_all_md5(__uint8_t hash[16], char *input, int is_string){

    if (flg.q) {
        print_md5(hash);
        printf("\n");
        return;
    }
    if (flg.r) {
        print_md5(hash);
        printf(" %s\n", input);
        return;
    }
	if (flg.s){
		printf("MD5 (");
		if (is_string) printf("\"");
		printf("%s", input);
		if (is_string) printf("\"");
		printf(") = ");
		print_md5(hash);
		printf("\n");
        flg.s = 0;
		return;
	}
	printf("(");
    if (is_string) printf("\"");
    printf("%s", input);
    if (is_string) printf("\"");
    printf(") = ");
    print_md5(hash);
    printf("\n");
}

void handle_stdin_md5(void) {

    __uint8_t buf[4096];
    __uint8_t *data = NULL;
    size_t total = 0;
    size_t n;
    __uint8_t hash[16];
	
	if (isatty(0))
        printf("ft_ssl: reading from stdin, press Ctrl+D to finish the input)\n");
    while ((n = read(0, buf, sizeof(buf))) > 0) {
        __uint8_t *tmp = malloc(total + n);
        if (data) {
            memcpy(tmp, data, total);
            free(data);
        }
        memcpy(tmp + total, buf, n);
        data = tmp;
        total += n;
    }
    md5(data, total, hash);
	if (flg.p)
    	print_all_md5(hash, (char *)data, 1);
	else
		print_all_md5(hash, "stdin", 0);
    free(data);
}




//----------------------------------------SHA256----------------------------------------//
void main_sha256(char *src, int is_str) {

    __uint8_t hash[32];
    struct stat status;

    if (!is_str && stat(src, &status) == 0 && S_ISREG(status.st_mode)) {

        int fd = open(src, O_RDONLY);
        if (fd < 0)
			return;

        __uint8_t *data = calloc(status.st_size, 1);
        if (!data) {
			close(fd);
			return; 
		}
        read(fd, data, status.st_size);
        close(fd);

        sha256(data, status.st_size, hash);
		flg.s = 1;
        print_all_sha256(hash, src, 0);
        free(data);

        return;
    }
    sha256((__uint8_t *)src, strlen(src), hash);
    print_all_sha256(hash, src, 1);
}

void print_sha256(__uint8_t hash[32]) {
    for (int i = 0; i < 32; i++)
        printf("%02x", hash[i]);
}

void print_all_sha256(__uint8_t hash[32], char *input, int is_string){

    if (flg.q) {
        print_sha256(hash);
        printf("\n");
        return;
    }
    if (flg.r) {
        print_sha256(hash);
        printf(" %s\n", input);
        return;
    }
	if (flg.s){
		printf("SHA256 (");
		if (is_string) printf("\"");
		printf("%s", input);
		if (is_string) printf("\"");
		printf(") = ");
		print_sha256(hash);
		printf("\n");
        flg.s = 0;
		return;
	}
	printf("(");
    if (is_string) printf("\"");
    printf("%s", input);
    if (is_string) printf("\"");
    printf(") = ");
    print_sha256(hash);
    printf("\n");
}

void handle_stdin_sha256(void) {

    __uint8_t buf[4096];
    __uint8_t *data = NULL;
    size_t total = 0;
    size_t n;
    __uint8_t hash[32];
	
	if (isatty(0))
        printf("ft_ssl: reading from stdin, press Ctrl+D to finish the input)\n");
    while ((n = read(0, buf, sizeof(buf))) > 0) {
        __uint8_t *tmp = malloc(total + n);
        if (data) {
            memcpy(tmp, data, total);
            free(data);
        }
        memcpy(tmp + total, buf, n);
        data = tmp;
        total += n;
    }
    sha256(data, total, hash);
	if (flg.p)
    	print_all_sha256(hash, (char *)data, 1);
	else
		print_all_sha256(hash, "stdin", 0);
    free(data);
}


static size_t	nb_word(char const *str, char ch)
{
	size_t	j;
	int		i;

	i = 0;
	j = 0;
	while (str[i])
	{
		if ((str[i] != ch && str[i] != '\0')
			&& (str[i + 1] == ch || str[i + 1] == '\0'))
			j++;
		i++;
	}
	return (j);
}

static int	size_word(char const *str, char ch)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] == ch && str[i])
		i++;
	while (str[i] != ch && str[i])
	{
		j++;
		i++;
	}
	return (j);
}

static char	*copy(char *dest, const char *src, char ch)
{
	int	i;

	i = 0;
	while (src[i] && src[i] != ch)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	**tab(char const *s, char c, char **tab_str)
{
	size_t	j;
	int		i;

	i = -1;
	j = 0;
	while (s[++i] && j < nb_word(s, c))
	{
		while (s[i] == c)
			i++;
		tab_str[j] = malloc((size_word(&s[i], c) + 1) * sizeof(char));
		if (!tab_str[j])
		{
			while (j-- >= 0)
				free(tab_str[j]);
			free(tab_str);
			return (0);
		}
		copy(tab_str[j], &s[i], c);
		if (s[i + size_word(&s[i], c)])
			i += size_word(&s[i], c);
		j++;
	}
	tab_str[j] = NULL;
	return (tab_str);
}

char	**ft_split(char const *s, char c)
{
	char		**tab_str;

	tab_str = (char **)malloc((nb_word(s, c) + 1) * sizeof(char *));
	if (!tab_str)
	{
		free(tab_str);
		return (0);
	}
	return (tab(s, c, tab_str));
}

int c_tab(char **tab){
    int i = 0;
    while (tab[i])
        i++;
    return (i);
}

char **take_in(void){
    __uint8_t buf[4096];
    __uint8_t *data = NULL;
    size_t total = 0;
    size_t n;
    __uint8_t hash[16];
	
	if (isatty(0))
        printf("ft_ssl: reading from stdin, press Ctrl+D to finish the input (with out quote)\n");
    while ((n = read(0, buf, sizeof(buf))) > 0) {
        __uint8_t *tmp = malloc(total + n);
        if (data) {
            memcpy(tmp, data, total);
            free(data);
        }
        memcpy(tmp + total, buf, n);
        data = tmp;
        total += n;
    }
    return (ft_split(((char* const)data), ' '));
}
