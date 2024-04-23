#include <stdlib.h>
#include <stdio.h>

typedef struct nodo
{
    char nombre[100];
    int edad;
    char direccion[200];
    long numTel;
    struct nodo *sig;
} Persona;

typedef struct
{
    Persona *inicio;
    char dueño[100];
    int numReg;
} Agenda;

