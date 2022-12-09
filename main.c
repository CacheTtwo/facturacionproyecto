#include <stdio.h>
#include <string.h>
#define LISTA 15
#define MAX_DESC 150

struct productos{
    int numarticulo;
    char descripcion[150];
    float precio;
    int stock;
};

void albaranes(struct productos listaproductos[15]);
void factura(struct productos listaproductos[15], struct productos productosiniciales[15], int *numalbaranes);
void nuevoarticulo();
void listalimpia();

typedef struct {
    char descripcion[150];
    int cantidad;
    float precio;
    int lleno;
}list;
list l_items[LISTA];

int main() {
    int ops, numalbaranes = 5;
    struct productos listaproductos[15] = {{1, "Martillo de carpintero con mango de fibra de vidrio", 4.88, 50}, {2, "Maza de goma", 8.22, 4}, {3, "Juego de llaves combinadas", 11.99, 10}, {4, "Llave inglesa ajustable con tornillo", 5.54, 12}, {5, "Juego de laves Allen", 6.95, 20}, {6, "Juego de llaves de vaso", 21.99, 10}, {7, "Juego de destornilladores de precisión", 18.46, 15}, {8, "Pinza pelacables", 5.99, 3}, {9, "Alicates universales", 5.63, 12}, {10, "Polimetro digital de bolsillo", 18.3, 7}, {11, "Polimetro digital multifuncion", 32.00, 12}};
    struct productos productosiniciales[15] = {{1, "Martillo de carpintero con mango de fibra de vidrio", 4.88, 50}, {2, "Maza de goma", 8.22, 4}, {3, "Juego de llaves combinadas", 11.99, 10}, {4, "Llave inglesa ajustable con tornillo", 5.54, 12}, {5, "Juego de laves Allen", 6.95, 20}, {6, "Juego de llaves de vaso", 21.99, 10}, {7, "Juego de destornilladores de precisión", 18.46, 15}, {8, "Pinza pelacables", 5.99, 3}, {9, "Alicates universales", 5.63, 12}, {10, "Polimetro digital de bolsillo", 18.3, 7}, {11, "Polimetro digital multifuncion", 32.00, 12}};
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
                if (numalbaranes > 0) {
                    albaranes(listaproductos);
                    numalbaranes--;
                } else printf("\nYa pediste 5 albaranes, no se admiten mas.\n\n");
                break;
            case 2:
                printf("2. Confeccion de factura\n");
                factura(listaproductos, productosiniciales, &numalbaranes);
                break;
            case 3:
                printf("3. Introduccion de nuevo articulo\n");
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

void albaranes(struct productos listaproductos[15]) {
    int p;

    printf("Introduzca el numero de articulos que tiene el albaran:\n");
    scanf("%d", &p);
    int numarticulo[p];
    int cantidad[p];

        for (int i = 0; i < p; ++i) {
            do {
                printf("Articulo %d:\n", i+1);
                scanf("%d", &numarticulo[i]);
                printf("Cantidad:\n");
                scanf("%d", &cantidad[i]);
                if((numarticulo[i] < 1) || (numarticulo[i] > 15) || (cantidad[i] <= 0)) printf("Ese articulo no existe o la cantidad es negativa, vuelva a introducir los datos.\n");
            } while ((numarticulo[i] < 1) || (numarticulo[i] > 15) || (cantidad[i] <= 0));
            for (int j = 0; j < i; ++j) {
                if (numarticulo[i] == numarticulo[j]) {
                    printf("Ese articulo ya esta en este albaran, no se puede repetir.\n");
                    i--;
                }
            }
        }

    for (int i = 0; i < p; ++i) {
        for (int j = 0; j < 15; ++j) {
            if (numarticulo[i] == listaproductos[j].numarticulo) {
                if (cantidad[i] > listaproductos[j].stock) cantidad[i] = listaproductos[j].stock;
                listaproductos[j].stock -= cantidad[i];
            }
        }
    }
}

void factura(struct productos listaproductos[15], struct productos produtosiniciales[15], int *numalbaranes) {
    int sin_pedidos = 0, cantidad;
    float preciototal = 0;

    for (int i = 0; i < 15; ++i) {
        if (listaproductos[i].stock == produtosiniciales[i].stock) sin_pedidos++;
    }
    if (sin_pedidos == 15) {
        printf("No hay albaranes. Para mostrar la factura introduce uno primero.\n");
    }
}

void nuevoarticulo() {
    int i, aux=0;
    printf("Introduzca el nuevo articulo:\n");
    for(i=0; i<LISTA && aux==0; i++) {
        if(l_items[i].lleno==0) {
            printf("Introduce los datos requeridos:\n Descripcion:");
            fflush(stdin);
            fgets(l_items[i].descripcion, MAX_DESC, stdin);
            fflush(stdin);
            printf("cantidad:\n ");
            scanf("%d", &l_items[i].cantidad);
            printf("Precio:\n ");
            scanf("%f", &l_items[i].precio);
            l_items[i].lleno = 1;
            break;
        } else if (l_items[LISTA-1].lleno == 1)
            printf("No hay espacio disponible");
    }
}

void listalimpia() {
    for (int i = 0; i <LISTA; ++i) {
        l_items[i].lleno = 0;
    }
}
