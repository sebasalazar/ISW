/**
 * @file main.c
 * @author Sebastián Salazar Molina <sebasalazar@gmail.com>
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parseador.h"
#include "blowfish.h"

/*
 * Pequeño programa para ocupar Curl en C
 */
int main(int argc, char** argv) {
    int opcion = 0;
    int salida;
    char* respuesta = NULL;
    char* mensaje = NULL;
    char* descifrado = NULL;

    LIBXML_TEST_VERSION;

    if (argc < 2) {
        opcion = -1;
    } else {
        if (strcmp(argv[1], "-d") == 0) {
            opcion = 1;
        } else if (strcmp(argv[1], "-v") == 0) {
            opcion = 2;
        } else {
            opcion = -2;
        }
    }

    switch (opcion) {
        case 1:
            respuesta = obtener_xml("http://sebastian.cl", 80, "/isw-rest/api/mensajeCifrado");
            if (respuesta != NULL) {
                fprintf(stdout, "\nXML : %s\n", respuesta);
                mensaje = getNodo(respuesta, "mensaje");
                // fprintf(stderr, "\nMensaje : %s\n", mensaje);

                descifrado = descifrar("isw", mensaje);
                fprintf(stdout, "\nDescifrado : %s\n", descifrado);
                salida = EXIT_SUCCESS;
            } else {
                fprintf(stderr, "\nError de Comunicacion.");
                salida = EXIT_FAILURE;
            }
            break;

        case 2:
            fprintf(stdout, "Fecha de Compilacion: %s %s\n", __DATE__, __TIME__);
            fprintf(stdout, "Version: 1.0.2\n");
            fprintf(stdout, "\n\tSebastian Salazar Molina\n");
            salida = EXIT_SUCCESS;
            break;

        default:
            fprintf(stdout, "\nModo de uso:");
            fprintf(stdout, "\n%s -d : Se conecta y descifra el XML", argv[0]);
            fprintf(stdout, "\n%s -v : Muestra la información de versión\n\n", argv[0]);
            salida = EXIT_FAILURE;
            break;
    }

    return salida;
}
