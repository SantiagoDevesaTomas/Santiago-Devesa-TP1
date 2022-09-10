#include <iostream>
#include <fstream>

using namespace std;

const int cantidad_clientes {8};
const int cantidad_productos {5};

//punto 2
void sortdoble(float vord[], int tam, int vaux[])
{
	int i, pos, imin;

	for (pos = 0; pos < tam - 1 ; pos++) {
		imin = pos;
		for (i = pos+1 ; i < tam ; i++)
			if (vord[i] < vord[imin])
				imin = i;
		swap(vord[pos], vord[imin]);
		swap(vaux[pos], vaux[imin]);
	}
}

//punto 2
void imprimir_productos_distancia(int i_max_supera_limite, float distancias[][cantidad_productos],
                       string productos[],int indice_productos[cantidad_productos])
{
    for (int j = 0; j < cantidad_productos; j++) {
        indice_productos[j] = j;
    }
    float copia_distancias[cantidad_productos];
    for (int j = 0; j < cantidad_productos; j++) {
        copia_distancias[j] = distancias[i_max_supera_limite][j];
    }
    cout << endl << "Listado de Km recorridos por tipo de producto (ascendente):" << endl;
    sortdoble(copia_distancias, cantidad_productos, indice_productos);
    for (int j = 0; j < cantidad_productos; j++) {
        cout << productos[indice_productos[j]] << ": " << copia_distancias[j] << endl;
    }
}

//punto 3
void imprimir_entregas_producto_mas_pesado(string productos[], int indice_productos[], int cantidad_productos, int entregas_producto[]){
    cout << endl << "Cantidad de entregas para el tipo de producto " << productos[indice_productos[cantidad_productos-1]]
         << ": " << entregas_producto[indice_productos[cantidad_productos-1]] << endl;

}




int main(){


    float pesos[cantidad_clientes][cantidad_productos];
    float distancias [cantidad_clientes][cantidad_productos];
    string clientes[cantidad_clientes];
    string productos[cantidad_productos];
    int entregas_producto[cantidad_productos];
    int indice_productos[cantidad_productos];


    ifstream datos;
    datos.open("Datos.txt");
    if (!datos) {
		cout << "No se puedo abrir el archivo de datos" << endl;
		return 1;
	}
	float peso;
	float distancia;
	int i_cliente, i_producto;
	for (int i=0; i < cantidad_clientes; i++) {
        for (int j=0; j < cantidad_productos; j++) {
            pesos[i][j] = 0;
            distancias[i][j] = 0;
            entregas_producto[j] = 0;
        }
	}
    while (datos >> i_cliente >> i_producto >> peso >> distancia) {
        pesos[i_cliente][i_producto] += peso;
        distancias[i_cliente][i_producto] += distancia;
        entregas_producto[i_producto]++;
	}
	datos.close();


    ifstream nombres;
    nombres.open("Nombres.txt");
	if (!nombres) {
        cout << "No se puedo abrir el archivo de datos" << endl;
		return 1;
	}
    string nombre;
	int i = 0;
	while (nombres >> nombre) {
        if (i < cantidad_clientes) {
            clientes[i] = nombre;
        }
        else {
            productos[i-cantidad_clientes] = nombre;
        }
        i++;
	}
	nombres.close();
    //Punto 1
    cout << "Listado por clientes, de los tipos de productos que superen los 13000 Kg acumulados:" << endl;
    int max_supera_limite = 0;
    int i_max_supera_limite = 0;
    for (int i = 0; i < cantidad_clientes; i++) {
        int supera_limite = 0;
        cout <<  clientes[i] << ": ";
        for (int j = 0; j < cantidad_productos; j++) {
            if (pesos[i][j] > 13000) {
                supera_limite++;
                if (supera_limite == 1) {
                    cout << productos[j];
                } else {
                    cout << ", " << productos[j];
                }
            }
        }
        cout << endl;
        if (max_supera_limite < supera_limite) {
            max_supera_limite = supera_limite;
            i_max_supera_limite = i;
        }
    }

    //punto 2
    imprimir_productos_distancia(i_max_supera_limite, distancias, productos, indice_productos);

    //punto 3
    imprimir_entregas_producto_mas_pesado(productos, indice_productos, cantidad_productos, entregas_producto);

}









