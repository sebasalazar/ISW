package cl.sebastian.isw.utils;

import java.io.Serializable;
import java.util.Arrays;
import javax.crypto.Cipher;
import javax.crypto.spec.IvParameterSpec;
import javax.crypto.spec.SecretKeySpec;
import org.apache.commons.codec.binary.Base64;
import org.apache.commons.codec.digest.DigestUtils;
import org.apache.commons.lang3.StringUtils;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 *
 * @author Sebastián Salazar Molina <ssalazar@orangepeople.cl>
 */
public class SecurityUtils implements Serializable {

    private static final String algoritmo = "Blowfish";
    private static final String modoAlgoritmo = "Blowfish/CBC/PKCS5Padding";
    private static final Logger logger = LoggerFactory.getLogger(SecurityUtils.class);

    public static String hashSha256(String text) {
        String hash = "";
        try {
            hash = DigestUtils.sha256Hex(text);
        } catch (Exception e) {
            logger.error(e.toString());
            logger.debug(e.toString());
        }
        return hash;
    }

    public static String hashSha1(String text) {
        String hash = "";
        try {
            hash = DigestUtils.sha1Hex(text);
        } catch (Exception e) {
            logger.error(e.toString());
            logger.debug(e.toString());
        }
        return hash;
    }

    public static String cifrar(String llave, String mensaje) {
        String resultado = "";
        try {
            if (StringUtils.isNotBlank(llave) && StringUtils.isNotEmpty(mensaje)) {
                // Mejorar la versión adjuntando el vector de inicialización
                byte[] biv = new byte[8];
                Arrays.fill(biv, (byte) 0);
                IvParameterSpec iv = new IvParameterSpec(biv);

                byte[] datos = llave.getBytes("UTF-8");
                SecretKeySpec ks = new SecretKeySpec(datos, algoritmo);
                Cipher cipher = Cipher.getInstance(modoAlgoritmo);
                cipher.init(Cipher.ENCRYPT_MODE, ks, iv);
                byte[] salida = cipher.doFinal(mensaje.getBytes("UTF-8"));
                resultado = Base64.encodeBase64String(salida);
            }
        } catch (Exception e) {
            resultado = "";
            logger.error("Error al cifrar texto: {}", e.toString());
            logger.error("Error al cifrar texto", e);
        }
        return resultado;
    }

    public static String descifrar(String llave, String mensaje) {
        String resultado = "";
        try {
            if (StringUtils.isNotBlank(llave) && StringUtils.isNotEmpty(mensaje)) {
                // Mejorar la versión adjuntando el vector de inicialización
                byte[] biv = new byte[8];
                Arrays.fill(biv, (byte) 0);
                IvParameterSpec iv = new IvParameterSpec(biv);

                byte[] datos = llave.getBytes("UTF-8");
                SecretKeySpec ks = new SecretKeySpec(datos, algoritmo);
                Cipher cipher = Cipher.getInstance(modoAlgoritmo);
                cipher.init(Cipher.DECRYPT_MODE, ks, iv);
                byte[] salida = cipher.doFinal(Base64.decodeBase64(mensaje));
                resultado = new String(salida);
            }
        } catch (Exception e) {
            resultado = "";
            logger.error("Error al descifrar texto: {}", e.toString());
            logger.error("Error al descifrar texto", e);
        }
        return resultado;
    }
}
