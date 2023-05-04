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
void menu (TNodo **, TNodo **, TNodo **, Tareas);
int interfazCarga (TNodo **, Tareas, int);
void cargarTarea (TNodo **, Tareas, int id);
TNodo * crearNodo (Tareas);
void listarTarea (TNodo *);
void cambiarTareas (TNodo **, TNodo **, TNodo **);
void moverTarea (TNodo ** , TNodo **, int);
TNodo * quitarNodo (TNodo **, int);
TNodo * buscarPorID (TNodo ** Start, int idBus);
void eliminarTarea (TNodo ** Start, int idBus);
void mostrarTareas (TNodo **, TNodo **, TNodo **);
void mostrarDatos (TNodo **);
void eliminarTarea (TNodo **, int);
void liberar (TNodo **);


int main ()
{
    srand(time(NULL));

    TNodo ** StPendientes, ** StRealizadas, ** StProceso;
    Tareas Tarea;

    StPendientes = (TNodo **) malloc(sizeof(TNodo *));
    StProceso = (TNodo **) malloc(sizeof(TNodo *));
    StRealizadas = (TNodo **) malloc(sizeof(TNodo *));

   * StPendientes = inicializarLista();
   * StRealizadas = inicializarLista();
   * StRealizadas = inicializarLista();


    menu (StPendientes, StProceso, StRealizadas, Tarea);

    liberar(StPendientes); liberar(StRealizadas); liberar(StProceso);

    return 0;
}


TNodo * inicializarLista ()
{

    return NULL;
} 

void menu (TNodo ** StPendientes, TNodo ** StProceso, TNodo ** StRealizadas, Tareas Tarea)
{
    int selec, flag = 1, id = 0;
    while (flag)
    {
        printf("\n---------------------------");
        printf("\n1. Ingresar nueva tarea");
        printf("\n2. Cambiar una tarea");
        printf("\n3. Salir");
        printf("\n---------------------------\n\n");
        scanf("%d", &selec);
        getchar();

        switch (selec)
        {
            case 1: id = interfazCarga(StPendientes, Tarea, id);
                break;
            case 2:
                cambiarTareas (StPendientes, StProceso, StRealizadas);
                break;
            case 3: flag = 0;
                break;
        } 
    }
}

int interfazCarga (TNodo ** StTarea, Tareas Tarea, int id)
{
    int cant;
    do {
    id ++;
    cargarTarea(StTarea, Tarea, id);
    
    printf("Desea ingresar otra tarea ? (Cualquier num seguir / 0 Fin): ");
    scanf("%d", &cant);
    getchar();
    } while (cant);

    return id;
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

void mostrarTareas (TNodo ** StPendientes, TNodo ** StProceso, TNodo ** StRealizadas)
{
    printf("\n // Tareas Pendientes //\n");
    mostrarDatos(StPendientes);

    printf("\n // Tareas en Proceso //\n");
    mostrarDatos(StProceso);

    printf("\n // Tareas Realizadas //\n");
    mostrarDatos(StRealizadas);
}

void cambiarTareas (TNodo ** StPendientes, TNodo ** StProceso, TNodo ** StRealizadas)

{
    int id, sel, op, mN = 1, tipoT = 0, flag = 1;
    TNodo * Aux;

    mostrarTareas (StPendientes, StProceso, StRealizadas);

    while (flag)
    {
        printf("\nID de la tarea: ");
        scanf("%d", &id);
        getchar();

        Aux = buscarPorID(StPendientes, id);

        TNodo ** Org, * Qn;

        if (Aux)
        {
            printf("\n---La Tarea %d sigue pendiente---\n", id);
            listarTarea(Aux);
            tipoT = 1;
            Org = StPendientes;
        } else {

            Aux = buscarPorID(StProceso, id);

            if (Aux)
            {
            printf("\n---La Tarea %d está en proceso---\n", id);
            listarTarea(Aux);
            tipoT = 2;
            Org = StProceso;
            } else {
                Aux = buscarPorID(StRealizadas, id);

                if (Aux)
                {
                    printf("\n---La Tarea %d ya fue realizada---\n", id);
                    listarTarea(Aux);
                    tipoT = 3;
                    Org = StRealizadas;
                } else {
                    printf ("\n---Tarea no encontrada---\n");
                    mN = 0;
                }
            }
        }

        if (mN)
        {
            printf("\n1. Mover tarea");
            printf("\n2. Eliminar tarea");
            printf("\n3. Volver\n");

            scanf("%d", &sel);
            getchar();

            switch (sel) {
            case 1:
            if (tipoT == 2 || tipoT == 3)
                printf("\n1. Mover a Pendientes");

            if (tipoT == 1 || tipoT == 3)   
                printf("\n2. Mover a en Proceso");

            if (tipoT == 1 || tipoT == 2)
                printf("\n3. Mover a Realizadas\n");

                    scanf("%d", &op);
                    getchar();

                switch (op) {
                case 1: moverTarea(StPendientes, Org, id);
                    printf("\n---Tarea movida %d a Pendientes---", id);
                    break;
                case 2: moverTarea(StProceso, Org, id);
                    printf("\n---Tarea movida %d a En Proceso---", id);
                    break;
                case 3: moverTarea(StRealizadas, Org, id);
                    printf("\n---Tarea %d movida a Realizadas---", id);
                }
                    break;
            case 2: 
                Qn = quitarNodo(Org, id); free (Qn);
                printf("\n---Tarea eliminada---\n");
                break;
            case 3:
                flag = 0;
                mostrarTareas(StPendientes, StProceso, StRealizadas);
                break;
            }
        }
        if (flag)
        {
            printf("\nDesea modificar otra tarea? (0 No / otro núm Si)\n");
            scanf("%d", &op);
            getchar();
            mN = 1;
            if (!op)
            {
                flag = 0;
                mostrarTareas(StPendientes, StProceso, StRealizadas);
            }
        }
    }
}


void moverTarea (TNodo ** StDst, TNodo ** StOrg, int id)
{
    TNodo * Aux;

    Aux = quitarNodo(StOrg, id);
    TNodo * NuevoN = * StDst;
    NuevoN = (TNodo *) malloc(sizeof(TNodo));
    NuevoN = Aux;

    NuevoN->sig = * StDst;
    * StDst = NuevoN;
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


void mostrarDatos (TNodo ** Tarea)
{
    int canT = 0, tiempo = 0;

    TNodo * Aux = * Tarea;
    while (Aux)
    {
        listarTarea(Aux);
        tiempo += Aux->Tarea.Duracion;
        Aux = Aux->sig;
        canT++;
    }

    if (canT > 0) {
    printf("\n---Cantidad de tareas: %d---", canT);
    printf("\n---Tiempo total: %d---\n", tiempo);
    } else printf("---Ninguna tarea por el momento---\n");

    printf("------------------------------");
    printf("\nPulse la tecla Enter para continuar...");
    getchar();
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
