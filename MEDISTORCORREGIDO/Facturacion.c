#include <stdio.h>
#include <string.h>
#include <time.h>
#include "Prototipos.h"
#include "lectura.h"

void Comprar_ConsumidoFinal(int *Num_med, char Name_med[][MAXIMO], int cant[], float precio[], float descuento[]) {
    int op;
    int total_productos = 0;
    float valor_total = 0;


    do {
        Adicionar_Compra(Num_med, Name_med, cant, precio, descuento, &total_productos, &valor_total);
        op = leerEntero("Desea seguir adquiriendo más productos:  (Si= 1 / No=2)");
    } while(op != 2);

    printf("------Consumidor Final --------\n"); 
    printf("Total de productos comprados: %d\n", total_productos);
    printf("Valor total de la compra: %.2f\n", valor_total);
    printf("----Gracias por preferirnos----\n");


}

void Adicionar_Compra(int *Num_med, char Name_med[][MAXIMO], int cant[], float precio[], float descuento[], int *total_productos, float *valor_total) {

    printf("Ingrese el nombre del medicamento a comprar: ");
    char nombre[MAXIMO];
    getchar();
    fgets(nombre, MAXIMO, stdin);
    nombre[strcspn(nombre, "\n")] = '\0';  // Eliminar el salto de línea

    Cargar_Medicamentos(Num_med, Name_med, cant, precio, descuento);

    int encontrado = -1;
    for (int i = 0; i < *Num_med; i++) {
        if (strcmp(Name_med[i], nombre) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) {
        printf("Medicamento no encontrado en la lista.\n");
        return;
    }

    int cantidadComprada;
    printf("Ingrese la cantidad a comprar: ");
    scanf("%d", &cantidadComprada);
    getchar();

    if (cantidadComprada > cant[encontrado]) {
        printf("No hay suficiente stock. Stock actual: %d\n", cant[encontrado]);
        return;
    }

    // Realizar la compra
    cant[encontrado] -= cantidadComprada;

    float subtotal = cantidadComprada * precio[encontrado];
    float descuento_aplicado = subtotal * (descuento[encontrado] / 100);
    float total_producto = subtotal - descuento_aplicado;

    *total_productos += cantidadComprada;
    *valor_total += total_producto;

    // Actualizar el archivo
    Guardar_Medicamentos(*Num_med, Name_med, cant, precio, descuento);

    printf("Compra adicionada exitosamente.\n");
    printf("Cantidad comprada: %d\n", cantidadComprada);
    printf("Subtotal: %.2f\n", subtotal);
    printf("Descuento aplicado: %.2f\n", descuento_aplicado);
    printf("Total por este producto: %.2f\n", total_producto);
}



char* Fecha() {
    static char fecha[30];  
    time_t now;
    time(&now);
    struct tm *local = localtime(&now);
    sprintf(fecha, "Fecha: %02d/%02d/%d", local->tm_mday, local->tm_mon + 1, local->tm_year + 1900);
    return fecha;
}


int Consultar_Cliente_Factura1(char cedula[], char nombre_cliente[]) {
    FILE *archivo = fopen("cedulas.txt", "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo\n");
        return 0;
    }

    char linea[100];
    while (fgets(linea, 100, archivo)) {
        char nombre_archivo[50];
        char cedula_archivo[20];
        sscanf(linea, "%49s %19s", nombre_archivo, cedula_archivo);

        printf("Cedula archivo: %s, Cedula ingresada: %s\n", cedula_archivo, cedula);

        if (strcmp(cedula, cedula_archivo) == 0) {
            strcpy(nombre_cliente, nombre_archivo);
            fclose(archivo);
            return 1;
        }
    }

    fclose(archivo);
    return 0;
}



void Comprar_Factura(int *Num_med, char Name_med[][MAXIMO], int cant[], float precio[], float descuento[]) {
    int op;
    int total_productos = 0;
    float valor_total = 0;

    do {
        Adicionar_Compra(Num_med, Name_med, cant, precio, descuento, &total_productos, &valor_total);
        op = leerEntero("Desea seguir adquiriendo mas productos:  (Si= 1 / No=2)");
    } while(op!= 2);

    char cedula[MAX_CI];
    char nombre_cliente[50];

    int encontrado = 0;
    while (!encontrado) {
        printf("Ingrese el numero de cedula del cliente: ");
        scanf("%s", cedula);

        if (Consultar_Cliente_Factura1(cedula, nombre_cliente)) {
            encontrado = 1;
            printf("\n==============================\n");
            printf("%s\n", Fecha());
            printf("\n===== FACTURA =====\n");
            printf("Cedula: %s\n", cedula);
            printf("Cliente: %s\n", nombre_cliente);
            printf("----------------------------\n");
            printf("Total de productos comprados: %d\n", total_productos);
            printf("Valor total de la compra: %.2f\n", valor_total);
            printf("----------------------------\n");
            printf("--Gracias por preferirnos---\n");
            printf("----------------------------\n");

            GuardarFactura(cedula, total_productos, valor_total);
        } else {
            printf("Cliente con cedula %s no encontrado. Intente nuevamente.\n", cedula);
        }
    }
}

void GuardarFactura(char cedula[], int total_productos, float valor_total) {
    FILE *archivo = fopen("facturas.txt", "a");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo\n");
        return;
    }

    fprintf(archivo, "Cedula: %s\n", cedula);
    fprintf(archivo, "%s\n", Fecha());
    fprintf(archivo, "Total de productos comprados: %d\n", total_productos);
    fprintf(archivo, "Valor total de la compra: %.2f\n\n", valor_total);
    fclose(archivo);
}


void BuscarFactura() {
    char cedula[20];
    printf("Ingrese el numero de cedula del cliente: ");
    scanf("%s", cedula);

    FILE *archivo = fopen("facturas.txt", "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo de facturas.\n");
        return;
    }

    char linea[100];
    int encontrado = 0;

    while (fgets(linea, sizeof(linea), archivo)) {
        if (strstr(linea, cedula) != NULL) {
            printf("Factura encontrada:\n");
            printf("%s", linea);
            for (int i = 0; i < 4; i++) {
                fgets(linea, sizeof(linea), archivo);
                printf("%s", linea);
            }
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("No se encontro factura para la cedula %s\n", cedula);
    }

    fclose(archivo);
}

void ImprimirTodasFacturas() {
    FILE *archivo = fopen("facturas.txt", "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo de facturas.\n");
        return;
    }

    char linea[100];
    printf("Todas las facturas:\n\n");

    while (fgets(linea, sizeof(linea), archivo)) {
        printf("%s", linea);
    }

    fclose(archivo);
}

