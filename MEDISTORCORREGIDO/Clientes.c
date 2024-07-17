#include <stdio.h>
#include <string.h>
#include "Prototipos.h"

int validacion(char cedula[]);
int cedula_repetida(char cedula[], FILE *archivo);

void Ingresar_Cliente(char nombre[MAXIMO],char cedula[MAX_CI]) {
    FILE *archivo = fopen("cedulas.txt", "a+");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo\n");
        return;
    }

    printf("Ingrese el nombre: ");
    scanf("%s", nombre);

    do {
        printf("Ingrese la cedula: ");
        scanf("%10s", cedula);
    } while (!validacion(cedula) || cedula_repetida(cedula, archivo));

    fprintf(archivo, "%-20s  %s\n", nombre, cedula);
    fclose(archivo);
}

int validacion(char cedula[]) {
    if (strlen(cedula) != 10) {
        printf("Esta cedula tiene menos de 10 digitos\n");
        return 0;
    }

    int digito_region = (cedula[0] - '0') * 10 + (cedula[1] - '0');

    if (digito_region < 1 || digito_region > 24) {
        printf("Esta cedula no pertenece a ninguna region\n");
        return 0;
    }

    int ultimo_digito = cedula[9] - '0';

    int pares = (cedula[1] - '0') + (cedula[3] - '0') + (cedula[5] - '0') + (cedula[7] - '0');

    int impares = 0;
    int numeros[5];
    numeros[0] = (cedula[0] - '0');
    numeros[1] = (cedula[2] - '0');
    numeros[2] = (cedula[4] - '0');
    numeros[3] = (cedula[6] - '0');
    numeros[4] = (cedula[8] - '0');

    for (int i = 0; i < 5; i++) {
        numeros[i] *= 2;
        if (numeros[i] > 9) {
            numeros[i] -= 9;
        }
        impares += numeros[i];
    }

    int suma_total = pares + impares;

    int primer_digito_suma = suma_total / 10;

    int decena = (primer_digito_suma + 1) * 10;

    int digito_validador = decena - suma_total;

    if (digito_validador == 10) {
        digito_validador = 0;
    }

    if (digito_validador == ultimo_digito) {
        printf("La cedula: %s es correcta\n", cedula);
        return 1;
    } else {
        printf("La cedula: %s es incorrecta\n", cedula);
        return 0;
    }
}


int cedula_repetida(char cedula[], FILE *archivo) {
    char linea[150];

    rewind(archivo);

    while (fgets(linea, sizeof(linea), archivo)) {
        char temp_cedula[MAX_CI];
        sscanf(linea, "%*20[^\n] %s", temp_cedula);
        if (strcmp(temp_cedula, cedula) == 0) {
            printf("La cedula %s ya esta registrada\n", cedula);
            return 1;
        }
    }

    return 0;
}

void Modificar_Cliente() {
    FILE *archivo = fopen("cedulas.txt", "r+");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo\n");
        return;
    }

    char cedula[MAX_CI];
    printf("Ingrese la cedula del cliente a modificar: ");
    scanf("%10s", cedula);

    char linea[150];
    long pos;
    int encontrado = 0;

    while (fgets(linea, sizeof(linea), archivo)) {
        char nombre[MAXIMO];
        char temp_cedula[MAX_CI];
        sscanf(linea, "%s %s", nombre, temp_cedula);
        if (strcmp(temp_cedula, cedula) == 0) {
            encontrado = 1;
            fseek(archivo, ftell(archivo) - strlen(linea), SEEK_SET);
            printf("Ingrese el nuevo nombre: ");
            char nuevo_nombre[MAXIMO];
            scanf("%s", nuevo_nombre);

            // Crear una cadena con la nueva línea completa
            char nueva_linea[150];
            sprintf(nueva_linea, "%-20s  %s\n", nuevo_nombre, temp_cedula);

            // Escribir la nueva línea completa
            fprintf(archivo, "%s", nueva_linea);
            break;
        }
    }

    if (!encontrado) {
        printf("Cliente con cedula %s no encontrado.\n", cedula);
    }

    fclose(archivo);
}

void Consultar_Cliente() {
    FILE *archivo = fopen("cedulas.txt", "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo\n");
        return;
    }

    char criterio[50];
    printf("Ingrese la cedula o el nombre del cliente a buscar: ");
    scanf("%s", criterio);

    char linea[150];
    int encontrado = 0;

    while (fgets(linea, sizeof(linea), archivo)) {
        if (strstr(linea, criterio)) {
            char nombre[50], apellido[50], cedula[MAX_CI];
            sscanf(linea, "%20[^\n]  %10[^\n]", nombre,  cedula);
            printf("%-20s %s\n", nombre, cedula);
            encontrado = 1;
        }
    }

    if (!encontrado) {
        printf("Cliente con criterio %s no encontrado.\n", criterio);
    }

    fclose(archivo);
}

void Listar_Clientes() {
    FILE *archivo = fopen("cedulas.txt", "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo\n");
        return;
    }

    char linea[150];
    printf("Listado de Clientes:\n");
    printf("%-20s  %-11s\n", "Nombre",  "Cedula");

    while (fgets(linea, sizeof(linea), archivo)) {
        char nombre[50], cedula[MAX_CI];
        sscanf(linea, "%20[^\n]  %10[^\n]", nombre, cedula);
        printf("%-20s  %s\n", nombre,  cedula);
    }

    fclose(archivo);
}
