package cl.sebastian.isw.servicio.impl;

import cl.sebastian.isw.modelo.Mensaje;
import cl.sebastian.isw.repository.MensajeRepository;
import cl.sebastian.isw.servicio.ServicioRest;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;
import javax.annotation.Resource;
import org.apache.commons.lang3.RandomUtils;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.stereotype.Service;

/**
 *
 * @author Sebastián Salazar Molina <ssalazar@orangepeople.cl>
 */
@Service("servicioRest")
public class ServicioRestImpl implements ServicioRest, Serializable {

    @Resource(name = "mensajeRepository")
    private MensajeRepository mensajeRepository;
    private static final Logger logger = LoggerFactory.getLogger(ServicioRestImpl.class);

    @Override
    public List<Mensaje> getMensajes() {
        List<Mensaje> mensajes = new ArrayList<Mensaje>();
        try {
            mensajes = mensajeRepository.findAll();
        } catch (Exception e) {
            mensajes = new ArrayList<Mensaje>();
            logger.error("Error al obtener mensajes: {}", e.toString());
            logger.debug("Error al obtener mensajes", e);
        }
        return mensajes;
    }

    @Override
    public Mensaje getMensajeAleatoreo() {
        Mensaje mensaje = new Mensaje();
        try {
            List<Mensaje> mensajes = getMensajes();
            int total = mensajes.size();
            if (total > 0) {
                int indice = RandomUtils.nextInt(0, total - 1);
                mensaje = mensajes.get(indice);
            }
        } catch (Exception e) {
            mensaje = new Mensaje();
            logger.error("Error al obtener mensaje aleatoreo: {}", e.toString());
            logger.debug("Error al obtener mensaje aleatoreo", e);
        }
        return mensaje;
    }

}
