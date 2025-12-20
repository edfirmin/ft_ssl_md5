/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edilson <edilson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 12:27:20 by edfirmin          #+#    #+#             */
/*   Updated: 2025/11/26 10:34:37 by edilson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static const __uint32_t r[64] = {
    7,12,17,22,7,12,17,22,7,12,17,22,7,12,17,22,
    5,9,14,20,5,9,14,20,5,9,14,20,5,9,14,20,
    4,11,16,23,4,11,16,23,4,11,16,23,4,11,16,23,
    6,10,15,21,6,10,15,21,6,10,15,21,6,10,15,21
};

__uint32_t fonc_K(int i){
    double v = fabs(sin(i + 1));
    return (4294967296 * v);// 4294967296 == 2^32
}

// __uint32_t leftrotate (x, c){
//     return (x << c) | (x >> (32-c));
// }

#define leftrotate(x, c) (((x) << (c)) | ((x) >> (32-(c))))

void md5(const __uint8_t *msg, int len, __uint8_t outp[16]) {
    __uint32_t a0 = 0x67452301;// valeur arbitaire du RFC
    __uint32_t b0 = 0xefcdab89;// pareil
    __uint32_t c0 = 0x98badcfe;// pareil
    __uint32_t d0 = 0x10325476;// pareil

    int new_len = len + 1;//pareil
    while (new_len % 64 != 56) new_len++;// pour setup les remplissage de "0" 
    __uint8_t *msg_pad = calloc(new_len + 8, 1);// pareil

    memcpy(msg_pad, msg, len);
    msg_pad[len] = 0x80;  // pour mettre un "1" devant

    __uint64_t bits_len = (__uint64_t)len * 8;
    memcpy(msg_pad + new_len, &bits_len, 8);

    for (int offset = 0; offset < new_len; offset += 64) {
        __uint32_t *w = (__uint32_t*)(msg_pad + offset);

        __uint32_t A = a0, B = b0, C = c0, D = d0;

        for (int i = 0; i < 64; i++) {
            __uint32_t F, g;
            if (i < 16) {
                F = (B & C) | ((~B) & D);
                g = i;
            } else if (i < 32) {
                F = (D & B) | ((~D) & C);
                g = (5 * i + 1) % 16;
            } else if (i < 48) {
                F = B ^ C ^ D;
                g = (3 * i + 5) % 16;
            } else {
                F = C ^ (B | (~D));
                g = (7 * i) % 16;
            }
            __uint32_t tmp = D;
            D = C;
            C = B;
            B = leftrotate((F + A + fonc_K(i) + w[g]), r[i]) + B;
            A = tmp;
        }
        a0 += A;
        b0 += B;
        c0 += C;
        d0 += D;
    }

    memcpy(outp, &a0, 4);
    memcpy(outp + 4, &b0, 4);
    memcpy(outp + 8, &c0, 4);
    memcpy(outp+12, &d0, 4);
    free(msg_pad);
}

