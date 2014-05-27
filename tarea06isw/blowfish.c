#include "blowfish.h"

byte* base64_decode(byte *buffer, long largo, long *largo_salida) {

    BIO *b64, *bmem;

    byte* resultado = (byte *) calloc(largo , sizeof(byte));
    memset(resultado, 0, largo);

    b64 = BIO_new(BIO_f_base64());
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    bmem = BIO_new_mem_buf(buffer, largo);
    bmem = BIO_push(b64, bmem);

    *largo_salida = BIO_read(bmem, resultado, largo);

    BIO_free_all(bmem);

    return resultado;
}

char* descifrar(char* llave, char* mensaje) {
    char* texto;
    long largo = 0;
    byte iv[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    byte* cifrado = base64_decode((byte *) mensaje, strlen(mensaje), &largo);

    BF_KEY clave;
    BF_set_key(&clave, strlen(llave), (byte *) llave);
    texto = (char *) calloc(largo + 1, sizeof (char));

    BF_cbc_encrypt(cifrado, (byte *) texto, largo, &clave, iv, BF_DECRYPT);

    return texto;
}