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
void cargarTarea (TNodo **, Tareas, int id);
TNodo * crearNodo (Tareas);
void listarTarea (TNodo *);
void preguntarRealizada (TNodo **, TNodo **);
void cambiarRealizada (TNodo ** , TNodo **, int);
TNodo * quitarNodo (TNodo **, int);
TNodo * buscarPorID (TNodo ** Start, int idBus);
TNodo * buscarPorPalabra (TNodo ** Start, char *);
void liberar (TNodo **);


int main ()
{
    srand(time(NULL));

    int cant, id, i = 0;
    TNodo ** StPendientes, ** StRealizadas;
    Tareas Tarea;

    StPendientes = (TNodo **) malloc(sizeof(TNodo *));
    StRealizadas = (TNodo **) malloc(sizeof(TNodo *));

   * StPendientes = inicializarLista();
   * StRealizadas = inicializarLista();


    do {
    i ++;
    cargarTarea(StPendientes, Tarea, i);
    
    printf("Desea ingresar otra tarea ? (Cualquier num seguir / 0 Fin): ");
    scanf("%d", &cant);
    getchar();
    } while (cant);

    preguntarRealizada(StPendientes, StRealizadas);

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

    if (Aux)
    {
        printf("\n---La Tarea sigue pendiente---\n");
        listarTarea(Aux);
    } else {

        Aux = buscarPorPalabra(StRealizadas, Buff);

        if (Aux)
        {
            printf("\n---La Tarea ya fue realizada---\n");
            listarTarea(Aux);
        } else printf ("\n---Tarea no encontrada---\n");
    }
    
    free(Buff);
    liberar(StPendientes); free (StRealizadas);

    return 0;
}


TNodo * inicializarLista ()
{

    return NULL;
} 

void cargarTarea (TNodo ** StPendientes, Tareas TareasPendientes, int id)
{
    size_t BuffSize = 100;
    char * Buff = malloc(BuffSize * sizeof(char));

    printf("\nIngrese la descripción de la tarea %d: ", id);
    getline(&Buff, &BuffSize, stdin);

    TareasPendientes.Descripcion = malloc((strlen(Buff)+1) * sizeof(char));
    strcpy (TareasPendientes.Descripcion, Buff);

    TareasPendientes.TareaID = id;
    TareasPendientes.Duracion = 10 + rand()%91;

    TNodo * NuevoNodo = crearNodo(TareasPendientes);
    NuevoNodo->sig = * StPendientes;
    * StPendientes = NuevoNodo;

    free(Buff);
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

void preguntarRealizada (TNodo ** StPendientes, TNodo ** StRealizada)
{
        int real;

        TNodo * Aux = * StPendientes;
        TNodo * AuxAux;

        while (Aux)
        {
            listarTarea(Aux);

            printf("Ya se realizó esta tarea? (1 para SI): ");
            scanf("%d", &real);
            getchar();

            AuxAux = Aux->sig;  
        
            if (real == 1)
            {
                printf("\nTarea %d realizada! \n ", Aux->Tarea.TareaID);
                cambiarRealizada(StRealizada, StPendientes, Aux->Tarea.TareaID);             
            } 

            Aux = AuxAux;       
        }
}

void cambiarRealizada (TNodo ** StOrg, TNodo ** StDst, int id)
{
    TNodo * Aux;

    Aux = quitarNodo(StDst, id);
    TNodo * NuevoN = * StOrg;
    NuevoN = (TNodo *) malloc(sizeof(TNodo));
    NuevoN = Aux;

    NuevoN->sig = * StOrg;
    * StOrg = NuevoN;
}

TNodo * quitarNodo (TNodo ** Start, int id)
{
    TNodo * Aux = * Start;
    TNodo * AuxAnt;

    while (Aux && Aux->Tarea.TareaID !=id)
    {
        AuxAnt = Aux;
        Aux = Aux->sig;
    }

    if (Aux)
    {
        if (Aux == * Start)
        {
            * Start = Aux->sig;
        }   
        else {
        
            AuxAnt->sig = Aux->sig;
        }

    }

    return Aux;
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
