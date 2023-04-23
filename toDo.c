#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// cSpell:disable

struct Tarea
{
  int TareaID; // Numerado en ciclo iterativo
  char *Descripcion;
  int Duracion; // entre 10 – 100
};

int main()
{

  int nTareas;
  printf("De cuantas tareas desea hacerse cargo: ");
  scanf("%d", &nTareas);

  struct Tarea **tareasPendientes;

  tareasPendientes = (struct Tarea **)malloc(sizeof(struct Tarea *) * nTareas);

  for (int i = 0; i < nTareas; i++)
  {
    tareasPendientes[i] = NULL;
  }

  for (int i = 0; i < nTareas; i++)
  {
    tareasPendientes[i] = (struct Tarea *)malloc(sizeof(struct Tarea));
    tareasPendientes[i]->TareaID = i + 1;
    char *buffer;
    buffer = (char *)malloc(sizeof(char) * 255);
    printf("Ingresar la descripcion: ");
    fflush(stdin);
    gets(buffer);
    fflush(stdin);
    tareasPendientes[i]->Descripcion = (char *)malloc(sizeof(char) * (strlen(buffer) + 1));
    strcpy(tareasPendientes[i]->Descripcion, buffer);
    free(buffer);
    tareasPendientes[i]->Duracion = 10 + rand() % 100;
  }
  struct Tarea **tareasRealizadas;

  tareasRealizadas = (struct Tarea **)malloc(sizeof(struct Tarea *) * nTareas);

  for (int i = 0; i < nTareas; i++)
  {
    tareasRealizadas[i] = NULL;
  }

  for (int i = 0; i < nTareas; i++)
  {
    char fueRealizada;
    printf("La tarea %s fue realizada?, (S/N)", tareasPendientes[i]->Descripcion);
    fflush(stdin);
    scanf("%c", &fueRealizada);
    if (fueRealizada == 'S' || fueRealizada == 's')
    {
      tareasRealizadas[i] = tareasPendientes[i];
      tareasPendientes[i] = NULL;
    }
  }

  printf("\n<-----------Tareas Realizadas con exito---------------->");
  for (int i = 0; i < nTareas; i++)
  {

    if (tareasRealizadas[i] != NULL)
    {
      printf("\nTarea: %s", tareasRealizadas[i]->Descripcion);
      printf("\nDuracion: %i", tareasRealizadas[i]->Duracion);
    }
  }

  printf("\n<-----------Tareas pendientes---------------->");
  for (int i = 0; i < nTareas; i++)
  {

    if (tareasPendientes[i] != NULL)
    {
      printf("\nTarea: %s", tareasPendientes[i]->Descripcion);
      printf("\nDuracion: %i", tareasPendientes[i]->Duracion);
    }
  }
  return 0;
}