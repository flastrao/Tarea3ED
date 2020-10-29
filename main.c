#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap.h"
#include "lectura_csv.c"
#include "menu.c"

typedef struct 
{
    char* nombre;
    HashMap* distancias;
} ciudad; //Estuctura de cada ciudad (Nombre y distancia)

ciudad * crearCiudad() //Funcion para crear una ciudad
{
    ciudad* input = (ciudad *) calloc (1, sizeof(ciudad)); //Se asigna memoria a la ciudad
    input->nombre = (char *) calloc (20, sizeof(char));
    input->distancias = createMap(50);
    return input; //Se retorna la ciudad creada
}
/*
typedef struct{
   char ciudad[30];
   int dist; 
   Node* prev; 
}Node;*/

void agregaInfo (HashMap* map, char* ciudad1, char* ciudad2, int distancia) //Funcion para agregar ciudades al un mapa
{
    ciudad* c1 = searchMap(map, ciudad1); //Se buscan en el mapa las ciudades 
    ciudad* c2 = searchMap(map, ciudad2);

    if(c1 == NULL) 
    {
        c1 = crearCiudad();
        insertMap(map, ciudad1, c1);
    }

    if(c2 == NULL) 
    { 
        c2 = crearCiudad();
        insertMap(map, ciudad2, c2);
    }

    insertMap(c1->distancias, ciudad2, &distancia);
    insertMap(c2->distancias, ciudad1, &distancia);
}

int main()
{
    HashMap* map = createMap(50); //Se crea el mapa
    char* ciudad1;
    char* ciudad2;
    int distancia = 0;
    FILE* Ciudades = fopen("distances.csv", "r"); //Se abre el archivo que contiene las ciudades y sus distancias
    char line[30];
    while(fgets(line, 29, Ciudades) != NULL)
    {
        ciudad1 = (char *) get_csv_field(line, 0);
        ciudad2 = (char *) get_csv_field(line, 1);
        distancia = atoi(get_csv_field(line, 2));
        agregaInfo(map, ciudad1, ciudad2, distancia); //Se van agregando las ciudades leidas al mapa correspondiente
    }

    fclose(Ciudades);
    free(Ciudades);
    menu(map);
    return 0;
}

/* FUNCIONES */

void Importar(char* nombre, HashMap* map) //Funcion que importa ciudades desde un archivo ingresado por el usuario 
{
    FILE* input;
    char nombre_Archivo[20];
    snprintf(nombre_Archivo, sizeof(nombre_Archivo), "%s%s", nombre, ".txt");
    input = fopen(nombre_Archivo, "r");
    int cont = 0;
    if(input == NULL) //Caso de que el archivo a leer no se encuentre
    {
        printf("No existe el archivo\n");
        return;
    }

    char* ciudad1;
    char* ciudad2;
    int distancia;
    char line[30];
    while(fgets(line, 29, input) != NULL)
    {
        ciudad1 = (char *) get_csv_field(line, 0);
        ciudad2 = (char *) get_csv_field(line, 1);
        distancia = atoi(get_csv_field(line, 2));
        agregaInfo(map, ciudad1, ciudad2, distancia);       
    }
    
    fclose(input);
    free(input);
    printf("Archivo importado exitosamente!\n");
}
 

void CiudadMasCercana (HashMap* map, char* ciudad)
{
  int distancia_mas_cercana = 0;
  char mas_cercana[10];

  int flag = 0;
  int cont = 0;
  int pos = 0;
  while(map != NULL)
  {
    if(firstMap(HashMap* map) != NULL){
      if(strcmp(map->buckets[cont]->key, ciudad) == 0)
      {
        flag++;
        break;
      }
      cont++;
    }
    else{
      printf("1");
      break;
    }
  }

  if(flag == 0)
  {
    printf("No se encontro la ciudad en tu GPS\n");
    return;
  }
  
  //Algoritmo de Dijkstra

}

void CrearRuta(HashMap* map, char* origen)
{
    ciudad* aux = searchMap(map, origen); //se crea un auxiliar a partir de la ciudad ingresada
    if(aux == NULL)
    {
        printf("La ciudad de origen no se encuentra almacenada en tu GPS\n"); //Caso de que no se encuentre la ciudad
        return;
    }

    while(1) //Si la ciudad se encuentra:
    {
        ciudad* aux_distancias = firstMap(aux->distancias);
        while(aux_distancias != NULL)
        {
            printf("%s\n", aux_distancias->nombre);
            aux_distancias = nextMap(aux->distancias);
        }
        char validador[3];
        printf("¿Deseas continuar tu ruta? (INGRESE 'Si' o 'No' respetando mayusculas)\n");
        fflush(stdin);
        scanf("%s", validador);
        if(strcmp(validador, "No") == 0) return;
        else
        {
            char ciudad_sgte[10];
            printf("¿A que ciudad deseas ir ahora?\n");
            fflush(stdin);
            scanf("%s", ciudad_sgte);
            aux = searchMap(map, ciudad_sgte);
        }

    }    
}

void RutaOptima(HashMap* map, char* origen, char* destino)
{
  //Algoritmo de Dijkstra
  


}
