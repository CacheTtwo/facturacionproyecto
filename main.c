#include <stdio.h>
#include <string.h>
#define LISTA 15
#define MAX_DESC 150
void albaranes(int numarticulo, int cantidad);
void factura(int identificador, int cantidad, float precio, float importe); //No se si esta deberia de ser int ya que dice que se pondra a 0 despues de visualizar miradlo pls
typedef struct
{
    char descripcion[MAX_DESC];
    int cantidad;
    float precio;
    int lleno;
}list;
list l_items[LISTA];
void nuevoarticulo(); //Tampoco se si la variable descripcion esta bien definida asi, habra que utilizar un getch o algo asi
void listalimpia();
int main() {
    int ops;
    listalimpia();
    do {
        printf("\n1. Introduccion de albaran\n");
        printf("2. Confeccion de factura\n");
        printf("3. Introduccion de nuevo articulo\n");
        printf("4. Salir del programa\n");
        printf("Elija una opcion:\n");
        scanf("%d", &ops);

        switch(ops) {
            case 1:
                printf("1. Introduccion de albaran\n");
                break;
            case 2:
                printf("2. Confeccion de factura\n");
                printf("----------------------------------------------------------------\n");
                printf("\t\tFactura -- Ferreteria Albacete --\n");
                printf("----------------------------------------------------------------\n");
                printf("\t Numero del articulo \t Cantidad \t Precio  Importe\n");
                printf("\t                  13 \t        6 \t   2.90    17.40\n");
                printf("----------------------------------------------------------------\n");
                printf("\t                                         TOTAL:  304.15\n");
                printf("----------------------------------------------------------------\n");
                break;
            case 3:

                nuevoarticulo();
                for(int i=0;i<LISTA;i++) {
                    printf("%s\n", l_items[i].descripcion);
                    printf("%d\n", l_items[i].cantidad);
                    printf("%.2f\n", l_items[i].precio);
                    printf("%d\n", l_items[i].lleno);
                }
                break;
            case 4:
                printf("4. Salir del programa\n");
                break;
            default:
                printf("La opcion no es valida\n");
        }
    } while(ops != 4);

    return 0;
}
void nuevoarticulo()
{
    int i;
    int aux=0;
    printf("Introduzca el nuevo articulo:\n");
    for(i=0;i<LISTA && aux==0;i++)
    {
        if(l_items[i].lleno==0) {
            printf("Introduce los datos requeridos:\n Descripcion:");
            fflush(stdin);
            fgets(l_items[i].descripcion, MAX_DESC, stdin);
            fflush(stdin);
            printf("cantidad:\n ");
            scanf("%d", &l_items[i].cantidad);
            printf("Precio:\n ");
            scanf("%f",&l_items[i].precio);
            l_items[i].lleno=1;
            break;
        }else if (l_items[LISTA-1].lleno==1)
            printf("No hay espacio disponible");


    }
}
void listalimpia()
{
    for (int i = 0; i <LISTA ; ++i)
    {
        l_items[i].lleno=0;
    }
}
