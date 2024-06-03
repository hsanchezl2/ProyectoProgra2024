#include <iostream>
#include <conio.h>
#include <cmath>
#include <windows.h> // Para SetConsoleCursorPosition()
#include <fstream>
#include <cstdio>
#include <unistd.h>

#define GREEN   "\033[32m"
#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */

using namespace std;
void gotoxy(int x, int y);
void displayMenu(int x , int y);
void processMenu(char option,int x,int y);
void setColorCaracter(int x, int y);
void setNewCaracter(int x, int y);
void grabarPantalla();
void limpiarPantalla();

char caracter = '*';
char* color = RESET;

char opcionMenu;

//############### METODOS PARA GENEREAR LAS FIGURAS EN UNA POSICION######################################
void generarCuadrado(int lado, int x, int y,const char* color,char orientacion) {//metodo para generar un cuadado
    // Imprimir las filas del cuadrado
    int posY=0;
    int posX=0;
    if(orientacion=='i'){//Isquierda
        posX= x;
        x=x-(lado*2);
    }else if(orientacion=='a'){//ABAJO
        posY = y;
        posX = x;
        y = y+(lado*2);
        x = x -((lado*2)/2);
    }else if(orientacion=='d'){ //derecha
    }
    else if(orientacion=='A'){ // Arriba
        posX = x;
        x = x -((lado*2)/2);
    }
    for (int i = 0; i < lado; ++i) {
        // Imprimir las columnas del cuadrado
        for (int j = 0; j < lado; ++j) {
                gotoxy(x+2*j,y+i);
            std::cout<<color << caracter<<" ";
        }
        std::cout << std::endl;
    }
    char tecla = _getch();
    if(orientacion=='i'){
        x = posX;
    }else if(orientacion=='a'||orientacion=='A'){
        x = posX;
    }

    displayMenu(x,y+(lado+2));
}

void generarRectangulo(int altura, int base,int x,int y, const char* color,char orientacion) {
    int posX = 0;
    int posY = 0;
    if(orientacion=='a'){
        posY=y;
        y = y+altura;
    }

    // Imprimir las filas del rectángulo
    for (int i = 0; i < altura; ++i) {
        // Imprimir las columnas del rectángulo
        for (int j = 0; j < base; ++j) {
             gotoxy(x+2*j,y+i);
            std::cout<<color <<caracter<<" ";
        }
        std::cout <<color<< std::endl;
    }

    displayMenu(x,y+(altura+2));
}

void generarTriangulo(int base,int x, int y ,const char* color,char orientacion) {
    // Imprimir las filas del triángulo
    //int k = 1;
            int posX=0;
    if(orientacion=='d' || orientacion=='A'){
       if( orientacion=='A'){
         for (int i = 1; i <= base; ++i) {
        // Imprimir los espacios en blanco antes de los asteriscos
         // Imprimir los asteriscos
            for (int k = 1; k <= 2 * i - 1; ++k) {
                posX=k;
            }
        }
        x=x-(posX/2);
        posX = (posX/2);
       }
     for (int i = 1; i <= base; ++i) {
        // Imprimir los espacios en blanco antes de los asteriscos
        for (int j = 1; j <= base - i; ++j) {
            gotoxy(x+j,y+i);
            std::cout << " ";
        }
        // Imprimir los asteriscos
        for (int k = 1; k <= 2 * i - 1; ++k) {
            if(i==base){
                gotoxy(x+k,y+i);
            }
            std::cout<<color<< caracter;
        }
        //gotoxy(x,y);
        std::cout << std::endl;
        }
    }else if(orientacion=='i'){

          for (int i = 1; i <= base; ++i) {
        // Imprimir los espacios en blanco antes de los asteriscos
         // Imprimir los asteriscos
            for (int k = 1; k <= 2 * i - 1; ++k) {
                posX=k;
            }
        }
        x=x-posX;
        for (int i = 1; i <= base; ++i) {
        // Imprimir los espacios en blanco antes de los asteriscos
         // Imprimir los asteriscos
        for (int j = 1; j <= base - i; ++j) {
            gotoxy(x+j,y+i);
            std::cout << " ";
        }

        // Imprimir los asteriscos
        for (int k = 1; k <= 2 * i - 1; ++k) {
            if(i==base){
                gotoxy(x+k,y+i);
            }

            std::cout<<color<< caracter;
        }
        //gotoxy(x,y);
        std::cout << std::endl;
        }
    }else if(orientacion=='a'){
          for (int i = 1; i <= base; ++i) {
        // Imprimir los espacios en blanco antes de los asteriscos
         // Imprimir los asteriscos
            for (int k = 1; k <= 2 * i - 1; ++k) {
                posX=k;
            }
        }
        x=x-(posX/2);
        y= y+base;
         for (int i = 1; i <= base; ++i) {
        // Imprimir los espacios en blanco antes de los asteriscos
         // Imprimir los asteriscos
        for (int j = 1; j <= base - i; ++j) {
            gotoxy(x+j,y+i);
            std::cout << " ";
        }

        // Imprimir los asteriscos
        for (int k = 1; k <= 2 * i - 1; ++k) {
            if(i==base){
                gotoxy(x+k,y+i);
            }

            std::cout<<color<< caracter;
        }
        //gotoxy(x,y);
        std::cout << std::endl;
        }
        posX = (posX/2);
    }

    char tecla = _getch();
    displayMenu(x+posX,y+(base+2));
}

void generarCirculo(int radio, int x, int y,const char* color, char orientacion) {
    // Definir el centro del círculo
    int centroX = radio + x;
    int centroY = radio + y;
    int posiX = x;
    int posiY = y;
    int radiotem;

     if(orientacion == 'i') {
        radiotem = radio * 2;
        x = x - radiotem;
     }
    else if (orientacion == 'a'){
        radiotem = radio * 2;
        y = y + radiotem;
     }

     else if (orientacion == 'A'){
         radiotem = radio;
        x = x - radiotem;
     }

    // Iterar sobre cada punto dentro de un cuadrado que rodea al círculo
    for (int posY = 0; posY <= 2 * radio; ++posY) {
        for (int posX = 0; posX <= 2 * radio; ++posX) {
            // Calcular la distancia entre el punto actual y el centro del círculo
            double distanciaAlCentro = sqrt((posX - radio) * (posX - radio) + (posY - radio) * (posY - radio));

            // Si la distancia es aproximadamente igual al radio, imprimir un asterisco,
            // lo que significa que estamos cerca del borde del círculo
            if (fabs(distanciaAlCentro - radio) < 0.5) {
                gotoxy(posX + x, posY + y);
                std::cout<<color <<caracter<< " ";
            }
        }
    }
    char tecla = _getch();
    displayMenu(posiX,y+radio+10);
}

void generarTrianguloR(int base,int x, int y ,const char* color, char orientacion) {

    // Imprimir las filas del triángulo
    //int k = 1;
    int posiX=x;
    int posiY=y;

    if (orientacion == 'i'){
    for (int i = 1; i <= base; ++i) {
        // Imprimir los espacios en blanco antes de los asteriscos
         // Imprimir los asteriscos
            for (int k = 1; k <= 2 * i - 1; ++k) {
                posiX=k;
            }
        }
        x= x-posiX;

    }
    else if (orientacion == 'a'){
             y= y + base;

            }

    else if (orientacion == 'A'){
    for (int i = 1; i <= base; ++i) {
        // Imprimir los espacios en blanco antes de los asteriscos
         // Imprimir los asteriscos
            for (int k = 1; k <= 2 * i - 1; ++k) {
                posiX=k;
            }
        }
        x= x-posiX/2;

    }

    for (int i = 1; i <= base; ++i) {
        // Imprimir los espacios en blanco antes de los asteriscos
        for (int j = 1; j <= base - i; ++j) {
            gotoxy(x+j,y+i);
            std::cout << " ";
        }
        // Imprimir los asteriscos
        for (int k = 1; k <= 2 * i - 1; ++k) {
            if(i==base){
                gotoxy(x+k,y+i);
            }
            std::cout<<color<<caracter;
        }
        //gotoxy(x,y);
        std::cout << std::endl;
    }
}

void generarTrianguloI(int base, int x, int y,const char* color, char orientacion){

    int posiX=x;

    if (orientacion == 'i'){
    for (int i = 1; i <= base; ++i) {
        // Imprimir los espacios en blanco antes de los asteriscos
         // Imprimir los asteriscos
            for (int k = 1; k <= 2 * i - 1; ++k) {
                posiX=k;
            }
        }
        x= x-posiX;

    }
    else if (orientacion == 'a'){
             y= y + base;

    }

    else if (orientacion == 'A'){
    for (int i = 1; i <= base; ++i) {
        // Imprimir los espacios en blanco antes de los asteriscos
         // Imprimir los asteriscos
            for (int k = 1; k <= 2 * i - 1; ++k) {
                posiX=k;
            }
        }
        x= x-posiX/2;

    }

    // Imprimir las filas del triángulo
    for (int i = base; i >= 1; --i) {
        // Imprimir los espacios en blanco antes de los asteriscos
        for (int j = 1; j <= base - i; ++j) {
            gotoxy(x + j, y + (base - i));
            std::cout << " ";
        }
        // Imprimir los asteriscos
        for (int k = 1; k <= 2 * i - 1; ++k) {
            gotoxy(x + k + (base - i), y + (base - i));
            std::cout<<color << caracter;
        }
        std::cout << std::endl;
    }
    char tecla = _getch();
    displayMenu(posiX,y+(base*2));
}


void generarRombo(int lado, int posX, int posY, const char* color, char orientacion) {
    int posiX = posX;
    int posiY = posY;

    // Generar el triángulo superior del rombo
    generarTrianguloR(lado,posX,posY,color, orientacion);
    generarTrianguloI(lado, posX, posY+lado,color, orientacion);

    }


void generarHexagono(int lado, int posX, int posY,const char* color,char orientacion) {
    // Definir el centro del hexágono
    int centroX = posX+4;
    int centroY = posY+4;

    // Calcular la altura del triángulo equilátero que forma cada lado del hexágono
    double altura = sqrt(3) * lado;

    // Calcular los vértices del hexágono
    int verticesX[6], verticesY[6];



    for (int i = 0; i < 6; ++i) {
        double angulo = M_PI / 3 * i; // Ángulo en radianes
        verticesX[i] = round(centroX + lado * cos(angulo));
        verticesY[i] = round(centroY + lado * sin(angulo));
    }

    // Dibujar el hexágono utilizando líneas
    for (int i = 0; i < 6; ++i) {
        int j = (i + 1) % 6; // Índice del siguiente vértice
        // Dibujar una línea desde el vértice i al vértice j
        if(orientacion == 'i'){
            gotoxy(verticesX[i]-lado*2, verticesY[i]);
        }else if(orientacion == 'a'){
            gotoxy(verticesX[i], verticesY[i]+lado);
        }else if(orientacion == 'd'){
            gotoxy(verticesX[i], verticesY[i]);
        }else if(orientacion == 'A'){
            gotoxy(verticesX[i]-lado/2, verticesY[i]);
        }

        //ffffffgotoxy(verticesX[i], verticesY[i]);
        std::cout<<color << caracter; // Se puede utilizar cualquier carácter para representar los vértices
        if(orientacion == 'i'){
            gotoxy(verticesX[j]-lado*2, verticesY[j]);
        }else if(orientacion == 'a'){
            gotoxy(verticesX[j], verticesY[j]+lado);
        }else if(orientacion == 'd'){
            gotoxy(verticesX[j], verticesY[j]);
        }else if(orientacion == 'A'){
            gotoxy(verticesX[j]-lado/2, verticesY[j]);
        }

        std::cout<<color << caracter; // Se puede utilizar cualquier carácter para representar los vértices
    }
     char tecla = _getch();
    displayMenu(posX, posY+(lado*2));
}

void generarLinea(int longitud, int x, int y, const char* color,char orientacion ){
    int posX =x;
    int posY =y;
    if(orientacion=='i'){//izquierda
        x = x-longitud;
    }else if(orientacion =='a'){//abajo
        y = y+longitud;
        x = x-(longitud/2);
        posY =y;
    }else if( orientacion == 'A' ){// arriba
        x = x-(longitud/2);
    }else if( orientacion=='d' ){ // la figura se muestra a la derecha por defecto

    }


    if (longitud > 0) {
        for (int i = 0; i < longitud; ++i) {
                 gotoxy(x+i, y);
            std::cout<< color<< caracter;
        }
        std::cout << std::endl; // Salto de línea al final de la línea generada
    } else {
        std::cout << "La longitud debe ser mayor que 0." << std::endl;
    }

     char tecla = _getch();
    displayMenu(posX, posY+2 );
}
//#########################################################################################################
// Función para mover el cursor a una posición específica en la consola
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
int main()
{
    int x = 0, y = 0; // Posición inicial del cursor
    bool posicion = true;
    while (posicion) {
        // Borra la pantalla
        system("cls");
        // Muestra el cursor en la posición actual
        gotoxy(x, y);
        std::cout << "|";

        // Imprime el cursor en la posición actual
        //std::cout << "Posicion del cursor: X=" << x << ", Y=" << y << std::endl;

        // Espera a que se presione una tecla
        while (!_kbhit());

        // Obtiene la tecla presionada
        char tecla = _getch();

        // Mueve el cursor según la tecla presionada
        switch (tecla) {
            case 'w':
                y--;
                break;
            case 's':
                y++;
                break;
            case 'a':
                x--;
                break;
            case 'd':
                x++;
                break;
            default:
                posicion = false;
                break;
        }
    }
    //Console::SetCursorPosition(x,y);
    //gotoxy(x,y);
    //generarCuadrado(4,x,y); ya funciona
    //generarTriangulo(8,x,y);
    //generarRectangulo(5,8,x,y,color);
    //generarCirculo(4,x,y);
    //generarRombo(5, x, y,color);


    displayMenu(x,y);
    return 0;
}

void displayMenu(int x, int y) {
    //system("cls");
    char* colorMenu = RESET;
    gotoxy(x,y);
    cout << colorMenu<<"Seleccione una opcion:" << endl;
    gotoxy(x,y+1);
    cout <<colorMenu<< "F1 - Triangulo equilatero" << endl;
    gotoxy(x,y+2);
    cout << colorMenu<<"F2 - Cuadrado" << endl;
    gotoxy(x,y+3);
    cout << colorMenu<<"F3 - Rectangulo" << endl;
    gotoxy(x,y+4);
    cout << colorMenu<<"F4 - Circulo" << endl;
    gotoxy(x,y+5);
    cout << colorMenu<<"F5 - Linea" << endl;
    gotoxy(x,y+6);
    cout << colorMenu<<"F6 - Rombo" << endl;
    gotoxy(x,y+7);
    cout << colorMenu<<"F7 - Hexagono" << endl;
    gotoxy(x,y+8);
    cout << colorMenu<<"F8 - Nuevo Caracter" << endl;
    gotoxy(x,y+9);
    cout << colorMenu<<"F9 - Limpiar Pantalla" << endl;
    gotoxy(x,y+10);
    cout << colorMenu<<"F10 - Color de Caracter" << endl;
    gotoxy(x,y+11);
    cout << colorMenu<<"F12 - Grabar Pantalla" << endl;
    gotoxy(x,y+12);
    cout << colorMenu<<"Ctrl + A - Abrir archivo y mostrar en pantalla" << endl;
    gotoxy(x,y+13);
    char tecla = _getch();
    opcionMenu = tecla;
    cout << "tecla precionada:"<< tecla << endl;
    processMenu(tecla,x,y+15);

}
void processMenu(char option,int x,int y) {
    int numGrafica;
    char orientacion;
    switch (option) {
        case '1': // Triangulo
            gotoxy(x,y);
            cout << "Ingrese la base del triángulo" << endl;
            gotoxy(x,y+1);
            cin>>numGrafica;

            gotoxy(x,y+2);
            cout << "Ingrese la orientacion del triangulo:" << endl;
            gotoxy(x,y+3);
            cin>>orientacion;
            generarTriangulo(numGrafica,x,y+4,color,orientacion); // Ejemplo: base de tamaño 5
            break;
        case '2': // Cuadrado
            //drawSquare(5); // Ejemplo: lado de tamaño 5
            gotoxy(x,y);
            cout << "Ingrese El tamaño del Cuadrado" << endl;
            gotoxy(x,y+1);
            cin>>numGrafica;
             gotoxy(x,y+2);
            cout << "Ingrese la orientacion del Cuadrado" << endl;
             gotoxy(x,y+3);
            cin>>orientacion;
            generarCuadrado(numGrafica,x,y+4,color,orientacion);
            break;
        case '3': // Rectangulo
            //drawRectangle(6, 3); // Ejemplo: base de tamaño 6 y altura de tamaño 3
            gotoxy(x,y);
            int base;
            int altura;
            cout << "Ingrese la altura del Rectangulo" << endl;
            gotoxy(x,y+1);
            cin>>base;

            gotoxy(x,y+2);
            cout << "Ingrese la base del Rectangulo" << endl;
            gotoxy(x,y+3);
            cin>>altura;

            gotoxy(x,y+4);
            cout << "Ingrese la orientacion" << endl;
            gotoxy(x,y+5);
            cin>>orientacion;
            generarRectangulo(base,altura,x,y+7,color,orientacion);
            break;
        case '4': // Circulo
            //drawCircle(4); // Ejemplo: radio de tamaño 4
            gotoxy(x,y);
            int radio;
            cout << "Ingrese el Radio del circulo" << endl;
            gotoxy(x,y+1);
            cin>>radio;
            gotoxy(x,y+2);
            cout << "Ingrese la orientacion" << endl;
            gotoxy(x,y+3);
            cin>>orientacion;
            generarCirculo(radio,x,y+4,color,orientacion);

            break;
        case '5': // Linea
            //drawLine(7, 'r'); // Ejemplo: longitud de 7 hacia la derecha
            gotoxy(x,y);
            cout << "Ingrese la longitud de la linea." << endl;
            gotoxy(x,y+1);
            cin>>numGrafica;
            gotoxy(x,y+2);
            cout << "Ingrese la orientacion de la linea." << endl;
            gotoxy(x,y+3);
            cin>>orientacion;
            generarLinea(numGrafica,x,y+4,color,orientacion);
            break;
        case '6': // Rombo
            //drawDiamond(7); // Ejemplo: lado de tamaño 7
            gotoxy(x,y);
            cout << "Ingrese la longitud del Rombo" << endl;
            gotoxy(x,y+1);
            cin>>numGrafica;
            gotoxy(x,y);
            cout << "Ingrese la orientacion" << endl;
            gotoxy(x,y+1);
            cin>>orientacion;
            generarRombo(numGrafica,x,y+3,color, orientacion);
            break;
        case '7': // Hexagono4
            //drawHexagon(7, 'v'); // Ejemplo: lado de tamaño 7 con orientación vertical
            gotoxy(x,y);
            cout << "Ingrese la longitud del Hexagono" << endl;
            gotoxy(x,y+1);
            cin>>numGrafica;
             gotoxy(x,y+2);
            cout << "Ingrese la orientacion" << endl;
            gotoxy(x,y+3);
            cin>>orientacion;
            generarHexagono(numGrafica,x,y+4,color,orientacion);
            break;
        case '8': // Nuevo Caracter
            setNewCaracter(x,y);
            //CURSOR_CHAR = newChar;
            break;
        case '9': // Limpiar Pantalla
            //clearScreen();
                limpiarPantalla();
            break;
        case '0': // Color de Caracter
            // Implementar la funcionalidad para cambiar el color del carácter
            setColorCaracter( x, y+1);
            break;
        case 'a': // Grabar Pantalla
            // Implementar la funcionalidad para grabar la pantalla en un archivo
            break;
        case 'b': // Abrir archivo
            // Implementar la funcionalidad para abrir un archivo y mostrarlo en pantalla
            break;
        default:
            cout << "Opcion no valida." << endl;
    }
}
void setColorCaracter(int x, int y){
     cout << "Seleccione un color " << endl;
    gotoxy(x,y+1);
    cout << "1 - GREEN" << endl;
    gotoxy(x,y+2);
    cout << "2 - RED" << endl;
    gotoxy(x,y+3);
    cout << "3 - YELLOW" << endl;
    gotoxy(x,y+4);
    cout << "4 - BLUE" << endl;
    gotoxy(x,y+5);
    cout << "5 - MAGENTA" << endl;
    gotoxy(x,y+6);
    cout << "6 - CYAN" << endl;
    gotoxy(x,y+7);
    cout << "7 - WHITE" << endl;
    gotoxy(x,y+8);
    cout << "8 - RESET" << endl;

    char option = _getch();
    if(option=='1'){
        color = GREEN;
        displayMenu( x,  y+9);
    }else if(option=='2'){
        color = RED;
        displayMenu( x,  y+9);
    }else if(option=='3'){
        color = YELLOW;
        displayMenu( x,  y+9);
    }else if(option=='4'){
        color = BLUE;
        displayMenu( x,  y+9);
    }else if(option=='5'){
        color = MAGENTA;
        displayMenu( x,  y+9);
    }else if(option=='6'){
        color = CYAN;
        displayMenu( x,  y+9);
    }else if(option=='7'){
        color = WHITE;
        displayMenu( x,  y+9);
    }else if(option=='8'){
        color = RESET;
        displayMenu( x,  y+9);
    }

}

void setNewCaracter(int x, int y){
     char* colorMenu = RESET;
    gotoxy(x,y);
    cout << colorMenu<<"Ingrese el nuevo carcater: " << endl;
    char newCaracter = _getch();
    cout << "El nuevo carcater es: "<< newCaracter << endl;
    caracter = newCaracter;
    displayMenu(x,y+2);
}

void grabarPantalla(){
   // Nombre del archivo donde se almacenará la salida
    const char* nombreArchivo = "salida.txt";

    // Redirigir la salida estándar hacia el archivo
    freopen(nombreArchivo, "w", stdout);

    // Ahora, cualquier cosa que se imprima en la consola se almacenará en el archivo

    std::cout << "Hola, esto se guardará en el archivo." << std::endl;

    // No cierres la redirección aquí

    // std::cout seguirá redirigido al archivo después de este punto

    // Imprime un mensaje final que se mostrará en la consola
    std::cout << "La salida ha sido redirigida al archivo '" << nombreArchivo << "'" << std::endl;

    // Cerrar la redirección
    fclose(stdout);
}

void limpiarPantalla(){
    system("cls");
    caracter = '*';
    color = RESET;
    gotoxy(1,1);
    main();
}
