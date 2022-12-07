#include <stdio.h>
#define LISTA 15
void albaranes(int numarticulo, int cantidad);
void factura(int identificador, int cantidad, float precio, float importe); //No se si esta deberia de ser int ya que dice que se pondra a 0 despues de visualizar miradlo pls
void nuevoarticulo(void); //Tampoco se si la variable descripcion esta bien definida asi, habra que utilizar un getch o algo asi
typedef struct
{
    char descripcion[150];
    int cantidad;
    float precio;
    int lleno;
}list;
list l_items[LISTA];
int main() {
    int ops;
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
                albaranes(numarticulo, cantidad);
                break;
            case 2:
                printf("2. Confeccion de factura\n");
                break;
            case 3:
                printf("3. Introduccion de nuevo articulo\n");
                nuevoarticulo();
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
void albaranes(int numarticulo, int cantidad) {
    int i=1, p ;
    printf("Cuantos albaranes quieres hacer:\n");
    scanf("%d", &p);
    do {

        printf("Albaran %d\n", i++);

            printf("Num\n");
            scanf("%d", &numarticulo);
            printf("Cant\n");
            scanf("%d", &cantidad);



    }while(i<=p);
}
void nuevoarticulo(void)
{
    int i, j;
    printf("Introduzca el nuevo articulo:\n");
    for(i=0;i<LISTA ;i++)
    {
        if(l_items[i].lleno==0)
        {
            printf("Introduce los datos requeridos:\n Descripcion:");
            fflush(stdin);
            fgets(l_items[i].descripcion,150,stdin);
            //
            printf("cantidad:\n ");
            scanf("%d",&l_items[i].cantidad);
            printf("Precio:\n ");
            scanf("%f",&l_items[i].precio);
            l_items[i].lleno=1;
            break;
        }else if (l_items[LISTA-1].lleno==1)
            printf("No hay espacio disponible maldito cabron");

    }
}
