#include <stdio.h>
#include "lectura.h"

int leerEnteroPositivo(char* mensaje){
  int valor;
  do{
    printf("%s", mensaje);
    scanf("%d",&valor);
  }while(valor <= 0);
  return valor;
}

int leerEntero(char* mensaje){
  int num1;
  printf("%s",mensaje);
  scanf("%d",&num1);
  return num1;
}

int leerEnteroEntre(char*mensaje, int min, int max){
  int num;
  do{
    printf("%s", mensaje);
    scanf("%d",&num);
  }while( num < min || num > max );
  return num;

}

float leerFlotantePositivo(char* mensaje){
  float valor;
  do{
    printf("%s", mensaje);
    scanf("%f",&valor);
  }while(valor <= 0);
  return valor;
}

float leerFlotante(char*mensaje){
  float num2;
  printf("%s",mensaje);
  scanf("%f", &num2);
  return num2;
}


float leerFlotanteEntre(char*mensaje, float min, float max){
  float num;
  do{
    printf("%s", mensaje);
    scanf("%f",&num);
  }while( num < min || num > max );
  return num;

}

char leerCaracter( char* mensaje){
  char caracter;
  printf("%s",mensaje);
  scanf(" %c", &caracter);
  return caracter;
}
float leerFlotanteMayorIgual (char* mensaje,float lim){
  float num;
  do{
    printf("%s", mensaje);
    scanf("%f",&num);
  }while( num < lim);
  return num;
}
