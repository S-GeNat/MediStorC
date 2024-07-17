#ifndef PROTOTIPOS_H
#define PROTOTIPOS_H
#define CONTRASEÑA "0524"
#define MAXIMO 100 
#define MAX_CI 11

//Main
void Opcion_Principal();
void ingresarTrabajador(char [MAXIMO], char [MAXIMO]);

//MEDICAMENTOS
void Ingresar_Medicamentos(int*, char [][MAXIMO], int [], float [], float []);
void Modificar_Medicamentos(int* , char [][MAXIMO], int [], float [], float []);
void Eliminar_Medicamentos(int*, char [][MAXIMO], int [], float [], float []);
void Consultar_Medicamentos(char [][MAXIMO], char [], int , int [], float [], float []);
void mostrarBuscar(char* , int , float , float );
void Lista_Medicamentos();
void Agregar_Stock(int *Num_med, char Name_med[][MAXIMO], int cant[], float precio[], float descuento[]);

//CLIENTES
void Ingresar_Cliente(char nombre[MAXIMO],char cedula[MAX_CI]);
void Modificar_Cliente();
void Consultar_Cliente();
void Listar_Clientes();

//FACTURAS
void Comprar_ConsumidoFinal(int*, char[][MAXIMO], int[], float[], float[]);
void Adicionar_Compra(int*, char[][MAXIMO], int[], float[], float[], int*, float*);
char* Fecha(void);
int Consultar_Cliente_Factura1(char [], char []);
void GuardarFactura(char [], int, float);
void Comprar_Factura(int *, char [][MAXIMO], int [], float [], float []);
void BuscarFactura(void);
void ImprimirTodasFacturas(void);

//FACTURAS Y MEDICAMENTOS
void Cargar_Medicamentos(int *Num_med, char Name_med[][MAXIMO], int cant[], float precio[], float descuento[]);
void Guardar_Medicamentos(int Num_med, char Name_med[][MAXIMO], int cant[], float precio[], float descuento[]);
#endif // PROTOTIPOS_H

