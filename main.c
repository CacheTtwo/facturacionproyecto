/*
  Integrantes del grupo (Grupo C - FPI):
  Sergio Fuentes Moreno
  Manuel Alejandro Torres Moreno
  Víctor Nolasco Sánchez
  Javier Yago Giménez
*/

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
    struct productos listaproductos[15] = {{1, "Martillo de carpintero con mango de fibra de vidrio", 4.88, 50,1}, {2, "Maza de goma", 8.22, 4,1}, {3, "Juego de llaves combinadas", 11.99, 10,1}, {4, "Llave inglesa ajustable con tornillo", 5.54, 12,1}, {5, "Juego de laves Allen", 6.95, 20,1}, {6, "Juego de llaves de vaso", 21.99, 10,1}, {7, "Juego de destornilladores de precision", 18.46, 15,1}, {8, "Pinza pelacables", 5.99, 3,1}, {9, "Alicates universales", 5.63, 12,1},{10, "Polimetro digital de bolsillo", 18.3, 7,1}, {11, "Polimetro digital multifuncion", 32.00, 12,1}};
    //Copia de la lista que utilizamos para realizar ciertas comprobaciones en la funcion 2
    struct productos productosiniciales[15] = {{1, "Martillo de carpintero con mango de fibra de vidrio", 4.88, 50,1}, {2, "Maza de goma", 8.22, 4,1}, {3, "Juego de llaves combinadas", 11.99, 10,1}, {4, "Llave inglesa ajustable con tornillo", 5.54, 12,1}, {5, "Juego de laves Allen", 6.95, 20,1}, {6, "Juego de llaves de vaso", 21.99, 10,1}, {7, "Juego de destornilladores de precision", 18.46, 15,1}, {8, "Pinza pelacables", 5.99, 3,1}, {9, "Alicates universales", 5.63, 12,1}, {10, "Polimetro digital de bolsillo", 18.3, 7,1}, {11, "Polimetro digital multifuncion", 32.00, 12,1}};

    do {
        printf("\n1. Introduccion de albaran\n");
        printf("2. Confeccion de factura\n");
        printf("3. Introduccion de nuevo articulo\n");
        printf("4. Salir del programa\n");
        printf("Elija una opcion:\n");
        scanf("%d", &ops);

        switch(ops) { //Menu
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
                    printf("\nDescripcion: %s\n", listaproductos[i].descripcion);
                    printf("Stock: %d\n", listaproductos[i].stock);
                    printf("Precio: %.2f\n", listaproductos[i].precio);
                    printf("El numero del articulo es %d\n", listaproductos[i].numarticulo);
                    printf("Lleno: %d\n", listaproductos[i].lleno);
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
    float totalalbaran = 0;

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

                totalalbaran += cantidad[i] * listaproductos[j].precio;
            }
        }
    }
    printf("Importe total del albaran: %.2f\n", totalalbaran);
}

void factura(struct productos listaproductos[15], struct productos productosiniciales[15], int *numalbaranes) {
    int sin_pedidos = 0, cantidad;
    float preciototal = 0, importe;

    for (int i = 0; i < 15; ++i) {
        if (listaproductos[i].stock == productosiniciales[i].stock) sin_pedidos++;
    }
    if (sin_pedidos == 15) {
        printf("No hay albaranes. Para mostrar la factura introduce uno primero.\n");
        return;
    } //Mediante el for y el if comprobamos si todavia no se ha introducido ningun albaran, en ese caso pedimos que se introduzca uno antes de mostrar una factura

    printf("----------------------------------------------------------------\n"); //Empezamos a imprimir la factura
    printf("\t\tFactura -- Ferreteria Albacete --\n");
    printf("----------------------------------------------------------------\n");
    printf("\t Descripcion \t Cantidad \t Precio  Importe\n");
    for (int i = 0; i < 15; ++i) {
        if (listaproductos[i].stock != productosiniciales[i].stock) { //Mediante esta sentencia hacemos que solo vayan a la factura los articulos cuyo stock se haya visto modificado
            cantidad = productosiniciales[i].stock - listaproductos[i].stock; //Calculamos la cantidad pedida restando al stock inicial el actual (despues de hacer albaranes)
            importe = listaproductos[i].precio * cantidad; //Calculamos el importe a pagar multiplicando el precio de los articulos pedidos por su cantidad
            printf("%s \t        %d \t   %.2f    %.2f\n", listaproductos[i].descripcion, cantidad, listaproductos[i].precio, importe); //Vamos imprimiendo todos los datos de cada articulo
            preciototal += importe; //Vamos calculando el precio total uno por uno segun van pasando los articulos y sumando el importe de cada uno de estos
            productosiniciales[i].stock = listaproductos[i].stock; //Despues de pasar cada articulo a la factura reiniciamos el stock de estos
        }
    }
    printf("----------------------------------------------------------------\n");
    printf("                                           TOTAL:  %.2f\n", preciototal);
    printf("----------------------------------------------------------------\n"); //Terminamos de imprimir la factura

    *numalbaranes = 5; //Reiniciamos tambien a 5 el numero de albaranes que se pueden pedir despues de hacer la factura
}

void new_art(struct productos lista[LISTA]) {
    int i, aux=0;

    printf("Introduzca el nuevo articulo.\n");
    for(i=0; i<LISTA && aux==0; i++) { //Con el for recorremos la lista de productos
        if(lista[i].lleno==0) { //Si encuentra un hueco vacio (lleno = 0) pide los datos del nuevo objeto y lo guarda en la lista
            printf("Introduce los datos requeridos:\n Descripcion:");
            fflush(stdin);
            fgets(lista[i].descripcion, MAX_DESC, stdin);
            cambio(lista[i].descripcion);
            fflush(stdin);
            printf("Precio:\n ");
            scanf("%f", &lista[i].precio);
            printf("Stock:\n ");
            scanf("%d", &lista[i].stock);
            lista[i].numarticulo = i+1;
            lista[i].lleno = 1;
            break;
        } else if (lista[14].lleno == 1) { //Si no encuentra huecos vacios imprime un mensaje de error
            printf("No hay espacio disponible\n");
            break;
        }
    }
}

void cambio(char palabra[MAX_DESC]) { //Una simple funcion que busque, usando un for, por el caracter '\n' en lo escrito
    for (int i = 0; i < MAX_DESC; ++i) {
        if(palabra[i]=='\n')
            palabra[i]='\0';
    }
}
