#include "Prototipos.h"
#include <stdio.h>
#include <string.h>
void Opcion_Principal() {
    printf("\n-----------Menu Principal-----------\n");
    printf("---------Medicamentos----------\n");
    printf("1.- Ingresar \n");
    printf("2.- Modificar \n");
    printf("3.- Eliminar \n");
    printf("4.- Agregar Stock \n");
    printf("5.- Consultar \n");
    printf("6.- Listado Medicamentos \n");
    printf("-----------Clientes-----------\n");
    printf("7.- Ingresar \n");
    printf("8.- Modificar \n");
    printf("9.- Consultar \n");
    printf("10.- Listado Clientes \n");
    printf("----------Facturacion----------\n");
    printf("11.- Comprar y Consumidor Final \n");
    printf("12.- Comprar y Facturar \n");
    printf("13.- Buscar Factura \n");
    printf("14.- Listado Facturas \n");
    printf("15.- Salir\n");
}

void ingresarTrabajador(char nombre[MAXIMO], char clave[MAXIMO]) {
    printf("---------Bienvenido a MediStor----------\n");
    printf("Ingrese su nombre: ");
    scanf("%s", nombre);
    do {
        printf("Ingrese contrasena de acceso: ");
        scanf("%s", clave);
        if (strcmp(clave, CONTRASEÑA) != 0) {
            printf("Contrasena incorrecta. Intente de nuevo.\n");
        }
    } while (strcmp(clave, CONTRASEÑA) != 0);
}
