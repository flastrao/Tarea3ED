#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap.h"
#include "hashmap.c"
#include "list.h"
#include "list.c"
#include "heap.h"
#include "heap.c"
#include "lectura_csv.c"
#include "menu.c"

typedef struct //Struct para el mapa principal
{
    char* nombre;
    HashMap* distancias;
} Ciudad;

typedef struct //Struct para el mapa de distancias de cada una de las ciudades 
{
    char *nombre;
    int dis;
} Info_Distancias;


Ciudad * crearCiudad(char * nombre) //Funcion que inicializa variables de mapa principal
{
    Ciudad* input = (Ciudad *) calloc (1, sizeof(Ciudad));
    input->nombre = nombre;
    input->distancias = createMap(50);
    return input;
}

Info_Distancias* crearDistancia(int distancia) //Funcion que inicializa variables del mapa distancia
{
    Info_Distancias* input = (Info_Distancias *) calloc (1, sizeof(Info_Distancias));
    input->nombre = (char *) calloc (30, sizeof(char));
    input->dis = distancia;
    return input;
}

void agregaInfo (HashMap* map, char* ciudad1, char* ciudad2, int distancia) //Funcion que agrega informacion a los mapas correspondientes
{
    Ciudad* c1 = searchMap(map, ciudad1); //Se busca la ciudad en el mapa
    if(c1 == NULL) //Esta ciudad no se encuentra en el mapa, por lo tanto se crea una nueva ciudad y se ingresa al mapa
    {
        c1 = crearCiudad(ciudad1);
        insertMap(map, ciudad1, c1);
    }
    
    Ciudad* c2 = searchMap(map, ciudad2);
    if(c2 == NULL)
    { 
        c2 = crearCiudad(ciudad2);
        insertMap(map, ciudad2, c2);
    }

    Info_Distancias* datos = crearDistancia(distancia);

    datos->nombre = ciudad1;
    insertMap(c1->distancias, ciudad2, datos); //Se ingresa ciudad 2 al mapa de distancias de ciudad 1

    datos->nombre = ciudad2;
    insertMap(c2->distancias, ciudad1, datos); //Se ingresa ciudad 1 al mapa de distancias de ciudad 2
}

int main()
{
    HashMap* map = createMap(50);
    char* ciudad1;
    char* ciudad2;
    int distancia = 0;
    FILE* Ciudades = fopen("distances.csv", "r");
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
void Importar(HashMap* map, char* nombre) //Esta funcion importa ciudades desde un archivo ingresado por el usuario 
{
    FILE* input;
    char nombre_Archivo[20];
    snprintf(nombre_Archivo, sizeof(nombre_Archivo), "%s%s", nombre, ".csv");
    input = fopen(nombre_Archivo, "r");
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
    printf("Archivo importado!\n");
}

void CiudadMasCercana(HashMap* map, char* origen) //Funcion que muestra por pantalla la ciudad mas cercana a una ciudad ingresada por el usuario
{
    Ciudad* c_origen = searchMap(map, origen); //Se busca la ciudad de origen en el mapa principal
    if(c_origen == NULL)
    {
        printf("La ciudad de origen no se encuentra almacenada en tu GPS\n");
        return;
    }

    //Se recorre el mapa de distancias de la ciudad ingresada para encontrar la ciudad mas cercana
    Info_Distancias* aux = firstMap(c_origen->distancias);
    Info_Distancias* mas_cercana = aux;
    while(aux != NULL)
    {
        if(mas_cercana->dis > aux->dis)
        {
            mas_cercana->nombre = aux->nombre;
            mas_cercana->dis = aux->dis;
        }
        aux = nextMap(c_origen->distancias);
    }
    printf("La ciudad mas cercana a %s es %s con %i Km de distancia\n", origen, mas_cercana->nombre, mas_cercana->dis);
}

void CrearRuta(HashMap* map, char* origen) //Funcion que permite crear una ruta al usuario
{
    Ciudad* aux = searchMap(map, origen); //Se busca la ciudad de origen en el mapa
    if(aux == NULL)
    {
        printf("La ciudad de origen no se encuentra almacenada en tu GPS\n");
        return;
    }

    while(1) //Ciclo que va preguntando al usuario a cual de ciudades que se imprimen por pantalla quiere ir para ir armando una ruta
    {
        //Se imprime por pantalla las ciudades adyacentes a la ciudad en la cual esta actualmente el usuario
        Ciudad* aux_distancias = firstMap(aux->distancias);
        while(aux_distancias != NULL)
        {
            printf("%s\n", aux_distancias->nombre);
            aux_distancias = nextMap(aux->distancias);
        }
        //Se le pregunta al usuario si desea continuar su ruta y de querer seguir se le pregunta a cual ciudad desea ir
        char validador[3];
        printf("¿Deseas continuar tu ruta? (INGRESE 'Si' o 'No' respetando mayusculas)\n");
        fflush(stdin);
        scanf("%s", validador);
        if(strcmp(validador, "No") == 0)
        {
            printf("Has terminado tu ruta\n");
            return;
        } 
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
/*
Heap* get_adyacent_nodes(HashMap* map, Ciudad* actual) //Funcion que crea un Heap con prioridad distancia entre ciudades con las ciudades adyacentes a la actual
{
    Heap* heap = createHeap();
    Info_Distancias* aux = firstMap(actual->distancias);
    //Se recorre el mapa distancias de la ciudad actual y se va ingresando al heap con prioridad de distancias entre ciudades
    while(aux != NULL)
    {
        heap_push(heap, aux, aux->dis);
        aux = nextMap(actual->distancias);
    }
    return heap;
}

void Ruta_Mas_Cercana(HashMap* map, char* origen, char* destino)
{
    Heap* heap = get_adyacent_nodes(map, origen); //Heap con las distancias a la ciudad actual
    Stack* S = createStack(); 
    push(S, heap_top(heap)); //Se ingresa la ciudad mas cercana a la ciudad actual a un stack
    Info_Distancias* actual = heap_top(heap);
    //Ciclo que va ingresando al stack las ciudades mas cercanas a la actual y verificando que la ciudad actual no sea el destino final
    while(1)
    {   
        if(strcmp(actual->nombre, destino) == 0) break; //Si se llego al destino
        else
        {
            heap = get_adyacent_nodes(map, actual); 
            push(S, heap_top(heap));
            actual = heap_top(heap);
        }
    }

    //Se imprime la ruta
    printf("La mejor ruta para ir de %s a %s es:\n", origen, destino);
    actual = top(S);
    while(actual != NULL)
    {
        printf("%s\n", actual->nombre);
        pop(S);
        actual = top(S);
    }
}
*/
void mostrartodo(HashMap* map) //SOLO PARA PRUEBAS
{
    Ciudad* aux = firstMap(map);
    while(aux != NULL)
    {
        printf("%s\n", aux->nombre);
        aux = nextMap(map);
    }
}