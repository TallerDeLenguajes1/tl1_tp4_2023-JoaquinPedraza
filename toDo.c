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

struct Tarea *BuscaTareaPorId(struct Tarea **T1, struct Tarea **T2, int idTarea, int numTareas);

struct Tarea *BuscaTareaPorPalabra(struct Tarea **T1, struct Tarea **T2, char *palabraClave, int numTareas);

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
      printf("\n=============");
      printf("\nId_Tarea: %d", tareasRealizadas[i]->TareaID);
      printf("\nDescripcion: %s", tareasRealizadas[i]->Descripcion);
      printf("\nDuracion: %i min", tareasRealizadas[i]->Duracion);
    }
  }

  printf("\n<-----------Tareas pendientes---------------->");
  for (int i = 0; i < nTareas; i++)
  {

    if (tareasPendientes[i] != NULL)
    {
      printf("\n=============");
      printf("\nId_Tarea: %d", tareasPendientes[i]->TareaID);
      printf("\nDescripcion: %s", tareasPendientes[i]->Descripcion);
      printf("\nDuracion: %i min", tareasPendientes[i]->Duracion);
    }
  }
  char respuesta;

  while (1)
  {
    printf("\n¿Desea buscar una tarea por ID:? (S/N): ");
    fflush(stdin);
    scanf(" %c", &respuesta);

    if (respuesta == 'S' || respuesta == 's')
    {
      int id_Tarea;
      printf("Ingrese el Id de la tarea que desea buscar\n");
      scanf("%d", &id_Tarea);
      struct Tarea *tareaBuscadaPorId = BuscaTareaPorId(tareasPendientes, tareasRealizadas, id_Tarea, nTareas);
      if (tareaBuscadaPorId != NULL)
      {
        printf("\n======Tarea Encontrada=======");
        printf("\nId_Tarea: %d", tareaBuscadaPorId->TareaID);
        printf("\nDescripcion: %s", tareaBuscadaPorId->Descripcion);
        printf("\nDuracion: %i min", tareaBuscadaPorId->Duracion);
      }
      else
      {
        printf("\n======Tarea No Encontrada=======");
      }

      break;
    }
    else if (respuesta == 'N' || respuesta == 'n')
    {
      printf("Saliendo...\n");
      break;
    }
    else
    {
      printf("Respuesta inválida. Por favor, responde con 'S' o 'N'.\n");
    }
  }

  while (1)
  {
    printf("\n¿Desea buscar una tarea por palabra clave:? (S/N): ");
    fflush(stdin);
    scanf(" %c", &respuesta);

    if (respuesta == 'S' || respuesta == 's')
    {
      char palabraClave[50];
      printf("Ingrese la palabra clave:\n");
      fflush(stdin);
      gets(palabraClave);
      struct Tarea *tareaBuscadaPorPalabra = BuscaTareaPorPalabra(tareasPendientes, tareasRealizadas, palabraClave, nTareas);
      if (tareaBuscadaPorPalabra != NULL)
      {
        printf("\n======Tarea Encontrada=======");
        printf("\nId_Tarea: %d", tareaBuscadaPorPalabra->TareaID);
        printf("\nDescripcion: %s", tareaBuscadaPorPalabra->Descripcion);
        printf("\nDuracion: %i min", tareaBuscadaPorPalabra->Duracion);
      }
      else
      {
        printf("\n======Tarea No Encontrada=======");
      }

      break;
    }
    else if (respuesta == 'N' || respuesta == 'n')
    {
      printf("Saliendo...\n");
      break;
    }
    else
    {
      printf("Respuesta inválida. Por favor, responde con 'S' o 'N'.\n");
    }
  }

  return 0;
}

struct Tarea *BuscaTareaPorId(struct Tarea **T1, struct Tarea **T2, int idTarea, int numTareas)
{
  struct Tarea *TareaBuscada = NULL;
  for (int i = 0; i < numTareas; i++)
  {
    if (T1[i] != NULL)
    {
      if (T1[i]->TareaID == idTarea)
      {
        TareaBuscada = T1[i];
      }
    }
    else if (T2[i]->TareaID == idTarea)
    {
      TareaBuscada = T2[i];
    }
  }
  return TareaBuscada;
}

struct Tarea *BuscaTareaPorPalabra(struct Tarea **T1, struct Tarea **T2, char *palabraClave, int numTareas)
{
  struct Tarea *TareaBuscada = NULL;
  for (int i = 0; i < numTareas; i++)
  {
    if (T1[i] != NULL)
    {
      if (strstr(T1[i]->Descripcion, palabraClave))
      {
        TareaBuscada = T1[i];
      }
    }
    else if (strstr(T2[i]->Descripcion, palabraClave))
    {
      TareaBuscada = T2[i];
    }
  }
  return TareaBuscada;
}