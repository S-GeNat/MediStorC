#include <stdio.h>
#include <string.h>
#include "Prototipos.h"
#include "lectura.h"

void Ingresar_Medicamentos(int *Num_med, char Name_med[][MAXIMO], int cant[], float precio[], float descuento[]) {
    FILE *archivo = fopen("medicamentos.txt", "r+");
    if (archivo == NULL) {
        archivo = fopen("medicamentos.txt", "w+");
        if (archivo == NULL) {
            printf("No se pudo crear el archivo.\n");
            return;
        }
    }

    // Obtener el último número de medicamento
    int ultimo_numero = 0;
    char linea[100];
    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        if (sscanf(linea, "Medicamento %d:", &ultimo_numero) == 1) {
            // No hacer nada, solo actualizar ultimo_numero
        }
    }

    fseek(archivo, 0, SEEK_END);

    printf("\nIngreso de Stock:\n");
    int Num = leerEnteroPositivo("Cuantos medicamentos se va a ingresar: ");

    for (int i = 0; i < Num; i++) {
        printf(" Medicamento %d :\n", ultimo_numero + i + 1);
        
        int indice = *Num_med; // Utilizar una variable separada para el índice

        char nombre[MAXIMO];
        while (1) {
            printf("Nombre: ");
            getchar(); 
            fgets(nombre, MAXIMO, stdin);
            nombre[strcspn(nombre, "\n")] = '\0';  
            
            int existe = 0;
            rewind(archivo); // Volver al principio del archivo
            while (fgets(linea, sizeof(linea), archivo) != NULL) {
                char nombre_archivo[MAXIMO];
                if (sscanf(linea, "Nombre: %s", nombre_archivo) == 1) {
                    if (strcmp(nombre_archivo, nombre) == 0) {
                        existe = 1;
                        break;
                    }
                }
            }
            
            if (existe) {
                printf("El nombre del medicamento ya existe. Por favor, ingrese un nombre diferente.\n");
            } else {
                break;
            }
        }
        
        strcpy(Name_med[indice], nombre); // Copiar el nombre válido a la matriz
        
        cant[indice] = leerEnteroPositivo("Cantidad: ");
        precio[indice] = leerFlotantePositivo("Precio unitario: ");
        descuento[indice] = leerEnteroEntre("Porcentaje Descuento (Ingrese 0 si no lo tiene): ", 0, 100);
       
        fprintf(archivo, "Medicamento %d:\n", ultimo_numero + i + 1);
        fprintf(archivo, "Nombre: %s\n", Name_med[indice]);
        fprintf(archivo, "Cantidad: %d\n", cant[indice]);
        fprintf(archivo, "Precio unitario: %.2f\n", precio[indice]);
        fprintf(archivo, "Porcentaje Descuento: %.2f\n", descuento[indice]);
    
        (*Num_med)++; // Incrementar el contador de medicamentos
    }

    fclose(archivo);
}

void Cargar_Medicamentos(int *Num_med, char Name_med[][MAXIMO], int cant[], float precio[], float descuento[]) {
    FILE *archivo = fopen("medicamentos.txt", "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo para leer.\n");
        return;
    }

    *Num_med = 0;
    int num = 0;
    while (fscanf(archivo, "Medicamento %d:\n", &num) == 1) {
        fscanf(archivo, "Nombre: %[^\n]\n", Name_med[*Num_med]);
        fscanf(archivo, "Cantidad: %d\n", &cant[*Num_med]);
        fscanf(archivo, "Precio unitario: %f\n", &precio[*Num_med]);
        fscanf(archivo, "Porcentaje Descuento: %f\n", &descuento[*Num_med]);
        (*Num_med)++;
    }

    fclose(archivo);
}

void Modificar_Medicamentos(int *Num_med, char Name_med[][MAXIMO], int cant[], float precio[], float descuento[]) {
    // Cargar los medicamentos desde el archivo
    *Num_med = 0;
    Cargar_Medicamentos(Num_med, Name_med, cant, precio, descuento);

    printf("Ingrese el nombre del medicamento a modificar: ");
    char nombre[MAXIMO];
    getchar(); // para consumir el salto de línea dejado por scanf en el menú principal
    fgets(nombre, MAXIMO, stdin);
    nombre[strcspn(nombre, "\n")] = '\0'; // eliminar el carácter de nueva línea

    int encontrado = 0;
    int num;
    for (num = 0; num < *Num_med; num++) {
        if (strcmp(Name_med[num], nombre) == 0) {
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Medicamento no encontrado.\n");
        return;
    }

    // Modificar la cantidad
    printf("Cantidad actual: %d\n", cant[num]);
    printf("Nueva cantidad (deje vacio para no cambiar): ");
    char nuevaCantidadStr[MAXIMO];
    fgets(nuevaCantidadStr, MAXIMO, stdin);
    nuevaCantidadStr[strcspn(nuevaCantidadStr, "\n")] = '\0'; // eliminar el carácter de nueva línea
    if (strlen(nuevaCantidadStr) > 0) {
        int nuevaCantidad;
        if (sscanf(nuevaCantidadStr, "%d", &nuevaCantidad) == 1 && nuevaCantidad > 0) {
            cant[num] = nuevaCantidad;
        } else {
            printf("Cantidad invalida. No se realizaron cambios en la cantidad.\n");
        }
    }

    // Modificar el precio
    printf("Precio unitario actual: %.2f\n", precio[num]);
    printf("Nuevo precio unitario (deje vacio para no cambiar): ");
    char nuevoPrecioStr[MAXIMO];
    fgets(nuevoPrecioStr, MAXIMO, stdin);
    nuevoPrecioStr[strcspn(nuevoPrecioStr, "\n")] = '\0'; // eliminar el carácter de nueva línea
    if (strlen(nuevoPrecioStr) > 0) {
        float nuevoPrecio;
        if (sscanf(nuevoPrecioStr, "%f", &nuevoPrecio) == 1 && nuevoPrecio > 0) {
            precio[num] = nuevoPrecio;
        } else {
            printf("Precio invalido. No se realizaron cambios en el precio.\n");
        }
    }

    // Modificar el descuento
    printf("Porcentaje Descuento actual: %.2f\n", descuento[num]);
    printf("Nuevo porcentaje Descuento (deje vacio para no cambiar): ");
    char nuevoDescuentoStr[MAXIMO];
    fgets(nuevoDescuentoStr, MAXIMO, stdin);
    nuevoDescuentoStr[strcspn(nuevoDescuentoStr, "\n")] = '\0'; // eliminar el carácter de nueva línea
    if (strlen(nuevoDescuentoStr) > 0) {
        float nuevoDescuento;
        if (sscanf(nuevoDescuentoStr, "%f", &nuevoDescuento) == 1 && nuevoDescuento >= 0 && nuevoDescuento <= 100) {
            descuento[num] = nuevoDescuento;
        } else {
            printf("Descuento invalido. No se realizaron cambios en el descuento.\n");
        }
    }

    // Abrir el archivo para escribir
    FILE *archivo = fopen("medicamentos.txt", "w");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo para escribir.\n");
        return;
    }

    for (int i = 0; i < *Num_med; i++) {
        fprintf(archivo, "Medicamento %d:\n", i + 1);
        fprintf(archivo, "Nombre: %s\n", Name_med[i]);
        fprintf(archivo, "Cantidad: %d\n", cant[i]);
        fprintf(archivo, "Precio unitario: %.2f\n", precio[i]);
        fprintf(archivo, "Porcentaje Descuento: %.2f\n", descuento[i]);
    }

    fclose(archivo);
    printf("Los cambios se guardaron exitosamente.\n");
}

void Guardar_Medicamentos(int Num_med, char Name_med[][MAXIMO], int cant[], float precio[], float descuento[]) {
    FILE *archivo = fopen("medicamentos.txt", "w");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo para escribir.\n");
        return;
    }

    for (int i = 0; i < Num_med; i++) {
        fprintf(archivo, "Medicamento %d:\n", i + 1);
        fprintf(archivo, "Nombre: %s\n", Name_med[i]);
        fprintf(archivo, "Cantidad: %d\n", cant[i]);
        fprintf(archivo, "Precio unitario: %.2f\n", precio[i]);
        fprintf(archivo, "Porcentaje Descuento: %.2f\n", descuento[i]);
    }

    fclose(archivo);
}

void Agregar_Stock(int *Num_med, char Name_med[][MAXIMO], int cant[], float precio[], float descuento[]) {
    Cargar_Medicamentos(Num_med, Name_med, cant, precio, descuento);

    while (1) {
        printf("Ingrese el nombre del medicamento para agregar stock (o 's' para salir): ");
        char nombre[MAXIMO];
        fgets(nombre, MAXIMO, stdin);
        nombre[strcspn(nombre, "\n")] = '\0'; // eliminar caracter de nueva línea

        if (strcmp(nombre, "s") == 0) {
            break; // Salir del bucle si el usuario ingresa 's'
        }

        // Limpiar el buffer de entrada antes de la siguiente lectura
        while (getchar() != '\n'); // Limpiar hasta encontrar el final de la línea

        int encontrado = 0;
        int num;
        for (num = 0; num < *Num_med; num++) {
            if (strcmp(Name_med[num], nombre) == 0) {
                encontrado = 1;
                break;
            }
        }

        if (!encontrado) {
            printf("Medicamento no encontrado.\n");
            continue; // Volver a pedir el nombre del medicamento si no se encontró
        }

        printf("Cantidad actual: %d\n", cant[num]);
        printf("Cantidad a agregar: ");
        int cantidad_a_agregar;
        scanf("%d", &cantidad_a_agregar);
        getchar(); // Para consumir el salto de línea dejado por scanf
        if (cantidad_a_agregar > 0) {
            cant[num] += cantidad_a_agregar;
            printf("Cantidad actualizada: %d\n", cant[num]);
        } else {
            printf("Cantidad inválida. No se realizaron cambios.\n");
        }

        // Guardar los cambios en el archivo
        Guardar_Medicamentos(*Num_med, Name_med, cant, precio, descuento);
    }
}





void Eliminar_Medicamentos(int *Num_med, char Name_med[][MAXIMO], int cant[], float precio[], float descuento[]) {
    printf("Ingrese el numero del medicamento a eliminar: ");
    int num;
    scanf("%d", &num);
    if (num <= 0 || num > *Num_med) {
        printf("Numero de medicamento no valido.\n");
        return;
    }
    num--;

    for (int i = num; i < *Num_med - 1; i++) {
        strcpy(Name_med[i], Name_med[i + 1]);
        cant[i] = cant[i + 1];
        precio[i] = precio[i + 1];
        descuento[i] = descuento[i + 1];
    }
    (*Num_med)--;

    FILE *archivo = fopen("medicamentos.txt", "w");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo para escribir.\n");
        return;
    }

    for (int i = 0; i < *Num_med; i++) {
        fprintf(archivo, "Medicamento %d:\n", i + 1);
        fprintf(archivo, "Nombre: %s\n", Name_med[i]);
        fprintf(archivo, "Cantidad: %d\n", cant[i]);
        fprintf(archivo, "Precio unitario: %.2f\n", precio[i]);
        fprintf(archivo, "Porcentaje Descuento: %.2f\n", descuento[i]);
    }

    fclose(archivo);
}

void Consultar_Medicamentos(char Name_med[][MAXIMO], char Buscar[], int nombre, int cantidades[], float precios[], float descuentos[]) {
    printf("Ingrese el nombre a buscar: ");
    getchar();
    fgets(Buscar, nombre, stdin);
    Buscar[strcspn(Buscar, "\n")] = '\0';

    FILE *archivo = fopen("medicamentos.txt", "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo para leer.\n");
        return;
    }

    char nombreMedicamento[MAXIMO];
    int cantidad;
    float precio, descuento;
    int encontrado = 0;

    while (fscanf(archivo, "Medicamento %*d:\n") != EOF) {
        fscanf(archivo, "Nombre: %[^\n]\n", nombreMedicamento);
        fscanf(archivo, "Cantidad: %d\n", &cantidad);
        fscanf(archivo, "Precio unitario: %f\n", &precio);
        fscanf(archivo, "Porcentaje Descuento: %f\n", &descuento);

        if (strcmp(nombreMedicamento, Buscar) == 0) {
            printf("Encontrado\n");
            mostrarBuscar(nombreMedicamento, cantidad, precio, descuento);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("No Encontrado\n");
    }

    fclose(archivo);
}



void mostrarBuscar(char* nombre, int cantidad, float precio, float descuento) {
    float precioFinal = precio * (1 - descuento / 100);
    printf("%-15s %8s %10s %11s %15s\n", "Nombre", "Cantidad", "Precio", "Descuento", "Precio Final");
    printf("------------------------------------------------------------------------\n");
    printf("%-15s %8d %10.2f %10.2f%% %15.2f\n", nombre, cantidad, precio, descuento, precioFinal);
}

void Lista_Medicamentos() {
    FILE *archivo = fopen("medicamentos.txt", "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo para leer.\n");
        return;
    }

    char nombre[MAXIMO];
    int cantidad, numero;
    float precio, descuento;

    printf("\n---------------------- Informacion de Medicamentos ----------------------\n");
    printf("%-8s %-15s %8s %10s %11s %10s\n", "Numero", "Nombre", "Cantidad", "Precio", "Descuento", "Precio Final");
    printf("----------------------------------------------------------------------------\n");

    while (fscanf(archivo, "Medicamento %d:\n", &numero) == 1) {
        fscanf(archivo, "Nombre: %[^\n]\n", nombre);
        fscanf(archivo, "Cantidad: %d\n", &cantidad);
        fscanf(archivo, "Precio unitario: %f\n", &precio);
        fscanf(archivo, "Porcentaje Descuento: %f\n", &descuento);

        float precioFinal = precio * (1 - descuento / 100);
        printf("%-8d %-15s %8d %10.2f %10.2f%% %10.2f\n", numero, nombre, cantidad, precio, descuento, precioFinal);
    }

    fclose(archivo);
}