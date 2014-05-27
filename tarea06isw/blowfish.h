/* 
 * File:   blowfish.h
 * Author: seba
 *
 * Created on May 26, 2014, 5:46 PM
 */

#ifndef BLOWFISH_H
#define	BLOWFISH_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <openssl/bio.h>
#include <openssl/blowfish.h>
#include <openssl/rand.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>
#include <openssl/err.h>

    /**
     * @typede typedef unsigned char byte
     * Definición por comodidad de un unsigned char byte 
     */
    typedef unsigned char byte;

    byte* base64_decode(byte *buffer, long len, long *len_out);

    char* descifrar(char* llave, char* mensaje);

#ifdef	__cplusplus
}
#endif

#endif	/* BLOWFISH_H */

