/* 
 * File:   parseador.h
 * Author: seba
 *
 * Created on May 26, 2014, 7:03 PM
 */

#ifndef PARSEADOR_H
#define	PARSEADOR_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

    typedef struct {
        char *data;
        int body_size;
        int body_pos;
    } postdata;

    int escribir_datos(void *ptr, size_t size, size_t nmemb, void *ctx);
    char* obtener_xml(char* servidor, int puerto, char *url);
    char* getNodo(char* xml, char* nombreNodo);

#ifdef	__cplusplus
}
#endif

#endif	/* PARSEADOR_H */

