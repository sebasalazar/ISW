package cl.sebastian.isw.utils;

import java.io.Serializable;
import javax.servlet.http.HttpServletRequest;
import org.apache.cxf.message.Message;
import org.apache.cxf.phase.PhaseInterceptorChain;
import org.apache.cxf.transport.http.AbstractHTTPDestination;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 *
 * @author Sebastián Salazar Molina <sebasalazar@gmail.com>
 */
public abstract class RestUtils implements Serializable  {
    private static final Logger logger = LoggerFactory.getLogger(RestUtils.class);

    public static String getIp() {
        String ip = "error";
        try {
            Message message = PhaseInterceptorChain.getCurrentMessage();
            if (message != null) {
                HttpServletRequest request = (HttpServletRequest) message.get(AbstractHTTPDestination.HTTP_REQUEST);
                if (request != null) {
                    ip = request.getRemoteAddr();
                } else {
                    logger.error("Request NULO");
                }
            } else {
                logger.error("message NULO");
            }
        } catch (Exception e) {
            ip = "error";
            logger.error(e.toString());
            logger.debug("Error al obtener Ip", e);
        }

        return ip;
    }
}
