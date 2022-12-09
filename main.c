#include <stdio.h>
#include <string.h>

struct productos{
    int identificador;
    char descripcion [200];
    double price;
    int stock;
};

//PROTOTIPOS//
void albaranes(int numarticulo, int cantidad);
void factura(struct productos producto[15], struct productos DatosdelProducto[15], int *NumerodePedidos); //No se si esta deberia de ser int ya que dice que se pondra a 0 despues de visualizar miradlo pls
void nuevoarticulo(void); //Tampoco se si la variable descripcion esta bien definida asi, habra que utilizar un getch o algo asi

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
void albaranes(int numarticulos, int cantidad) {
    int p;



    printf("Introduzca el numero de articulos que tiene el albaran:\n");
    scanf("%d", &p);
    int identificador[p];
    int cantidades[p];
    if ((p >= 1) && (p <= 5)) {
        for (int i = 0; i < p; ++i) {
            do {
                printf("Articulo %d:\n", i);

                scanf("%d", &identificador[i]);

                printf("Cantidad:\n");
                scanf("%d", &cantidades[i]);


            } while ((identificador[i] < 1) || (identificador[i] > 15) || (cantidades[i] <= 0));
            for (int j = 0; j < i; ++j) {
                if (identificador[i] == identificador[j]) {
                    printf("El articulo pedido ya se añadio. No se añadio nada de la peticion anterior!\n");
                    i--;
                }
            }
        }
    }else printf("No se admiten mas de 5 articulos\n");
}
void factura(struct productos producto[15], struct productos DatosdelProducto[15], int *NumerodePedidos) {

    int CantidadObjetos, Nopedido = 0;
    int LimiteDescripcion; //Usado para mostrar la tabla a la izquierda de la pantalla
    double CantidadTotal = 0;

    printf("\n\t-= OPCION 2 | RECIBO DE LA FACTURA =-\n\n");

    for (int i = 0; i < 15; ++i) {
        if (producto[i].stock == DatosdelProducto[i].stock) Nopedido++; //Comprueba que ningun pedido se ha realizado y muestra un mensaje de error
    }
    if (Nopedido == 15) {
        printf("No has pedido nada.\nPara ello, selecciona la Opcion 1.\n\n");
        return;
    }

    for (int i = 0; i < 15; ++i) { //Busca la descripcion maxima para poner la tabla
        if (producto[i].stock != DatosdelProducto[i].stock)
            if (strlen(producto[i].descripcion) > LimiteDescripcion)
                LimiteDescripcion = strlen(producto[i].descripcion); //Establece la longitud maxima
    }
    printf("%*s  %10s  %10s  %10s\n", LimiteDescripcion, "DESCRIPCION", "CANTIDAD", "PRECIO", "IMPORTE"); //MOSTRAR LA TABLA CON LOS OBJETOS PEDIDOS
    for (int i = 0; i < 15; ++i) {
        if (producto[i].stock != DatosdelProducto[i].stock) { //Imprime los objetos pedidos mientras que el stock no se haya acabado
            CantidadObjetos = DatosdelProducto[i].stock - producto[i].stock; //Calcula la cantidad de objetos basado en la diferencia entre el stock inicial y el actual
            printf("%*s  %10d  %10.2f  %10.2f\n", LimiteDescripcion, producto[i].descripcion, CantidadObjetos, producto[i].price, producto[i].price * CantidadTotal);
            CantidadTotal += CantidadObjetos * producto[i].price; //Calcula el importe total para todos los objetos
            DatosdelProducto[i].stock = producto[i].stock; //Actualiza los datos del stock inicial para siguientes facturas;
        }
    }
    printf("\n-> TOTAL: %.2f\n\n\n", CantidadTotal); //Imprime el importe total para todos los objetos

    //RESET
    *NumerodePedidos = 5; //Establece a 0 el numero de pedidos para permitir al usuario pedir nuevos pedidos otra vez
}
