/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfirmin <edfirmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 11:37:43 by edfirmin          #+#    #+#             */
/*   Updated: 2025/12/24 08:35:42 by edfirmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

t_flag flg = {0, 0, 0, 0};

void go_sha256 (char **av, int ac){
    for (int i = 0; i < ac; i++) {
        if (make_opt(&av[i], 1, &i))
            continue;
        main_sha256(av[i], 0);
    }
    if (!isatty(0) && !flg.p)
        handle_stdin_sha256();
}

void go_md5 (char **av, int ac){
    for (int i = 0; i < ac; i++) {

        if (make_opt(&av[i], 0, &i))
            continue;
        main_md5(av[i], 0);
    }
    if (!isatty(0) && !flg.p)
        handle_stdin_md5();
}

int main(int ac, char** av){
    char **in_av = NULL;
    if (ac < 2)
        return mess_error(0, NULL), 0;
    else if (check_com(av[1]) == 2)
        return mess_error(667, av[1]), 0;
    check_opt(&av[2]);
    void (*fonc[])(char**, int) = {
        go_md5,
        go_sha256
    };
    if (ac == 2 && isatty(0)){
        in_av = take_in();
        fonc[check_com(av[1])](in_av, c_tab(in_av));
        tab_free(in_av);
        return 0;
    }
    fonc[check_com(av[1])](&av[2], ac - 2);
    return (1);
}
