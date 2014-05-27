BEGIN TRANSACTION;

DROP TABLE IF EXISTS mensajes CASCADE;
CREATE TABLE mensajes (
    pk bigserial NOT NULL,
    fecha timestamp NOT NULL DEFAULT NOW(),
    mensaje text,
    largo bigint DEFAULT '0',
    PRIMARY KEY (pk)
);

INSERT INTO mensajes (mensaje) VALUES ('Rendirse es lo que mata a las personas. Es sólo cuando se resisten a rendirse a pesar de todo lo demás, que ellos obtienen el derecho de caminar por la noble senda de la humanidad.');
INSERT INTO mensajes (mensaje) VALUES ('Es un error capital el teorizar antes de poseer datos. Insensiblemente, uno comienza a deformar los hechos para hacerlos encajar en las teorías en lugar de encajar las teorías en los hechos');
INSERT INTO mensajes (mensaje) VALUES ('Lo que un hombre puede inventar, otro lo puede descubrir');
INSERT INTO mensajes (mensaje) VALUES ('Es un error capital el teorizar antes de poseer datos. Insensiblemente, uno comienza a deformar los hechos para hacerlos encajar en las teorías en lugar de encajar las teorías en los hechos');
INSERT INTO mensajes (mensaje) VALUES ('Nada aclara tanto un caso como exponérselo a otra persona');
INSERT INTO mensajes (mensaje) VALUES ('Cuando todo aquello que es imposible ha sido eliminado, lo que quede, por muy improbable que parezca, es la verdad');
INSERT INTO mensajes (mensaje) VALUES ('Nada resulta más engañoso que un hecho evidente');
INSERT INTO mensajes (mensaje) VALUES ('Un tonto encuentra siempre otro más tonto que lo admira');
INSERT INTO mensajes (mensaje) VALUES ('Las facultades se agudizan cuando las dejas con hambre');
INSERT INTO mensajes (mensaje) VALUES ('Datos, datos, datos. No puedo fabricar ladrillos sin arcilla');
INSERT INTO mensajes (mensaje) VALUES ('Cuando no hay humildad, las personas se degradan.');
INSERT INTO mensajes (mensaje) VALUES ('Lo más razonable que se ha dicho sobre el matrimonio y sobre el celibato es esto: hagas lo que hagas te arrepentirás.');

UPDATE mensajes SET largo = length(mensaje);
COMMIT;
