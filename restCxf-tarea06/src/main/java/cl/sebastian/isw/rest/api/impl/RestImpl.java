package cl.sebastian.isw.rest.api.impl;

import cl.sebastian.isw.modelo.Mensaje;
import cl.sebastian.isw.rest.api.Rest;
import cl.sebastian.isw.servicio.ServicioRest;
import cl.sebastian.isw.utils.SecurityUtils;
import java.io.Serializable;
import javax.annotation.Resource;
import javax.ws.rs.Consumes;
import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.ws.rs.Produces;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;
import org.apache.commons.lang3.StringUtils;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 *
 * @author Sebastián Salazar Molina <ssalazar@orangepeople.cl>
 */
@Produces({MediaType.APPLICATION_JSON + "; charset=UTF-8", MediaType.APPLICATION_XML})
@Consumes({MediaType.APPLICATION_JSON, MediaType.APPLICATION_XML})
public class RestImpl implements Rest, Serializable {

    @Resource(name = "servicioRest")
    private ServicioRest servicioRest;
    private static final Logger logger = LoggerFactory.getLogger(RestImpl.class);

    @Override
    @GET
    @Path("/mensajeCifrado")
    public Response mensajeCifrado() {
        Mensaje mensaje = new Mensaje();
        try {
            Mensaje mensajeAleatoreo = servicioRest.getMensajeAleatoreo();
            String cifrado = SecurityUtils.cifrar("isw", mensajeAleatoreo.getMensaje());
            mensaje.setMensaje(cifrado);
            mensaje.setLargo((long) StringUtils.length(cifrado));
        } catch (Exception e) {
            mensaje = new Mensaje();
            logger.error("Error en el mensaje Cifrado: {}", e.toString());
            logger.debug("Error en el mensaje Cifrado", e);
        }
        return Response.ok(mensaje).build();
    }
}
