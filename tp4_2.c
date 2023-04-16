// modulo ToDO

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    int TareaID;
    char * Descripcion;
    int Duracion; 
}Tarea;

void inicializar (Tarea **, int cant);
void cargarTarea (Tarea **, int cant);
void listarTarea (Tarea *);
void preguntarRealizada (Tarea **, Tarea **, int cant);
Tarea * buscarTareaPorId (Tarea **, Tarea **, int cant);
Tarea * buscarTareaPorPalabra (Tarea **, Tarea **, int cant);

int main ()
{
    srand(time(NULL));

    int cant;
    Tarea ** TareasPendientes;
    Tarea ** TareasRealizadas;

    printf("Ingrese la cantidad de tareas a cargar: ");
    scanf("%d", &cant);
    getchar();

    TareasPendientes = (Tarea **)malloc(cant * sizeof(Tarea *));
    TareasRealizadas = (Tarea **)malloc(cant * sizeof(Tarea *));

    inicializar(TareasPendientes, cant); inicializar(TareasRealizadas, cant);

    cargarTarea(TareasPendientes, cant);
    

    for (int i=0; i<cant; i++) {
        listarTarea(TareasPendientes[i]);
        preguntarRealizada(TareasPendientes, TareasRealizadas, i);
    }

    printf("\nTareas Pendientes\n");
    for (int i=0; i<cant; i++) {
        listarTarea(TareasPendientes[i]);
    }
 
    printf("\nTareas realizadas\n");
    for (int i=0; i<cant; i++) {
        listarTarea(TareasRealizadas[i]);
    }

    // Busqueda por ID
    listarTarea (buscarTareaPorId(TareasPendientes, TareasRealizadas, cant));

    // Busqueda por palabras
    listarTarea (buscarTareaPorPalabra(TareasPendientes, TareasRealizadas, cant));    
    
    for (int i=0; i<cant; i++)
    {
        free(TareasPendientes[i]); free(TareasRealizadas[i]);
    }

    free(TareasPendientes); free(TareasRealizadas);

    return 0;
}


void inicializar (Tarea ** Tarea, int cant)
{

    for (int i=0; i<cant; i++) {
        Tarea[i] = NULL;
    }
} 

void cargarTarea (Tarea ** TareasPendientes, int cant)
{
    size_t BuffSize = 100;
    char * Buff = malloc(BuffSize * sizeof(char));
    
    for (int i=0; i<cant; i++) {
        TareasPendientes[i] = (Tarea *) malloc(sizeof(Tarea));

        printf("\nIngrese la descripción de la tarea ID %d: ", i);
        getline(&Buff, &BuffSize, stdin);

        TareasPendientes[i]->Descripcion = malloc((strlen(Buff)+1) * sizeof(char));
        strcpy (TareasPendientes[i]->Descripcion, Buff);

        TareasPendientes[i]->TareaID = i;
        TareasPendientes[i]->Duracion = 10 + rand()%91;
    }

    free(Buff);
}

void listarTarea (Tarea * Tarea)
{

    if (Tarea) {
        printf("--------------------------------\n");
        printf("Tarea ID: %d\n", Tarea->TareaID);
        printf("Descripcion: %s", Tarea->Descripcion);
        printf("Duracion: %d\n", Tarea->Duracion);

    }
}

void preguntarRealizada (Tarea ** Pendiente, Tarea ** Realizada, int id)
{
        int real;

        if (Pendiente) {
        printf("Ya se realizó esta tarea? (1 para SI): ");
        scanf("%d", &real);
        getchar();
        
        if (real == 1) {
            Realizada[id] = Pendiente[id];
            Pendiente[id] = NULL;
            printf("\nTarea %d realizada! \n ", Realizada[id]->TareaID);
        }
    }
}

Tarea * buscarTareaPorId (Tarea ** TareasPendientes, Tarea ** TareasRealizadas, int cant)
{
    int id;
    printf("\nIngrese el ID de Tarea a buscar: ");
    scanf("%d", &id);
    getchar();

    for (int i=0; i<cant; i++)
    {
        if (TareasPendientes[i] && TareasPendientes[i]->TareaID == id) {
                printf("\nTarea %d pendiente: \n", i);
                return TareasPendientes[i];
        }

        if (TareasRealizadas[i] && TareasRealizadas[i]->TareaID == id) {
                printf("\nTarea %d realizada: \n", i);
                return TareasRealizadas[i];
        }

    }

    printf("\n-------Tarea no encontrada---------\n");

    return NULL;
}

Tarea * buscarTareaPorPalabra (Tarea ** TareasPendientes, Tarea ** TareasRealizadas, int cant)
{
    size_t BuffSize = 100;
    char * Buff = malloc(BuffSize * sizeof(char));

    printf("\nIngrese la palabra a buscar: ");    
    getline(&Buff, &BuffSize, stdin);

    Buff[strlen(Buff)-1] = '\0';

    for (int i=0; i<cant; i++)
    {
        if (TareasPendientes[i] && strstr(TareasPendientes[i]->Descripcion, Buff)) {
                printf("\nTarea %d pendiente: \n", i);
                free(Buff);
                return TareasPendientes[i];
        }

        if (TareasRealizadas[i] && strstr(TareasRealizadas[i]->Descripcion, Buff)) {
                printf("\nTarea %d realizada: \n", i);
                free(Buff);
                return TareasRealizadas[i];
        }
    }

    printf("\n-------Tarea no encontrada---------\n");
    free(Buff);

    return NULL;
}
