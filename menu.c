#include <stdio.h>

void Importar(HashMap* map, char* nombre);
void CiudadMasCercana(HashMap* map, char* nombre);
void CrearRuta(HashMap* map, char* origen);

int menu (HashMap* map)
{
    char opcion;
    int flag = -1; //Variable que mantiene el menu en uso hasta que el usuario indica que no desea realizar otra accion
    printf("Bienvenido a tu GPS\n");

    while(flag != 0)
    {
        printf("\n");
        printf("¿Que deseas hacer?\n a) Buscar la ciudad mas cercana\n b) Crear tu propia ruta\n c) Encontrar la ruta mas corta\n d) Encontrar el mejor circuito\n e) Importar ciudades nuevas a tu GPS\n \n Si no quieres hacer nada presiona ENTER\n");
        fflush(stdin); //Se limpia stdin para que no guarde basura
        scanf("%c", &opcion);
        switch (opcion)
        {
            case 'a':
            {
                char nombre[10];
                printf("Ingresa el nombre de la ciudad de la cual quieres saber la ciudad mas cercana (Respete mayusculas e ignore espacios en caso de ser necesitados)\n");
                fflush(stdin);
                scanf("%s", nombre);
                CiudadMasCercana(map, nombre);
                break;
            }
            case 'b':
            {
              char origen[10];
              printf("Ingresa el nombre de la ciudad donde quieres comenzar tu ruta (Respete mayusculas e ignore espacios en caso de ser necesitados)\n");
              fflush(stdin);
              scanf("%s", origen);
              CrearRuta(map, origen);
              break;
            }
            case 'c':
            {
              char origen[10];
              char destino[10];
              printf("Ingresa el nombre de la ciudad donde quieres comenzar tu ruta (Respete mayusculas e ignore espacios en caso de ser necesitados)\n");
              fflush(stdin);
              scanf("%s", origen);
              printf("Ingresa el nombre de la ciudad donde quieres terminar tu ruta (Respete mayusculas e ignore espacios en caso de ser necesitados)\n");
              fflush(stdin);
              scanf("%s", destino);
              //RutaOptima(map, origen, destino);
              break;
            }
            case 'd':
            {
                char ciudad1[10];
                char ciudad2[10];
                char ciudad3[10];
                printf("Ingresa el nombre de la ciudad donde quieres comenzar tu ruta (Respete mayusculas e ignore espacios en caso de ser necesitados)\n");
                fflush(stdin);
                scanf("%s", ciudad1);
                printf("Ingresa el nombre de la segunda ciudad por donde quieres que pase tu ruta (Respete mayusculas e ignore espacios en caso de ser necesitados)\n");
                fflush(stdin);
                scanf("%s", ciudad2);
                printf("Ingresa el nombre de la tercera ciudad donde quieres que pase tu ruta (Respete mayusculas e ignore espacios en caso de ser necesitados)\n");
                fflush(stdin);
                scanf("%s", ciudad3);
                //MejorCircuito(map, ciudad1, ciudad2, ciudad3);
                break;          
            }
            case 'e':
            {
                char archivo[20];
                printf("Ingrese el nombre del archivo a importar (Sin formato)\n");
                fflush(stdin);
                scanf("%s", archivo);
                Importar(map, archivo);
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