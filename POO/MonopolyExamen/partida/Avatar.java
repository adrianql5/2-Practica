package partida;

import java.util.ArrayList;
import java.util.Random;

import monopoly.Casilla;


public class Avatar {
    
    //ATRIBUTOS
    private String id; //Identificador: una letra generada aleatoriamente.
    private String tipo; //Sombrero, Esfinge, Pelota, Coche
    private Jugador jugador; //Un jugador al que pertenece ese avatar.
    private Casilla lugar; //Los avatares se sitúan en casillas del tablero.
    private boolean movimientoAvanzado; //TRUE si el avatar está en modo de movimiento avanzado.
    private ArrayList<Avatar> avCreados;
    private int bloqueado; //Valor para casos en los que hay que bloquear algún comando en el turno


    //SECCIÓN DE CONSTRUCTORES DE AVATAR--------------------------------------------------------------------------------
    
    /**
     * Constructor principal.
     *
     * @param tipo      Tipo del avatar
     * @param jugador   Jugador al que pertenece
     * @param lugar     Lugar en el que está ubicado
     * @param avCreados Arraylist con los avatares creados (usado para crear un ID distinto a los demás)
     */
    public Avatar(String tipo, Jugador jugador, Casilla lugar, ArrayList<Avatar> avCreados) {
        this.tipo = tipo;
        this.jugador = jugador;
        this.lugar = lugar;
        this.movimientoAvanzado = false;
        this.avCreados = avCreados;
        generarId(avCreados);
        this.avCreados.add(this);
        this.bloqueado=0;
    }

    /**
     * Método que permite generar un ID para un avatar. Sólo lo usamos en esta clase (por ello es privado).
     * El ID generado será una letra mayúscula entre A y Z.
     *
     * @param avCreados Arraylist de los avatares ya creados (objetivo: evitar que se generen dos ID iguales)
     */
    private void generarId(ArrayList<Avatar> avCreados) {
        Random num = new Random();
        String ID;
        boolean repetido = true;

        while (repetido) {
            repetido = false;
            ID = String.valueOf((char) (num.nextInt(26) + 'A'));

            for (Avatar a : avCreados) {
                if (a != null && a.getId().equals(ID)) {
                    repetido = true;
                    break;  //Si uno es igual no hace falta comprobar el resto
                }
            }
            if (!repetido) {
                this.id = ID;
            }
        }
    }


    
    //SECCIÓN DE MÉTODOS ÚTILES DE AVATAR-------------------------------------------------------------------------------

    /**Método que imprime la información sobre el avatar.*/
    public void infoAvatar() {
        String str = "{\n\tID: " + this.id + "\n" +
                "\tTipo: " + this.tipo + "\n" +
                "\tJugador: " + this.jugador.getNombre() + "\n" +
                "\tCasilla: " + this.lugar.getNombre() + "\n}";

        // Imprimir directamente el string
        System.out.println(str);
    }

    /**Método para cambiar el tipo de movimiento del avatar.*/
    public void cambiarMovimiento() {
        this.movimientoAvanzado = !this.movimientoAvanzado;
    }

    /**
     * Método que permite mover a un avatar a una casilla concreta.
     * Este método no comprueba si se pasa por la Salida ni hace el ingreso correspondiente.
     * Versión 2: ya se admite que valorTirada sea un número negativo.
     * @param casillas    Array con las casillas del tablero. Es un arrayList de arrayList de casillas (uno por lado)
     * @param valorTirada Número de casillas a moverse (se llama valorTirada pero no depende de los dados siempre)
     */
    public void moverAvatar(ArrayList<ArrayList<Casilla>> casillas, int valorTirada) {
        // Obtener la posición actual del avatar
        int posicionActual = this.lugar.getPosicion();

        // Calcular la nueva posición en el tablero después de la tirada
        int nuevaPosicion;
        // Si queremos avanzar un número positivo de casillas (o un número negativo sin pasar por la Salida hacia atrás)
        if(valorTirada>=0 || posicionActual>=Math.abs(valorTirada)) {
            nuevaPosicion = (posicionActual + valorTirada) % 40;
        }
        else {
            //Nos queremos mover un número de casillas negativo (y pasamos hacia atrás por la casilla de Salida)
            nuevaPosicion = 40 + ( (posicionActual + valorTirada) % 40 );
        }

        // Eliminar el avatar de la casilla actual
        this.lugar.eliminarAvatar(this);

        // Buscar la nueva casilla en el tablero
        for (ArrayList<Casilla> lado : casillas) {
            for (Casilla casilla : lado) {
                if (casilla.getPosicion() == nuevaPosicion) {
                    this.lugar = casilla; // Actualizar la ubicación del avatar a la nueva casilla
                    break;
                }
            }
        }

        // Añadir el avatar a la nueva casilla
        this.lugar.anhadirAvatar(this);
    }

    //SECCIÓN DE GETTERS Y SETTERS DE AVATAR----------------------------------------------------------------------------
    public String getId() {
        return id;
    }
    //El id no necesita setter porque se le asigna un valor al crear el Avatar y no hay que modificarlo nunca

    public String getTipo() {
        return tipo;
    }

    public void setTipo(String tipo_avatar) {
        switch (tipo_avatar) {
            case "sombrero":
            case "esfinge":
            case "pelota":
            case "coche":
                this.tipo = tipo_avatar;
                break;
            default:
                System.out.println(tipo_avatar + " no es un tipo de avatar válido.\n");
        }
    }

    public Jugador getJugador() {
        return jugador;
    }
    
    public void setJugador(Jugador jugador_avatar) {
        this.jugador = jugador_avatar;
    }

    public Casilla getLugar() {
        return lugar;
    }

    public void setLugar(Casilla casilla_avatar) {
        this.lugar = casilla_avatar;
    }

    public boolean getMovimientoAvanzado() {
        return movimientoAvanzado;
    }

}