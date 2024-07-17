#include <stdio.h>
#include <string.h>
#include "Prototipos.h"

//gcc -c .\Main.c .\Opciones.c .\Clientes.c .\Facturacion.c .\lectura.c .\Productos.c 
//gcc .\Main.o .\Opciones.o .\Clientes.o .\Facturacion.o .\lectura.o .\Productos.o -o Medi
//.\Medi.exe

int main (int argc, char *argv[]) {
    //Ingreso a MediStor
    char User[MAXIMO],clave[MAXIMO];
    ingresarTrabajador(User,clave);

    //Inicializacion de Variable Medicamentos
    char Name_med[MAXIMO][MAXIMO];
    int cant[MAXIMO];
    float precio[MAXIMO], descuento[MAXIMO];
    int Num_med = 0;
    char Buscar[MAXIMO];

    char nombre[MAXIMO];
    char cedula[MAX_CI];

   int op; 
    do{
       Opcion_Principal();
       
       scanf("%d", &op);
       switch (op) {
            case 1:
                Ingresar_Medicamentos(&Num_med,Name_med, cant, precio,descuento);
                break;
            case 2:
                Modificar_Medicamentos(&Num_med,Name_med,cant,precio,descuento);
                break;
            case 3:
                Eliminar_Medicamentos(&Num_med,Name_med, cant, precio,descuento);
                break;
            case 4:
                Agregar_Stock( &Num_med, Name_med,  cant, precio,  descuento);
                break;    
            case 5:
                Consultar_Medicamentos(Name_med,Buscar,MAXIMO, cant, precio,descuento);
                break; 
            case 6:
                Lista_Medicamentos();
                break; 
            case 7:
                Ingresar_Cliente(nombre,cedula);
                break; 
            case 8:
                Modificar_Cliente();
                break; 
            case 9:
                Consultar_Cliente();
                break; 
            case 10:
                Listar_Clientes();
                break;  
            case 11:
                Comprar_ConsumidoFinal(&Num_med,  Name_med,  cant,  precio,  descuento);
                break; 
            case 12:
                Comprar_Factura(&Num_med, Name_med, cant,precio,descuento);
                break; 
            case 13:
                BuscarFactura();
                break; 
            case 14:
                ImprimirTodasFacturas();
                break;                                       
            case 15:
                printf("Saliendo del programa....\n");
                break;
            default:
                printf("Opcion no valida. Intenta de nuevo.\n");
                break;
        }
    }while(op != 15);
    
    return 0;
}