#include "parseador.h"

int escribir_datos(void *ptr, size_t size, size_t nmemb, void *ctx) {
    postdata *cbc = ctx;

    if (cbc->body_pos + size * nmemb > cbc->body_size) {
        return 0;
    }

    memcpy(&cbc->data[cbc->body_pos], ptr, size * nmemb);
    cbc->body_pos += size * nmemb;
    return size * nmemb;
}

char* obtener_xml(char* servidor, int puerto, char *url) {
    CURL *curl;
    CURLcode res;

    char* conexion;
    char* respuesta;
    char datos[8192];
    int tamano = 8192;
    postdata cbc;
    cbc.data = datos;
    cbc.body_size = tamano;
    cbc.body_pos = 0;
    struct curl_slist *slist = NULL;


    // Reservo espacio para el buffer del servidor
    conexion = (char *) calloc((strlen(servidor) + strlen(url) + 15), sizeof (char));

    sprintf(conexion, "%s:%d%s", servidor, puerto, url);

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "sebastian.cl/1.0");
        curl_easy_setopt(curl, CURLOPT_URL, conexion);
        curl_easy_setopt(curl, CURLOPT_COOKIEFILE, ""); // mantener cookies en memoria. 
        curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_1);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0); // No verificar el certificar peer 
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0); // No verificar contra el host del cert
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1); // rebotar a la siguiente página 
        curl_easy_setopt(curl, CURLOPT_FORBID_REUSE, 1); // mimic real world use
        curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1); // Desabilitar señales en el uso de thread 


        curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 15L);
        curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);

        curl_easy_setopt(curl, CURLOPT_HEADER, 0L);
        curl_easy_setopt(curl, CURLOPT_WRITEHEADER, 0L);
        slist = curl_slist_append(NULL, "Accept: application/xml;");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, slist);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &escribir_datos);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &cbc);



        res = curl_easy_perform(curl);

        respuesta = (char*) calloc(strlen(cbc.data) + 1, sizeof (char));
        sprintf(respuesta, "%s", cbc.data);
        respuesta[strlen(cbc.data)] = '\0';

        /* Limpiar */
        curl_slist_free_all(slist);
        curl_easy_cleanup(curl);

    }

    return respuesta;
}

char* getNodo(char* xml, char* nombreNodo) {
    char* resultado = NULL;
    xmlDoc* doc = NULL;
    xmlNode* raiz = NULL;
    xmlNode* nodo = NULL;

    if (strlen(xml) > 0) {
        doc = xmlParseDoc((xmlChar *) xml);
        if (doc) {
            raiz = xmlDocGetRootElement(doc);

            // Cómo es un arbol muy pequeño usaremos fuerza bruta,
            // para arboles grandes es mejor usar xpath o alguna estrategia similar.
            nodo = raiz->children;
            while (nodo != NULL) {
                if (xmlStrcasecmp(nodo->name, (xmlChar *) nombreNodo) == 0) {
                    resultado = (char *) xmlNodeGetContent(nodo);
                }
                nodo = nodo->next;
            }
        }
        xmlFreeDoc(doc);
        xmlCleanupParser();
    }

    return resultado;
}
