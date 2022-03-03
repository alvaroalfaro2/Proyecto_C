#include <stdio.h>
#include <gtk/gtk.h>
#include <unistd.h>

/*
Proyecto C - IE-0117
Alvaro Alfaro Miranda B70224
Heiner Mauricio Obando Vega B55130
Miguel Roberto Jimenez Tung B94104
*/

/*
El programa consiste en un juego de gato, el cual es ejecutado desde una
interfaz gráfica, esto permite al usuario elegir la posición del símbolo que le
corresponde ya sea 'X' o 'O' a través de los botones en la interfaz,
el programa puede comprobar si el jugador logró ganar tanto en posición
horizontal, vertical o diagonal de los símbolos, indica si ganó el jugador
1 ó 2 y también puede indicar si sucedió un empate. Los símbolos ya colocados
no pueden ser remplazados, indicándole al jugador que la posición está ocupada
y se le permite poner el símbolo en otro espacio.
*/

// Se declara el struct a utilizar en el programa
struct datos {
    int valor;
    GtkWidget *label;
};

// Encabezado de la funciones utilizadas
void juego(GtkWidget *widget, struct datos *datos);
void salida(GtkWidget *widget);
void victoria(int jugador, int fin, int empate, int pos[], gpointer label);

int main(int argc, char* argv[]){

    // Se inicializan los widgets a utilizar
    GtkBuilder *constructor;
    GtkWidget *ventana;
    GtkWidget *boton_1;
    GtkWidget *boton_2;
    GtkWidget *boton_3;
    GtkWidget *boton_4;
    GtkWidget *boton_5;
    GtkWidget *boton_6;
    GtkWidget *boton_7;
    GtkWidget *boton_8;
    GtkWidget *boton_9;
    GtkWidget *boton_10;

    // Se inicializa GTK
    gtk_init(&argc, &argv);

    // Se crean el constructor y se carga el archivo .glade
    constructor = gtk_builder_new_from_file("Proyecto.glade");

    // Se obtiene el widget de ventana por su ID
    ventana = GTK_WIDGET(gtk_builder_get_object(constructor, "main_window"));

    // Crea una asociación entre la señal "destroy" y la función Gtk.main_quit
    g_signal_connect(ventana, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Inicializan los struct necesarios para enviar a la función juego
    struct datos valor_1 = {
        .valor = 1,
        .label = GTK_WIDGET(gtk_builder_get_object(constructor, "label_1"))
    };
    struct datos valor_2 = {
        .valor = 2,
        .label = GTK_WIDGET(gtk_builder_get_object(constructor, "label_1"))
    };
    struct datos valor_3 = {
        .valor = 3,
        .label = GTK_WIDGET(gtk_builder_get_object(constructor, "label_1"))
    };
    struct datos valor_4 = {
        .valor = 4,
        .label = GTK_WIDGET(gtk_builder_get_object(constructor, "label_1"))
    };
    struct datos valor_5 = {
        .valor = 5,
        .label = GTK_WIDGET(gtk_builder_get_object(constructor, "label_1"))
    };
    struct datos valor_6 = {
        .valor = 6,
        .label = GTK_WIDGET(gtk_builder_get_object(constructor, "label_1"))
    };
    struct datos valor_7 = {
        .valor = 7,
        .label = GTK_WIDGET(gtk_builder_get_object(constructor, "label_1"))
    };
    struct datos valor_8 = {
        .valor = 8,
        .label = GTK_WIDGET(gtk_builder_get_object(constructor, "label_1"))
    };
    struct datos valor_9 = {
        .valor = 9,
        .label = GTK_WIDGET(gtk_builder_get_object(constructor, "label_1"))
    };

    // Se obtienen los widgets de los botones por su ID
    boton_1 = GTK_WIDGET(gtk_builder_get_object(constructor, "button_1"));
    boton_2 = GTK_WIDGET(gtk_builder_get_object(constructor, "button_2"));
    boton_3 = GTK_WIDGET(gtk_builder_get_object(constructor, "button_3"));
    boton_4 = GTK_WIDGET(gtk_builder_get_object(constructor, "button_4"));
    boton_5 = GTK_WIDGET(gtk_builder_get_object(constructor, "button_5"));
    boton_6 = GTK_WIDGET(gtk_builder_get_object(constructor, "button_6"));
    boton_7 = GTK_WIDGET(gtk_builder_get_object(constructor, "button_7"));
    boton_8 = GTK_WIDGET(gtk_builder_get_object(constructor, "button_8"));
    boton_9 = GTK_WIDGET(gtk_builder_get_object(constructor, "button_9"));
    boton_10 = GTK_WIDGET(gtk_builder_get_object(constructor, "button_10"));

    // Se crea una asociación entre los botones y la función juego
    g_signal_connect(boton_1, "clicked", G_CALLBACK(juego), &valor_1);
    g_signal_connect(boton_2, "clicked", G_CALLBACK(juego), &valor_2);
    g_signal_connect(boton_3, "clicked", G_CALLBACK(juego), &valor_3);
    g_signal_connect(boton_4, "clicked", G_CALLBACK(juego), &valor_4);
    g_signal_connect(boton_5, "clicked", G_CALLBACK(juego), &valor_5);
    g_signal_connect(boton_6, "clicked", G_CALLBACK(juego), &valor_6);
    g_signal_connect(boton_7, "clicked", G_CALLBACK(juego), &valor_7);
    g_signal_connect(boton_8, "clicked", G_CALLBACK(juego), &valor_8);
    g_signal_connect(boton_9, "clicked", G_CALLBACK(juego), &valor_9);
    g_signal_connect(boton_10, "clicked", G_CALLBACK(salida), NULL);

    // Muestra e inicia el bucle principal
    gtk_widget_show_all(ventana);
    gtk_main();
    return 0;
}

void juego(GtkWidget *widget, struct datos *datos){

    /*
    Este función lleva acabo el funcionamiento del juego, recibe valores
    a través de los botones, cambiando el signo en los botones y
    el texto del label en la interfaz gráfica según el jugador que juegue,
    revisa si hay un ganador o un empate y deja de actuar cuando una de
    las dos situaciones sucede.
    */

    /*
    Se inicializan las variables necesarias, estas son estáticas para que
    mantegan su valor aunque la función no esté trabajando
    */
    static int fin = 0; // cero es falso, 1 es verdadero
    static int empate = 0; // cero es falso, 1 es verdadero
    static int contador = 0; // Verifica si hubo un empate y quien juega
    static int pos[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
    static int indice; // Posición del símbolo
    static int senal; // Símbolo correspondiente
    static int jugador;
    static int bandera; // Comprueba si hay un ganador
    static int i;
    static int k;

    // Se comprueba si el juego finalizó
    if (fin == 1){
        return;
    } else {
        bandera = 0;
        /*
        Se verifica que jugador está colocando su símbolo, cual símbolo es
        y se muestra en el label el número del jugador, la variable y el
        texto no corresponde en el código pero el funcionamiento es correcto
        de esta manera.
        */
        if(contador % 2 == 0){
            senal = 'X';
            GtkLabel *label = (GtkLabel*) datos->label;
            gtk_label_set_text(label, "Turno del jugador 2");
            jugador = 1;
        } else {
            senal = 'O';
            GtkLabel *label = (GtkLabel*) datos->label;
            gtk_label_set_text(label, "Turno del jugador 1");
            jugador = 2;
        }

        // Se indica la posición del símbolo
        indice = datos->valor;

        // Se verifica si la posición está ocupada
        if (pos[indice-1] == 'X' || pos[indice-1] == 'O'){
            GtkLabel *label = (GtkLabel*) datos->label;
            gtk_label_set_text(label, "Posición ocupada");
            return;
        }

        // Si la posición no está ocupada se coloca el símbolo correspondiente
        pos[indice-1] = senal;

        // Se coloca en el botón el símbolo correspondiente
        if (senal == 'X'){
            GtkButton *boton = (GtkButton*) widget;
            gtk_button_set_label(boton, "X");
        } else {
            GtkButton *boton = (GtkButton*) widget;
            gtk_button_set_label(boton, "O");
        }

        /*
        Se verifica si se realizaron 9 movimientos o no para comprobar el
        empate
        */
        if(contador < 9) {
            // Este for comprueba si alguien ganó consiguiento una fila
            for(i=0; i<9; i++){
                if (i%3 == 0){
                    bandera = 0;
                }
                if (pos[i] == senal){
                    bandera++;
                }
                if (bandera == 3){
                    fin = 1;
                    empate = 0;
                    victoria(jugador, fin, empate, pos, datos->label);
                    return;
                }
            }
            // Se reinicia la bandera
            bandera = 0;
            // Este for comprueba si alguien ganó consiguiendo una columna
            for(i=0; i<3; i++){
                for(k=i; k <= i + 6; k += 3){
                    if(pos[k]==senal){
                        bandera++;
                    }
                }
                if (bandera == 3){
                    fin = 1;
                    victoria(jugador, fin, empate, pos, datos->label);
                    empate = 0;
                    return;
                }
                bandera = 0; // Se reinicia la bandera
            }
            // Este if comprueba si alguiente ganó consiguiendo una diagonal
            if((pos[0] == senal && pos[4] == senal && pos[8] == senal) ||
                (pos[2] == senal && pos[4] == senal && pos[6] == senal)) {
                fin = 1;
                empate = 0;
                victoria(jugador, fin, empate, pos, datos->label);
                return;
            }
        // Si no, se logra el empate
        } else {
            fin = 1;
            empate = 1;
            victoria(jugador, fin, empate, pos, datos->label);
            return;
        }
        contador++;
        // Otra verificación del empate
        if (contador == 9){
            fin = 1;
            empate = 1;
            victoria(jugador, fin, empate, pos, datos->label);
            return;
        }
        return;
    }
}


void victoria(int jugador, int fin, int empate, int pos[], gpointer label){
    /*
    Este función se encarga de cambiar el label y colocar en el si hubo un
    ganador y cual jugador fue, de lo contrario muestra que hubo un empate
    */

    /*
    Este if comprueba si empate es 0, de ser así comprueba cual jugador ganó
    y lo muestra en el label
    */
    if(fin == 1 && empate == 0){
        if (jugador == 1){
            GtkLabel *label_1 = (GtkLabel*) label;
            gtk_label_set_text(label_1, "Ganador: Jugador 1");
            return;
        } else {
            GtkLabel *label_1 = (GtkLabel*) label;
            gtk_label_set_text(label_1, "Ganador: Jugador 2");
            return;
        }
    } else {
        GtkLabel *label_1 = (GtkLabel*) label;
        gtk_label_set_text(label_1, "Hubo un empate");
        return;
    }
}

void salida(GtkWidget *widget){
    /*
    Esta función se encarga de cerrar el programa
    */
    exit(0);
}
