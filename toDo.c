#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// cSpell:disable

struct Tarea
{
  int TareaID; // Numerado en ciclo iterativo
  char *Descripcion;
  int Duracion; // entre 10 – 100
};

struct Nodo
{
  struct Tarea T;
  struct Nodo *Siguiente;
};

typedef struct Nodo *Lista;

Lista crearLista();
bool esListaVacia(Lista L);
struct Nodo *crearNuevaTarea();
void insertarAlFinal(Lista T, Lista *L);
void quitarNodo(Lista Nodo, Lista *L);
void mostrarLista(Lista L);
struct Nodo *buscarTareaPorId(Lista L, int idTarea);
struct Nodo *buscarTareaPorPalabra(Lista L, char *clave);

int main()
{

  // Se solicita conocer la cantidad de tareas
  int nTareas;
  printf("De cuantas tareas desea hacerse cargo: ");
  scanf("%d", &nTareas);

  // Cargo las tareas incialmente todas comienzan en el estado de tareas pendientes.
  Lista tareasPendientes = crearLista();

  for (int i = 0; i < nTareas; i++)
  {
    insertarAlFinal(crearNuevaTarea(i), &tareasPendientes);
  }

  Lista tareasRealizadas = crearLista();

  char respuesta;
  if (!esListaVacia(tareasPendientes)) // SI NO ESTA VACIA LAS TAREAS PENDIENTES
  {
    if ((tareasPendientes->Siguiente))
    {
      Lista recorrido = tareasPendientes;

      while (recorrido->Siguiente)
      {
        printf("La tarea %s fue realizada? (S/N)", recorrido->T.Descripcion);
        fflush(stdin);
        scanf("%c", &respuesta);

        if (respuesta == 'S')
        {
          quitarNodo(recorrido, &tareasPendientes);
          Lista Aux = recorrido;
          recorrido = recorrido->Siguiente;
          Aux->Siguiente = NULL;
          insertarAlFinal(Aux, &tareasRealizadas);
        }
        else
        {
          recorrido = recorrido->Siguiente;
        }
      }

      printf("La tarea %s fue realizada? (S/N)", recorrido->T.Descripcion);
      fflush(stdin);
      scanf("%c", &respuesta);

      if (respuesta == 'S')
      {
        quitarNodo(recorrido, &tareasPendientes);
        Lista Aux = recorrido;
        recorrido = recorrido->Siguiente;
        Aux->Siguiente = NULL;
        insertarAlFinal(Aux, &tareasRealizadas);
      }
    }
    else
    {
      printf("La tarea %s fue realizada? (S/N)", tareasPendientes->T.Descripcion);
      fflush(stdin);
      scanf("%c", &respuesta);

      if (respuesta == 'S')
      {
        insertarAlFinal(tareasPendientes, &tareasRealizadas);
        tareasPendientes = tareasPendientes->Siguiente;
      }
    }
  }
  printf("\n\n#####Tareas Pendientes#####");
  mostrarLista(tareasPendientes);
  printf("\n\n#####Tareas Realizadas#####");
  mostrarLista(tareasRealizadas);

  struct Nodo *tareaBuscadaPorId = buscarTareaPorId(tareasPendientes, 2);
  struct Nodo *tareaBuscadaPorPalabra = buscarTareaPorPalabra(tareasRealizadas, "mundo");
  return 0;
}

Lista crearLista()
{
  return NULL;
}
struct Nodo *crearNuevaTarea(int sucesorID)
{

  struct Nodo *nuevaTarea;
  nuevaTarea = (struct Nodo *)malloc(sizeof(struct Nodo));
  nuevaTarea->T.TareaID = sucesorID + 1;

  char *buffer;
  buffer = (char *)malloc(sizeof(char) * 255);
  printf("Ingresar la descripcion: ");
  fflush(stdin);
  gets(buffer);
  nuevaTarea->T.Descripcion = (char *)malloc(sizeof(char) * (strlen(buffer) + 1));
  strcpy(nuevaTarea->T.Descripcion, buffer);
  free(buffer);

  nuevaTarea->T.Duracion = 10 + rand() % 100;

  return nuevaTarea;
}
void insertarAlFinal(Lista nuevoNodo, Lista *L)
{
  if (!esListaVacia(*L))
  {
    Lista Aux = *L;
    while (Aux->Siguiente)
    {
      Aux = Aux->Siguiente;
    }
    nuevoNodo->Siguiente = Aux->Siguiente;
    Aux->Siguiente = nuevoNodo;
  }
  else
  {
    nuevoNodo->Siguiente = *L;
    *L = nuevoNodo;
  }
}
void quitarNodo(Lista Nodo, Lista *L)
{
  if (Nodo != *L)
  {
    Lista aux = *L;
    Lista AuxAnterior = *L;

    while (aux != Nodo)
    {
      AuxAnterior = aux;
      aux = aux->Siguiente;
    }
    AuxAnterior->Siguiente = aux->Siguiente;
  }
  else
  {
    *L = Nodo->Siguiente;
  }
}
bool esListaVacia(Lista L)
{
  return (L == NULL);
}
void mostrarLista(Lista L)
{
  int item = 0;
  if (!esListaVacia(L))
  {
    item++;
    while (L->Siguiente)
    {
      printf("\n\n========Item %d de la lista========", item);
      printf("\nID_Tarea: %d", L->T.TareaID);
      printf("\nDescripcion: %s", L->T.Descripcion);
      printf("\nTiempo de realizacion: %d min", L->T.Duracion);

      L = L->Siguiente;
      item++;
    }
    printf("\n\n========Item %d de la lista========", item);
    printf("\nID_Tarea: %d", L->T.TareaID);
    printf("\nDescripcion: %s", L->T.Descripcion);
    printf("\nTiempo de realizacion: %d min", L->T.Duracion);
  }
  else
  {
    printf("\n\nSin datos para mostrar");
  }
}

struct Nodo *buscarTareaPorId(Lista L, int idTarea)
{

  if (!esListaVacia(L))
  {
    while (L && L->T.TareaID != idTarea)
    {
      L = L->Siguiente;
    }
    return L;
  }
  else
  {
    return NULL;
  }
}

struct Nodo *buscarTareaPorPalabra(Lista L, char *clave)
{

  if (!esListaVacia(L))
  {
    while (L && strstr(L->T.Descripcion, clave) == clave)
    {
      L = L->Siguiente;
    }
    return L;
  }
  else
  {
    return NULL;
  }
}