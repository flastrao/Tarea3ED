#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap.h"
#include "hashmap.c"
#include "lectura_csv.c"
#include "menu.c"

typedef struct 
{
    char* nombre;
    HashMap* distancias;
} ciudad; //Estructura de cada ciudad, tiene su nombre y una distancia

ciudad * crearCiudad() //Funcion que crea una ciudad
{
    ciudad* input = (ciudad *) calloc (1, sizeof(ciudad)); 
    input->nombre = (char *) calloc (20, sizeof(ciudad));
    input->distancias = createMap(50);
    return input;
}
void agregaInfo (HashMap* ciudades, char* ciudad1, char* ciudad2, int distancia)
{
    ciudad* c1 = searchMap(ciudades, ciudad1); 
    ciudad* c2 = searchMap(ciudades, ciudad2);

    if(c1 == NULL) //Si la ciudad1 no se encuentra:
    {
        c1 = crearCiudad(); //Se crea una ciudad respecto a c1
        insertMap(ciudades, ciudad1, c1); //Se inserta la ciudad1 en el mapa de ciudades
    }

    if(c2 == NULL) 
    { 
        c2 = crearCiudad(); //Se crea una ciudad c2
        insertMap(ciudades, ciudad2, c2);
    }

    insertMap(c1->distancias, ciudad2, &distancia);
    insertMap(c2->distancias, ciudad1, &distancia);
}

int main()
{
    HashMap* map = createMap(50);
    char* ciudad1;
    char* ciudad2;
    int distancia = 0;
    FILE* Ciudades = fopen("distances.txt", "r");
    char line[30];
    while(fgets(line, 29, Ciudades) != NULL)
    {
        ciudad1 = (char *) get_csv_field(line, 0);
        ciudad2 = (char *) get_csv_field(line, 1);
        distancia = atoi(get_csv_field(line, 2));
        agregaInfo(map, ciudad1, ciudad2, distancia);
    }

    fclose(Ciudades);
    free(Ciudades);
    menu(map);
    return 0;
}

/* FUNCIONES */
void Importar(char* nombre, HashMap* map) //Esta funcion importa ciudades desde un archivo ingresado por el usuario 
{
    FILE* input;
    char nombre_Archivo[20];
    snprintf(nombre_Archivo, sizeof(nombre_Archivo), "%s%s", nombre, ".txt");
    input = fopen(nombre_Archivo, "r");
    int cont = 0;
    if(input == NULL)
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
  int pos = 0;
  while(map->buckets[pos] != NULL)
  {
    if(strcmp(map->buckets[pos]->key, ciudad) == 0)
    {
      flag++;
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
  //Se revisa que la ciudad de origen este en el mapa
  int flag = 0;
  int pos = 0;
  while(map->buckets[pos] != NULL)
  {
    if(strcmp(map->buckets[pos]->key, ciudad) == 0)
    {
      flag++;
      break;
    }
  }

  if(flag == 0)
  {
    printf("No se encontro la ciudad de origen en tu GPS\n");
    return;
  }

  //A partir de una ciudad se va mostrando por pantalla los nombres de las ciudades adyacentes y el usuario va ingresando el nombre de la ciudad a la cual quiere ir
}

void RutaOptima(HashMap* map, char* origen, char* destino)
{
  //Algoritmo de Dijkstra
}
