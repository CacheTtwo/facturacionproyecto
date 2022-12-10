#include <stdio.h>
#include <string.h>
#define LISTA 15
#define MAX_DESC 150

struct productos{
    int numarticulo;
    char descripcion[150];
    float precio;
    int stock;
    int lleno;
};
void albaranes(struct productos listaproductos[15]);
void factura(struct productos listaproductos[15], struct productos productosiniciales[15], int *numalbaranes);
void new_art(struct productos lista[LISTA]);
void cambio(char palabra[MAX_DESC]);

int main() {
    int ops, numalbaranes = 5;
    //Lista de productos
    struct productos listaproductos[15] = {{1, "Martillo de carpintero con mango de fibra de vidrio", 4.88, 50,1}, {2, "Maza de goma", 8.22, 4,1}, {3, "Juego de llaves combinadas", 11.99, 10,1}, {4, "Llave inglesa ajustable con tornillo", 5.54, 12,1}, {5, "Juego de laves Allen", 6.95, 20,1}, {6, "Juego de llaves de vaso", 21.99, 10,1}, {7, "Juego de destornilladores de precisión", 18.46, 15,1}, {8, "Pinza pelacables", 5.99, 3,1}, {9, "Alicates universales", 5.63, 12,1},{10, "Polimetro digital de bolsillo", 18.3, 7,1}, {11, "Polimetro digital multifuncion", 32.00, 12,1}};
    //Copia de la lista que utilizamos para realizar ciertas comprobaciones en la funcion 2
    struct productos productosiniciales[15] = {{1, "Martillo de carpintero con mango de fibra de vidrio", 4.88, 50,1}, {2, "Maza de goma", 8.22, 4,1}, {3, "Juego de llaves combinadas", 11.99, 10,1}, {4, "Llave inglesa ajustable con tornillo", 5.54, 12,1}, {5, "Juego de laves Allen", 6.95, 20,1}, {6, "Juego de llaves de vaso", 21.99, 10,1}, {7, "Juego de destornilladores de precisión", 18.46, 15,1}, {8, "Pinza pelacables", 5.99, 3,1}, {9, "Alicates universales", 5.63, 12,1}, {10, "Polimetro digital de bolsillo", 18.3, 7,1}, {11, "Polimetro digital multifuncion", 32.00, 12,1}};


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
                if (numalbaranes > 0) {
                    albaranes(listaproductos);
                    numalbaranes--; //Reduce en 1 (inicialmente vale 5) el numero de albaranes que podemos crear cada vez que vamos a la opcion 1
                } else printf("\nYa pediste 5 albaranes, no se admiten mas.\n\n");
                break;
            case 2:
                printf("2. Confeccion de factura\n");
                factura(listaproductos, productosiniciales, &numalbaranes);
                break;
            case 3:
                printf("3. Introduccion de nuevo articulo\n");
                new_art(listaproductos);
                for(int i=0;i<LISTA;i++) {
                    printf("%s\n", listaproductos[i].descripcion);
                    printf("%d\n", listaproductos[i].stock);
                    printf("%.2f\n", listaproductos[i].precio);
                    printf("El num de articulo es %d\n", listaproductos[i].numarticulo);
                    printf("%d\n", listaproductos[i].lleno);
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

void albaranes(struct productos listaproductos[15]) {
    int p;

    printf("Introduzca el numero de articulos que tiene el albaran:\n");
    scanf("%d", &p);
    int numarticulo[p];
    int cantidad[p]; //Listas que contienen el numero del articulo y su cantidad

    for (int i = 0; i < p; ++i) {
        do {
            printf("Articulo %d:\n", i+1);
            scanf("%d", &numarticulo[i]);
            printf("Cantidad:\n");
            scanf("%d", &cantidad[i]);
            if((numarticulo[i] < 1) || (numarticulo[i] > 15) || (cantidad[i] <= 0)) printf("Ese articulo no existe o la cantidad es negativa, vuelva a introducir los datos.\n");
        } while ((numarticulo[i] < 1) || (numarticulo[i] > 15) || (cantidad[i] <= 0)); //Si el articulo introducido no es valido por alguna de estas razones se vuelven a pedir los datos de este
        for (int j = 0; j < i; ++j) {
            if (numarticulo[i] == numarticulo[j]) {
                printf("Ese articulo ya esta en este albaran, no se puede repetir.\n");
                i--;
            } //Este if comprueba que cada articulo que pedimos no ha sido pedido ya anteriormente
        }
    }

    for (int i = 0; i < p; ++i) {
        for (int j = 0; j < 15; ++j) {
            if (numarticulo[i] == listaproductos[j].numarticulo) { //Buscamos el producto pedido en la lista de articulos
                if (cantidad[i] > listaproductos[j].stock) cantidad[i] = listaproductos[j].stock; //Si la cantidad pedida es mayor que el stock solo damos el stock que haya
                listaproductos[j].stock -= cantidad[i]; //Reducimos el stock del articulo segun la cantidad pedida
            }
        }
    }
}

void factura(struct productos listaproductos[15], struct productos produtosiniciales[15], int *numalbaranes) {
    int sin_pedidos = 0, cantidad;
    float preciototal = 0, importe;

    for (int i = 0; i < 15; ++i) {
        if (listaproductos[i].stock == produtosiniciales[i].stock) sin_pedidos++;
    }
    if (sin_pedidos == 15) {
        printf("No hay albaranes. Para mostrar la factura introduce uno primero.\n");
        return;
    } //Mediante el for y el if comprobamos si todavia no se ha introducido ningun albaran, en ese caso pedimos que se introduzca uno antes de mostrar una factura

    printf("----------------------------------------------------------------\n");
    printf("\t\tFactura -- Ferreteria Albacete --\n");
    printf("----------------------------------------------------------------\n");
    printf("\t Descripcion \t Cantidad \t Precio  Importe\n");
    for (int i = 0; i < 15; ++i) {
        if (listaproductos[i].stock != produtosiniciales[i].stock) {
            cantidad = produtosiniciales[i].stock - listaproductos[i].stock;
            importe = listaproductos[i].precio * cantidad;
            printf("%s \t        %d \t   %8.2f    %8.2f\n", listaproductos[i].descripcion, cantidad, listaproductos[i].precio, importe);
            preciototal += importe;
            produtosiniciales[i].stock = listaproductos[i].stock;
        }
    }
    printf("----------------------------------------------------------------\n");
    printf("                                      TOTAL:  %8.2f\n", preciototal);
    printf("----------------------------------------------------------------\n");

    *numalbaranes = 5;
}

void new_art(struct productos lista[LISTA]) //La estructura para la funcion es simple, se usa
        // un guardado de datos a través de un for, ya que es la forma de guardar datos en
        // una matriz o vector, recordar que para matrices se utilizan dos, la estructura ayuda, pues
        // escribir cuatro o cinco vectores para recopilar los datos habrían hecho de este proyecto uno mucho
        // mas extenso y dificil de compilar, pues el programa tendria que acceder a puntos distintos y no relacionados
        // de la memoria. Tambien cabe mencionar que el sistema de recoleccion de la variable lleno y el numero de
        // descripcion son simplemente beneficios de usar un loop 'for', y que siempre tengan en cuenta que los vectores
        // y matrices empiezan en 0, por tanto para que tanto las variables de llenado como los n_art sean correctos
        // hay que escribir el i+1 numero que se busque guardar.
{
    int i, aux=0;
    printf("Introduzca el nuevo articulo:\n");
    for(i=0; i<LISTA && aux==0; i++) {
        if(lista[i].lleno==0) {
            printf("Introduce los datos requeridos:\n Descripcion:");
            fflush(stdin);
            fgets(lista[i].descripcion, MAX_DESC, stdin);
            cambio(lista[i].descripcion);
            fflush(stdin);
            printf("Stock:\n ");
            scanf("%d", &lista[i].stock);
            printf("Precio:\n ");
            scanf("%f", &lista[i].precio);
            lista[i].numarticulo=i+1;
            lista[i].lleno = 1;
            break;
        } else if (lista[14].lleno == 1)
        {
            printf("No hay espacio disponible\n");
            break;
        }

    }
}
void cambio(char palabra[MAX_DESC]) //Una simple funcion que busque, usando un for, por el caracter '\n' en lo escrito,
// tampoco hay mucho que explicar xd
{
    for (int i = 0; i < MAX_DESC; ++i) {
        if(palabra[i]=='\n')
            palabra[i]='\0';
    }
}
