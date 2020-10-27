#include <stdio.h>

void Importar(char* nombre, HashMap* map);

int menu (HashMap* map)
{
    char opcion;
    int flag = -1;
    printf("Bienvenido a tu GPS\n");

    while(flag != 0)
    {
        printf("\n");
        printf("¿Que deseas hacer?\n a) Buscar la ciudad mas cercana\n b) Crear tu propia ruta\n c) Encontrar la ruta mas corta\n d) Encontrar el mejor circuito\n e) Importar ciudades nuevas a tu GPS\n \n Si no quieres hacer nada presiona ENTER\n");
        fflush(stdin);
        scanf("%c", &opcion);
        switch (opcion)
        {
            case 'a':
            {
                char nombre[10];
                printf("Ingresa el nombre de la ciudad de la cual quieres saber la ciudad mas cercana\n");
                fflush(stdin);
                scanf("%s", nombre);
                CiudadMasCercana(map, nombre);
                break;
            }
            case 'b':
            {
              char origen[10];
              printf("Ingresa el nombre de la ciudad donde quieres comenzar tu ruta\n");
              fflush(stdin);
              scanf("%s", origen);
              CrearRuta(map, origen, destino);
              break;
            }
            case 'c':
            {
              char origen[10];
              char destino[10];
              printf("Ingresa el nombre de la ciudad donde quieres comenzar tu ruta\n");
              fflush(stdin);
              scanf("%s", origen);
              printf("Ingresa el nombre de la ciudad donde quieres terminar tu ruta\n");
              fflush(stdin);
              scanf("%s", destino);
              RutaOptima(map, origen, destino);
              break;
            }
            case 'e':
            {
                char archivo[20];
                printf("Ingrese el nombre del archivo a importar (Sin formato)\n");
                fflush(stdin);
                scanf("%s", archivo);
                Importar(archivo, map);
                break;
            }
            case '\n':
            {
                flag = 0;
                break;
            }
            default:
            {
                printf("Entrada no valida\n");
                printf("\n");
                break;
            }        
        }
    }
    return 0;
}