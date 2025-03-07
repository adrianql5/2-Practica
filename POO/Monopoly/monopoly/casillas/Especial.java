package monopoly.casillas;

import monopoly.*;
import partida.*;

import partida.avatares.*;

import java.util.*;

public class Especial extends Casilla{

    private float bote;

    // ==========================
    // SECCIÓN: CONSTRUCTORES
    // ==========================
    public Especial(String nombre, int posicion){
        super(nombre,posicion);
        this.bote=0;
    }

    public void incrementarBote(float bote) {
        this.bote += bote;
    }

    public float getBote(){
        return this.bote;
    }

    public void resetBote(){
        this.bote=0;
    }


    /**Modificación del método jugadoresEnCasilla (Casilla.java) para la casilla Cárcel,
     * ya que se deben imprimir los turnos que llevan para salir o si están de visita.
     * Si no hay ningún jugador en la casilla no hace nada.
     * Nota: los imprime con salto de línea al final.
     */
    private void jugadoresEnCarcel() {

        // Obtenemos la lista de avatares que hay en la casilla cárcel (pos=10)
        ArrayList<Avatar> avataresEnCasilla = this.getAvatares();

        // Si hubiera avatares se imprimen
        if(!avataresEnCasilla.isEmpty()) {

            // Recorremos la lista de avatares y mostramos todos los jugadores en la misma línea
            Juego.consola.imprimir("\tJugadores: ");
            for (Avatar avatar : avataresEnCasilla) {
                Jugador jugador = avatar.getJugador();
                // Es diferente si está encarcelado que si está de visita
                if (jugador.isEnCarcel()) {
                    // Imprimimos el jugador que está encarcelado con el número de tiradas en la cárcel
                    Juego.consola.imprimir("[" + jugador.getNombre() + ", " + jugador.getTiradasCarcel() + "]  ");
                } else {
                    // Imprimimos el jugador que está de visita
                    Juego.consola.imprimir("[" + jugador.getNombre() + " (visita)]  ");
                }
            }
            Juego.consola.imprimir("\n");
        }
    }

    @Override
    public boolean evaluarCasilla(Tablero tablero, Jugador jugadorActual, int tirada){
        incrementarVecesVisitada();

        switch (this.nombre) {
            case "Carcel":
                Juego.consola.imprimir("Has caído en la Cárcel. Disfruta de la visita.");
                break;
            case "Parking":
                //v2: ahora el bote del Parking se guarda en Parking.valor
                Juego.consola.imprimir(String.format("Has ganado el bote del Parking: %,.0f€\n", bote));
                jugadorActual.sumarFortuna(bote);
                jugadorActual.getEstadisticas().sumarDineroRecaudadoBote(bote);
                resetBote();
                break;
            case "IrCarcel":
                Juego.consola.imprimir("Mala suerte, te vas a la cárcel.");
                Juego.consola.imprimir("Vas directamente sin pasar por la Salida ni cobrar.");

                // Obtenemos la casilla Carcel del tablero
                Especial carcel = (Especial) tablero.getCasilla(10);
                jugadorActual.encarcelar(carcel);
                break;
            case "Salida":
                Juego.consola.imprimir("Has llegado a la casilla de Salida.");
                break;
            default:
                Juego.consola.imprimir("Error en evaluarCasilla.");
                return false;
        }
        return true;
    }

    @Override
    public String infoCasilla(){
        String info = "{\n";
        info += "\tTipo: Especial\n";
        switch (this.nombre) {
            case "Carcel":
                info += String.format("{\n\tPago para salir: %,.0f€\n", Valor.SALIR_CARCEL);
                jugadoresEnCarcel();
                info += "}\n";
                return info;
            
            case "Parking":
                info+=String.format("{\n\tBote acumulado: %,.0f€\n",bote);
                break;

            case "IrCarcel":
                info+=String.format("\tSi caes vas a la carcel\n");
                break;

            case "Salida":
                info += String.format("\tPago por vuelta: %,.0f€\n", Valor.SUMA_VUELTA);
                break;
            default:
                break;
        }
        info += jugadoresEnCasilla();
        info += "}\n";
        return info;
    }

}

