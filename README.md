# Proyecto C
Programacion bajo plataformas abiertas
Universidad de Costa Rica

Integrantes: 

-Alvaro Alfaro Miranda B70224

-Heiner Mauricio Obando Vega B55130

-Miguel Roberto Jimenez Tung B94104

Para este programa se utiliza la interfaz gráfica GTK, donde se utilizan botones para simular el juego conocido como Gato. El juego inicia con el turno del jugador 1, que utiliza el símbolo X y el siguiente turno es para el jugador 2 que utiliza el símbolo O. Cabe destacar que no se puede reiniciar el juego ni sobreescribir posiciones previamente ocupadas durante la partida. Por otro lado, una vez finalizado el juego, ya sea por una victoria o empate, el juego se detiene y no se pueden utilizar los botones, por lo que se deberá utilizar el botón de Salida. Este botón se puede utilizar en todo momento. 

Para compilar, debe estar ubicado en la dirección de esta carpeta en la terminal y usar los siguientes comandos:

## Para compilar:
```bash
$ gcc `pkg-config --cflags gtk+-3.0` Proyecto_C.c -o exe `pkg-config --libs gtk+-3.0`
```

## Para ejecutar:
```bash
$ ./exe
```
Esta carpeta también cuenta con un Makefile, por lo tanto, se puede compilar y ejecutar el programa de una manera más sencilla:

Para compilar, debe estar ubicado en la dirección de esta carpeta en la terminal y usar los siguientes comandos:

## Para compilar:
```bash
$ make
```
## Para ejecutar:
```bash
$ make run
```
## Para borrar el ejecutable:
```bash
$ make clean
```
Para este proyecto se utilizó la biblioteca GTK, esta viene instalada de manera previa por lo que no se necesita una instalación extra para poder utilizar este programa.
