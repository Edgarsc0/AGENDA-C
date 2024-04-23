#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include <string.h>

void inicializarAgenda(Agenda *agenda, char *nombre)
{
    agenda->inicio = NULL;
    agenda->numReg = 0;
    strcpy(agenda->dueño, nombre);
}

Persona *crearPersona()
{
    Persona *per = NULL;
    per = (Persona *)malloc(sizeof(Persona));
    if (per != NULL)
    {
        per->sig = NULL;
    }
    return per;
}

void agregarRegistro(Agenda *agenda, Persona *registro)
{
    Persona *nav = NULL;
    if (agenda->inicio == NULL)
    {
        agenda->inicio = registro;
        agenda->numReg += 1;
        return;
    }
    nav = agenda->inicio;
    while (nav->sig != NULL)
    {
        nav = nav->sig;
    }
    nav->sig = registro;
    agenda->numReg += 1;
    return;
}

void mostrarRegistros(Agenda *agenda)
{
    int i = 1;
    Persona *nav;
    nav = agenda->inicio;
    while (nav != NULL)
    {
        printf("%d: ", i);
        printf("Nombre: %s", nav->nombre);
        printf("---------------------------------------------------------\n");
        printf("Edad: %d\n", nav->edad);
        printf("Direccion: %s", nav->direccion);
        printf("Telefono: %ld\n\n", nav->numTel);
        nav = nav->sig;
        i++;
    }
}

void borrarRegistro(Agenda *agenda)
{
    Persona *nav;
    if (agenda->inicio == NULL)
    {
        return;
    }
    nav = agenda->inicio;
    agenda->inicio = agenda->inicio->sig;
    agenda->numReg -= 1;
    free(nav);
    return;
}

Persona *getPersonaByID(Agenda *agenda, int id)
{
    int i = 1;
    Persona *nav;
    nav = agenda->inicio;
    while (i != id)
    {
        nav = nav->sig;
        i++;
    }
    return nav;
}

void actualizarRegistro(Agenda *agenda, int selectedRegister, int fieldToUpdateIndex)
{
    Persona *registro = getPersonaByID(agenda, selectedRegister);
    system("cls");
    switch (fieldToUpdateIndex)
    {
    case 1:
        printf("Escriba el nuevo nombre %S: ");
        setbuf(stdin, NULL);
        fgets(registro->nombre, 100, stdin);
        printf("Se ha actualizado el nombre.");
        // nombre
        break;
    case 2:
        // edad
        printf("Escriba la nueva edad: ");
        scanf("%d", &(registro->edad));
        printf("Se ha actualizado la edad");
        break;
    case 3:
        // direccion
        printf("Escriba la nueva direccion %S: ");
        setbuf(stdin, NULL);
        fgets(registro->direccion, 200, stdin);
        printf("Se ha actualizado la direccion.");
        break;
    case 4:
        // telefono
        printf("Escriba el nuevo telefono: ");
        scanf("%ld", &(registro->numTel));
        printf("Se ha actualizado el telefono");
        break;
    default:
        break;
    }
}

void mostrarNombresAgendas(Agenda *agenda)
{
    int i = 1;
    Persona *nav;
    nav = agenda->inicio;
    while (nav != NULL)
    {
        printf("%d: ", i);
        printf("%s", nav->nombre);
        nav = nav->sig;
        i++;
    }
}

void escribirAgenda(Agenda *agenda, FILE *archivo)
{
    int i = 1;
    Persona *nav;
    nav = agenda->inicio;
    while (nav != NULL)
    {
        char linea[500];
        sprintf(linea, "%d: NOMBRE %s, EDAD: %d, DIRECCION: %s, TELEFONO: %ld\n", i, nav->nombre, nav->edad, nav->direccion, nav->numTel);
        fprintf(archivo, linea);
        nav = nav->sig;
        i++;
    }
    fclose(archivo);
    printf("Se ha guardado la agenda correctamente\n");
}

int main()
{
    int selectedOption;
    int selectedRegister;
    int fieldToUpdateIndex;
    char dueño[100];
    char newAction[2];

    // Datos de la agenda
    printf("Bienvenido a la app de Agenda. \n");
    printf("Por favor ingrese el duenno: ");
    scanf("%s", dueño);
    system("cls");

    // Inicializar agenda:
    Agenda miAgenda;
    inicializarAgenda(&miAgenda, dueño);

    do
    {
        // Menu
        printf("Mostrando agenda de %s\n", dueño);
        printf("1. AGREGAR REGISTRO\n");
        printf("2. MOSTRAR AGENDA\n");
        printf("3. BORRAR UN RESGISTRO\n");
        printf("4. ACTUALIZAR REGISTRO\n");
        printf("5. AGREGAR AGENDA A TXT\n");
        printf("Elija una opcion: ");
        scanf("%d", &selectedOption);

        // Operaciones
        switch (selectedOption)
        {
        case 1:
            // Limpiar consola
            system("cls");

            // Crear el espacio de memoria
            Persona *nuevoRegistro = crearPersona();
            nuevoRegistro->sig = NULL;

            // Rellenar el espacio de memoria

            // Nombre
            printf("Ingrese el nombre de la persona: ");
            setbuf(stdin, NULL);
            fgets(nuevoRegistro->nombre, 100, stdin);

            // Edad
            printf("Ingrese la edad de %s: ", nuevoRegistro->nombre);
            scanf("%d", &(nuevoRegistro->edad));

            // Direccion
            printf("Ingrese la direccion de %s: ", nuevoRegistro->nombre);
            setbuf(stdin, NULL);
            fgets(nuevoRegistro->direccion, 200, stdin);

            // Telefono
            printf("Ingrese el telefono de %s: ", nuevoRegistro->nombre);
            scanf("%ld", &(nuevoRegistro->numTel));

            // Limpiar consola
            system("cls");

            agregarRegistro(&miAgenda, nuevoRegistro);
            printf("\n%s", "Se ha agregado el registro a la agenda");

            break;
        case 2:
            // Limpiar consola
            system("cls");

            printf("Mostrando agenda de %s\n", dueño);

            mostrarRegistros(&miAgenda);
            break;
        case 3:
            borrarRegistro(&miAgenda);
            printf("%s", "Se ha borrado el primer registro.\n");
            break;
        case 4:
            // Limpiar consola
            system("cls");
            printf("Mostrando agenda de %s\n", dueño);
            mostrarNombresAgendas(&miAgenda);
            printf("Escriba el numero del registro que desea modificar: ");
            scanf("%d", &selectedRegister);
            system("cls");
            Persona *registroModificar = getPersonaByID(&miAgenda, selectedRegister);
            printf("MOSTRANDO INFORMACION DE: %s", registroModificar->nombre);
            printf("1. NOMBRE: %s", registroModificar->nombre);
            printf("2. EDAD: %d\n", registroModificar->edad);
            printf("3. DIRECCION %s", registroModificar->direccion);
            printf("4. TELEFONO: %ld\n", registroModificar->numTel);
            printf("Seleccione el campo a modificar de %s: ", registroModificar->nombre);
            scanf("%d", &fieldToUpdateIndex);
            actualizarRegistro(&miAgenda, selectedRegister, fieldToUpdateIndex);
            break;
        case 5:
            FILE *archivo;
            char nombre_archivo[50];
            sprintf(nombre_archivo, "agenda_%s.txt", dueño);
            archivo = fopen(nombre_archivo, "w");
            if (archivo != NULL)
            {
                escribirAgenda(&miAgenda, archivo);
            }
            break;
        }
        printf("\nDeseas realizar una nueva accion? Si(S) No(N): ");
        scanf("%1s", &newAction);

        // Limpiar consola
        system("cls");

    } while (strcmp(newAction, "S") == 0);

    return 0;
}
