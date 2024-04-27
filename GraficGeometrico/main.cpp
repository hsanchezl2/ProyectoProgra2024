#include <iostream>
#include <vector>
#include <math.h>
#include <conio.h>
#include <windows.h>
// tamaño de pantalla
const int SCREEN_WIDTH = 50;
const int SCREEN_HEIGHT = 25;

// Matriz pantalla
std::vector<std::vector<char>> screen(SCREEN_HEIGHT, std::vector<char>(SCREEN_WIDTH, ' '));

// Cursor
int cursorX = SCREEN_WIDTH / 2;
int cursorY = SCREEN_HEIGHT / 2;

//funciones
void clearScreen();
void drawScreen();
void moveCursor(int x, int y);
void drawSquare(int x, int y, int side);
void drawRectangle(int x, int y, int base, int height);
void drawTriangle(int x, int y, int base);
void drawCircle(int x, int y, int radius);
void showMenu();
char getMenuOption();
void processMenuOption(char option);
int main() {
    char input;
    do {
        clearScreen(); // Limpiar la pantalla
        input = _getch();
        if (input == '1') {
            std::cout << " opcion 1 "<<input << std::endl;
             moveCursor(10,10);
        } else if (input == '2') { // Tecla F12
            std::cout <<"Ingresar al menu, presione " << input << std::endl;
        // Menú
        showMenu();
        input = getMenuOption();
        processMenuOption(input);
        drawScreen(); //Dibujar
        }
     }while (input != 'q'); // salir del programa

    return 0;
}

void clearScreen() {
    screen.assign(SCREEN_HEIGHT, std::vector<char>(SCREEN_WIDTH, ' '));
}

void drawScreen() {
    for (int i = 0; i < SCREEN_HEIGHT; ++i) {
        for (int j = 0; j < SCREEN_WIDTH; ++j) {
            std::cout << screen[i][j];
        }
        std::cout << std::endl;
    }
}

// Dirección del cursor
void moveCursor(int x, int y) {

    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    /*char direction;
    std::cout << " Direccion "<<direction << std::endl;
    do{
             switch(direction) {
        case 'w': // Arriba
            if (cursorY > 0) {
                --cursorY;
            }
            break;
        case 's': // Abajo
            if (cursorY < SCREEN_HEIGHT - 1) {
                ++cursorY;
            }
            break;
        case 'a': // Izquierda
            if (cursorX > 0) {
                --cursorX;
            }
            break;
        case 'd': // Derecha
            if (cursorX < SCREEN_WIDTH - 1) {
                ++cursorX;
            }
            break;
    }

    }
    while( direction != 'q'  );*/
}

void drawSquare(int x, int y, int side) {
    std::cout << "SCREEN_HEIGHT: "<<SCREEN_HEIGHT << std::endl;
    std::cout << "SCREEN_WIDTH: "<<SCREEN_WIDTH << std::endl;
    std::cout << "x : "<<x << std::endl;
    std::cout << "y : "<<y << std::endl;
    std::cout << "side : "<<side << std::endl;
    for (int i = y; i < y + side; ++i) {
        for (int j = x; j < x + side; ++j) {
            if (i >= 0 && i < SCREEN_HEIGHT && j >= 0 && j < SCREEN_WIDTH) {
                screen[i][j] = '*';
            }
        }
    }
}

void drawRectangle(int x, int y, int base, int height) {
    for (int i = y; i < y + height; ++i) {
        for (int j = x; j < x + base; ++j) {
            if (i >= 0 && i < SCREEN_HEIGHT && j >= 0 && j < SCREEN_WIDTH) {
                screen[i][j] = '*';
            }
        }
    }
}

void drawTriangle(int x, int y, int base) {
    int startX = x - base / 2;
    int endX = x + base / 2;
    for (int i = y; i >= y - base / 2; --i) {
        for (int j = startX; j <= endX; ++j) {
            if (i >= 0 && i < SCREEN_HEIGHT && j >= 0 && j < SCREEN_WIDTH) {
                screen[i][j] = '*';
            }
        }
        ++startX;
        --endX;
    }
}

void drawCircle(int x, int y, int radius) {
    for (int i = 0; i < SCREEN_HEIGHT; ++i) {
        for (int j = 0; j < SCREEN_WIDTH; ++j) {
            int dx = j - x;
            int dy = i - y;
            double distance = sqrt(dx*dx + dy*dy);
            if (distance > radius - 0.5 && distance < radius + 0.5) {
                if (i >= 0 && i < SCREEN_HEIGHT && j >= 0 && j < SCREEN_WIDTH) {
                    screen[i][j] = '*';
                }
            }
        }
    }
}

// Menú
void showMenu() {
    std::cout << "Seleccione la figura a dibujar:" << std::endl;
    std::cout << "1. Cuadrado" << std::endl;
    std::cout << "2. Rectangulo" << std::endl;
    std::cout << "3. Triangulo" << std::endl;
    std::cout << "4. Circulo" << std::endl;
    std::cout << "Presione 'q' para salir" << std::endl;
}

char getMenuOption() {
    char option;
    std::cout << "Ingrese la opción deseada: ";
    std::cin >> option;
    return option;
}

void processMenuOption(char option) {
    switch(option) {
        case '1': {
            int side;
            std::cout << "Ingrese la longitud del lado del cuadrado: ";
            std::cin >> side;
            drawSquare(cursorX, cursorY, side);
            break;
        }
        case '2': {
            int base, height;
            std::cout << "Ingrese la base del rectángulo: ";
            std::cin >> base;
            std::cout << "Ingrese la altura del rectángulo: ";
            std::cin >> height;
            drawRectangle(cursorX, cursorY, base, height);
            break;
        }
        case '3': {
            int base;
            std::cout << "Ingrese la base del triángulo: ";
            std::cin >> base;
            drawTriangle(cursorX, cursorY, base);
            break;
        }
        case '4': {
            int radius;
            std::cout << "Ingrese el radio del círculo: ";
            std::cin >> radius;
            drawCircle(cursorX, cursorY, radius);
            break;
        }
        case 'q':
            std::cout << "Saliendo del programa..." << std::endl;
            break;
        default:
            std::cout << "Opción no válida. Por favor, seleccione una opción válida." << std::endl;
            break;
    }
}
