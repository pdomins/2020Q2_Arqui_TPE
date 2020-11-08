# 2020Q2_Arqui_TPE

## Autores:                                                   
-Arce Doncella , Julian Francisco 60509                         
-Domingues, Paula Andrea 60148                                
-Lombardi, Matias Federico 60527                               

# Manual de Usuario


## Índice 

Introducción                                          
Funciones de la Shell                                 
Funciones del Ajedrez: Funciones Básicas              
Funciones del Ajedrez: Funciones In-Game              
Requisitos Mínimos                                    
Ejecución del Programa                                 
Syscalls                                               


## Introducción

Este documento contiene un manual básico respecto de los comandos ofrecidos al usuario para desenvolverse en la terminal. A continuación, se presentarán las distintas instrucciones implementadas con sus respectivas funcionalidades, junto con un ejemplo de uso. <br>
Previo a la lectura de este manual, se insta a tomar en consideración que al momento de bootear el kernel se desplegará un intérprete de comandos o Shell en donde se podrán insertar los comandos correspondientes.

## Funciones de la Shell
El usuario cuenta con nueve comandos que se le permiten ejecutar desde la terminal.  Para ejecutar los mismos simplemente se debe escribir en ella el comando deseado y presionar la tecla “ENTER”.<br>

*about*: Imprime por salida estándar información sobre el Sistema Operativo y sus desarrolladores.<br>
*help*: Imprime por salida estándar un menú con las distintas opciones útiles para el usuario.<br>
*time*: Imprime por salida estándar el horario local, en formato DD/MM/AA HH:MM:SS.<br>
*infoReg*: Para el correcto funcionamiento de este comando es necesario haber ejecutado, previo a la llamada al mismo, la combinación de teclas “CTRL+S”. De esta forma, se genera un snapshot de los registros en este preciso instante. Luego, al ejecutar el comando infoReg, los mismos se despliegan por salida estándar. <br>
*printMem*: Recibe como argumento una posición de memoria en formato Hexadecimal  e imprime por salida estándar los primeros 32 bytes a partir de la dirección recibida. 
*clear*: Limpia la pantalla de la terminal activa.<br>
*exceptionZ*: Arroja una excepción de división por cero. Subsecuentemente, imprime en pantalla el respectivo mensaje de error y el valor de los registros al momento que ocurrió la misma, incluidos entre ellos el Instruction Pointer.  <br>
*exceptionOP*: Al igual que exceptionZ, arroja una excepción por código de operación invalido e imprime su información correspondiente.<br>
chess: Inicia la ejecución de un juego de ajedrez. En el apartado siguiente se explicarán las funcionalidades del mismo en mayor detalle.<br>

## Funciones del Chess
Al igual que las funciones de Shell, las funciones básicas del ajedrez son comandos ejecutables desde terminal. Se comportan del mismo modo que las anteriormente mencionadas. <br>

*chess start o new*: Inicia una nueva partida de ajedrez. En el caso que hubiera un juego previo en pausa, este se reinicia. También es compatible con la instrucción chess -s, chess -n, o simplemente chess.<br>
*chess resume o continue*: Reanuda la partida de ajedrez en el estado previo a la pausa realizada. Acordemente, chess -r o chess -c.<br>
*chess menu o help*: Despliega un menú con las distintas opciones implementadas para el juego. Se puede ingresar también como chess -m o chess -h.<br>
*chess info*: Imprime, en el caso que hubiera una partida en pausa, el estado en el que se encuentra la misma. Se distingue de qué jugador es el turno y los tiempos acordes a los mismos. Compatible con chess -i.<br>

### Funciones In-Game
Una vez iniciado el juego, mediante su respectivo comando básico antes  mencionado, se desplegará un tablero de ajedrez, con las piezas y timers necesarios. A partir de aquí, es requerido que el usuario ingrese la jugada que desea llevar a cabo, utilizando una notación específica del ajedrez, en la cual primero se declara en qué posición se encuentra la pieza que se desea mover y luego hacia qué coordenada se desea mover. Por ejemplo, en el caso que se quiera mover el peón que se encuentra en la posición c2  hacia la posición c4, debería ingresarse el comando <br>
      $ c2c4<br>
Una vez que el movimiento se haya realizado, se desplegará en el costado derecho un log con las jugadas de cada contrincante. <br>
    Movimientos como enroques, promoción de peones y peón al paso han sido implementados adicionalmente a los movimientos básicos de las piezas. <br>
A diferencia de las funciones regulares de ajedrez, los siguientes comandos están destinados para ser ejecutados una vez iniciado el juego. No es necesario presionar “ENTER” en caso de requerir los mismos:<br>
‘R’: Permite rotar 90 grados el tablero de ajedrez. <br>
‘P’: Produce una pausa en el juego, luego, retorna a la Shell.<br>
‘Q’: Finaliza la ejecución del juego y retorna a la Shell. <br>


## Requisitos Mínimos 
Previo a obtener un archivo ejecutable, es necesario realizar una compilación del código que se pone a disposición. Para poder compilar correctamente, se debe contar con una computadora que cuente con Docker, el cual será requerido al momento de compilación y que a su vez debe contar con la imagen proveída por la cátedra y QEMU, requerido al momento de ejecución.<br>
Asimismo, para poder ejecutar correctamente el emulador de procesadores, es requisito contar con una computadora con por lo menos un CPU de 64-bits, sea Intel o AMD (o cualquier otro que utilice la arquitectura x86-64) y como mínimo 2 MB de RAM.  <br>

## Ejecución del Programa
Dentro del contenedor de Docker mencionado anteriormente:<br>
Dentro de la carpeta Toolchain, ejecutar el comando make all.<br>
Dentro de la carpeta principal, ejecutar el comando make all.<br>
Ejecutar el comando ./run.sh<br>
A continuación, se desplegará la Shell comentada anteriormente y se podrá ejecutar cualquiera de los comandos mencionados.<br>

## Syscalls 
A continuación, se encuentra un cuadro de las syscalls provistas al usuario.<br>

| Number | Syscall Name | %rdi |     %rsi     |      %rdx      |  %r10   |  %r8    |   %r9   |
|--------|--------------|------|--------------|----------------|---------|---------|---------|
|   0    |     read     | 0x00 |  int length  |  char* toRead  |    -    |    -    |    -    |
|   1    |     write    | 0x01 |  int length  |  char* toWrite | int row | int col |int color|
|   2    |     draw     | 0x02 |  int* matrix |    int row     | int col | int row | int cols|
|   3    |     clear    | 0x03 |      -       |        -       |    -    |    -    |    -    |
|   8    |    infoReg   | 0x08 |  int length  |        -       |    -    |    -    |    -    |
|   9    |    memDump   | 0x09 |  int length  |   char* dump   |    -    |    -    |    -    |
|   10   |     time     | 0x0A |  int length  |        -       |    -    |    -    |    -    |
|   11   |    setAlarm  | 0x0B |  int length  |uint64_t enabled|    -    |    -    |    -    |
|   12   | screenHeight | 0x0C |      -       |        -       |    -    |    -    |    -    |
|   13   | screenWidth  | 0x0D |      -       |        -       |    -    |    -    |    -    |



