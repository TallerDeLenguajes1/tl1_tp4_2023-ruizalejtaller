// modulo ToDO

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    int TareaID;
    char * Descripcion;
    int Duracion; 
}Tareas;

struct TNodo {
    Tareas Tarea;
    struct TNodo * sig;
} typedef TNodo;

TNodo * inicializarLista();
void cargarTarea (TNodo **, Tareas, int cant);
TNodo * crearNodo (Tareas);
void listarTarea (TNodo *);
void preguntarRealizada (TNodo **, TNodo **, int);
void cambiarRealizada (TNodo ** , TNodo **, TNodo **);
void quitarNodo (TNodo **, TNodo **);
TNodo * buscarPorID (TNodo ** Start, int idBus);
TNodo * buscarPorPalabra (TNodo ** Start, char *);
void liberar (TNodo **);


int main ()
{
    srand(time(NULL));

    int cant, id;
    TNodo ** StPendientes, ** StRealizadas;
    Tareas Tarea, TareasRealizadas;

    StPendientes = (TNodo **) malloc(sizeof(TNodo *));
    StRealizadas = (TNodo **) malloc(sizeof(TNodo *));

   * StPendientes = inicializarLista();
   * StRealizadas = inicializarLista();

    printf("Ingrese la cantidad de tareas a cargar: ");
    scanf("%d", &cant);
    getchar();

    cargarTarea(StPendientes, Tarea, cant);
    
    preguntarRealizada(StPendientes, StRealizadas, cant);

    // Mostrar tareas
    printf("\n// Tareas Pendientes //\n");

    TNodo * Aux = * StPendientes;
    while (Aux)
    {
        listarTarea(Aux);
        Aux = Aux->sig;
    }

        printf("\n // Tareas Realizadas //\n");

    Aux = * StRealizadas;
    while (Aux)
    {
        listarTarea(Aux);
        Aux = Aux->sig;
    }

    // Busqueda por ID
    printf("\nIngrese el ID de la tarea a buscar: ");

    scanf("%d", &id);
    getchar();

    Aux = buscarPorID(StPendientes, id);

    if (Aux)
    {
        printf("\n---La Tarea %d sigue pendiente---\n", id);
        listarTarea(Aux);
    } else {

        Aux = buscarPorID(StRealizadas, id);

        if (Aux)
        {
            printf("\n---La Tarea %d ya fue realizada---\n", id);
            listarTarea(Aux);
        } else printf ("\n---Tarea no encontrada---\n");
    }

    // Buscar por palabra

    size_t BuffSize = 100;
    char * Buff = malloc(BuffSize * sizeof(char));

    printf("\nIngrese la palabra a buscar: ");    
    getline(&Buff, &BuffSize, stdin);

    Buff[strlen(Buff) - 1] = '\0';

    Aux = buscarPorPalabra(StPendientes, Buff);

    

    free(Buff);
    liberar(StPendientes); free (StRealizadas);

    return 0;
}


TNodo * inicializarLista ()
{

    return NULL;
} 

void cargarTarea (TNodo ** StPendientes, Tareas TareasPendientes, int cant)
{
    size_t BuffSize = 100;
    char * Buff = malloc(BuffSize * sizeof(char));
    
    for (int i=0; i<cant; i++) {

        printf("\nIngrese la descripción de la tarea ID %d: ", i);
        getline(&Buff, &BuffSize, stdin);

        TareasPendientes.Descripcion = malloc((strlen(Buff)+1) * sizeof(char));
        strcpy (TareasPendientes.Descripcion, Buff);

        TareasPendientes.TareaID = i;
        TareasPendientes.Duracion = 10 + rand()%91;

        TNodo * NuevoNodo = crearNodo(TareasPendientes);
        NuevoNodo->sig = * StPendientes;
        * StPendientes = NuevoNodo;
    }

    //free(Buff);

}

TNodo * crearNodo (Tareas Tarea)
{
    TNodo * NNodo = (TNodo *) malloc(sizeof(TNodo));
    NNodo->Tarea.Descripcion = malloc(strlen(Tarea.Descripcion) * sizeof(char));
    strcpy(NNodo->Tarea.Descripcion, Tarea.Descripcion);
    NNodo->Tarea.TareaID = Tarea.TareaID;
    NNodo->Tarea.Duracion = Tarea.Duracion;
    NNodo->sig = NULL;
    return NNodo;
}



void listarTarea (TNodo * Tarea)
{

    if (Tarea) {
        printf("--------------------------------\n");
        printf("Tarea ID: %d\n", Tarea->Tarea.TareaID);
        printf("Descripcion: %s", Tarea->Tarea.Descripcion);
        printf("Duracion: %d\n", Tarea->Tarea.Duracion);

    }
}

void preguntarRealizada (TNodo ** StPendientes, TNodo ** StRealizada, int cant)
{
        int real;

        TNodo ** Aux;
        TNodo ** AuxAnt = Aux;

        * Aux = (TNodo *) malloc (sizeof(TNodo));
        * AuxAnt = (TNodo *) malloc (sizeof(TNodo));

        * Aux = * StPendientes;


        while (* Aux)
        {
            listarTarea(* Aux);

            printf("Ya se realizó esta tarea? (1 para SI): ");
            scanf("%d", &real);
            getchar();
        
            if (real == 1) {
                printf("\nTarea %d realizada! \n ", (* Aux)->Tarea.TareaID);

                cambiarRealizada(StRealizada, StPendientes, Aux);                

            } else {
            * AuxAnt = * Aux;
            * Aux = (* Aux)->sig;
            }
        }
}

void cambiarRealizada (TNodo ** StRealizada, TNodo ** StPendientes, TNodo ** Aux)
{
    TNodo * NuevoN = * StRealizada;
    NuevoN = (TNodo *) malloc(sizeof(TNodo));
    NuevoN = * Aux;
    quitarNodo(StPendientes, Aux);

    NuevoN->sig = * StRealizada;
    * StRealizada = NuevoN;
}

void quitarNodo (TNodo ** Start, TNodo ** Aux)
{
    if (* Start == * Aux)
    {
        * Start = (* Aux)->sig;
        * Aux = (* Start);
    }

    else {
        TNodo * AuxAnt;
        TNodo * AuxAux = * Start;
        while (AuxAux && * Aux != AuxAux)
        {
            AuxAnt = AuxAux;
            AuxAux = AuxAux->sig;
        }

        if (AuxAux)
        {
            AuxAnt->sig = AuxAux->sig;

            * Aux = AuxAux->sig;
        }

        }
}

TNodo * buscarPorID (TNodo ** Start, int idBus)

{
    TNodo * Aux = * Start;

    while((Aux) && (Aux)->Tarea.TareaID != idBus)
        Aux = (Aux)->sig;

    return Aux;
}

TNodo * buscarPorPalabra (TNodo ** Start, char * Buff)

{
    TNodo * Aux = * Start;

    while(Aux && !(strstr(Aux->Tarea.Descripcion, Buff)))
    {
        Aux = Aux->sig;
    }
    return Aux;
}


void liberar (TNodo ** Lista)
{
    TNodo * Aux = * Lista;
    while (Aux) {
        * Lista = Aux;
        Aux = Aux->sig;
        free(* Lista);
    }

    free(Lista);
}
