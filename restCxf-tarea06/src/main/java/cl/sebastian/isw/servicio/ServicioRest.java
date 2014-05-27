package cl.sebastian.isw.servicio;

import cl.sebastian.isw.modelo.Mensaje;
import java.util.List;

/**
 *
 * @author Sebastián Salazar Molina <ssalazar@orangepeople.cl>
 */
public interface ServicioRest {

    public List<Mensaje> getMensajes();

    public Mensaje getMensajeAleatoreo();
}
