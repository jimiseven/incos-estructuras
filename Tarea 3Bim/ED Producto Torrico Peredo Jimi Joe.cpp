/*
	Nombre : Jimi Joe Torrico Peredo
	Curso :  Sistemas 2
	Carrera : Sistemas Informaticos
	Materia : Estructura de Datos
	
*/
#include<iostream>
#include<string>
#include<fstream>
#include<stdlib.h>

using namespace std;

struct NodoProducto {
    int codigo;
    string nombreArt;
    int precioUnit;
    int cantidad;
    string nombreProv;
    struct NodoProducto* siguiente;
    struct NodoProducto* anterior;
};

struct NodoProducto* listaProductos = NULL;

struct NodoProducto* crearNodoProducto() {
    int codigo, precioUnit, cantidad;
    string nombreArt, nombreProv;

    cout << "\nIngrese el codigo del producto: ";
    cin >> codigo;
    cout << "Ingrese el nombre del articulo: ";
    cin.ignore(); // Limpiar el buffer de entrada
    getline(cin, nombreArt);
    cout << "Ingrese el precio unitario: ";
    cin >> precioUnit;
    cout << "Ingrese la cantidad: ";
    cin >> cantidad;
    cout << "Ingrese el nombre del proveedor: ";
    cin.ignore(); // Limpiar el buffer de entrada
    getline(cin, nombreProv);

    struct NodoProducto* nuevoProducto = new struct NodoProducto;
    if (nuevoProducto == NULL) {
        cout << "Error: Memoria insuficiente o usuario sin privilegios";
        return NULL;
    }

    nuevoProducto->codigo = codigo;
    nuevoProducto->nombreArt = nombreArt;
    nuevoProducto->precioUnit = precioUnit;
    nuevoProducto->cantidad = cantidad;
    nuevoProducto->nombreProv = nombreProv;
    nuevoProducto->siguiente = NULL;
    nuevoProducto->anterior = NULL;

    return nuevoProducto;
}

void insertarUltimo() {
    struct NodoProducto* nuevoProducto = crearNodoProducto();
    if (nuevoProducto == NULL) {
        return;
    }

    if (listaProductos == NULL) {
        listaProductos = nuevoProducto;
    } else {
        struct NodoProducto* auxiliar = listaProductos;
        while (auxiliar->siguiente != NULL) {
            auxiliar = auxiliar->siguiente;
        }
        auxiliar->siguiente = nuevoProducto;
        nuevoProducto->anterior = auxiliar;
    }

    cout << "Producto insertado al final de la lista." << endl;
}

void insertarCabeza() {
    struct NodoProducto* nuevoProducto = crearNodoProducto();
    if (nuevoProducto == NULL) {
        return;
    }

    if (listaProductos == NULL) {
        listaProductos = nuevoProducto;
    } else {
        nuevoProducto->siguiente = listaProductos;
        listaProductos->anterior = nuevoProducto;
        listaProductos = nuevoProducto;
    }

    cout << "Producto insertado al principio de la lista." << endl;
}

void insertarEnOrden() {
    struct NodoProducto* nuevoProducto = crearNodoProducto();
    if (nuevoProducto == NULL) {
        return;
    }

    if (listaProductos == NULL || nuevoProducto->codigo < listaProductos->codigo) {
        nuevoProducto->siguiente = listaProductos;
        if (listaProductos != NULL) {
            listaProductos->anterior = nuevoProducto;
        }
        listaProductos = nuevoProducto;
    } else {
        struct NodoProducto* actual = listaProductos;
        while (actual->siguiente != NULL && actual->siguiente->codigo < nuevoProducto->codigo) {
            actual = actual->siguiente;
        }
        nuevoProducto->siguiente = actual->siguiente;
        nuevoProducto->anterior = actual;
        if (actual->siguiente != NULL) {
            actual->siguiente->anterior = nuevoProducto;
        }
        actual->siguiente = nuevoProducto;
    }

    cout << "Producto insertado en orden por codigo." << endl;
}

void mostrarProducto(NodoProducto* producto) {
    cout << "Codigo: " << producto->codigo << endl;
    cout << "Nombre del articulo: " << producto->nombreArt << endl;
    cout << "Precio unitario: " << producto->precioUnit << endl;
    cout << "Cantidad: " << producto->cantidad << endl;
    cout << "Nombre del proveedor: " << producto->nombreProv << endl;
}

void buscarProducto() {
    int codigoBuscado;
    cout << "\nIngrese el codigo del producto a buscar: ";
    cin >> codigoBuscado;

    NodoProducto* auxiliar = listaProductos;
    while (auxiliar != NULL) {
        if (auxiliar->codigo == codigoBuscado) {
            cout << "\nProducto encontrado:\n";
            mostrarProducto(auxiliar);
            return;
        }
        auxiliar = auxiliar->siguiente;
    }

    cout << "\nProducto no encontrado." << endl;
}

void insertarAntesDe() {
    int codigoInsertar;
    cout << "\nIngrese el codigo del producto antes del cual desea insertar: ";
    cin >> codigoInsertar;

    NodoProducto* nuevoProducto = crearNodoProducto();
    if (nuevoProducto == NULL) {
        return;
    }

    NodoProducto* auxiliar = listaProductos;
    while (auxiliar != NULL) {
        if (auxiliar->codigo == codigoInsertar) {
            if (auxiliar->anterior == NULL) {
                nuevoProducto->siguiente = auxiliar;
                auxiliar->anterior = nuevoProducto;
                listaProductos = nuevoProducto;
            } else {
                nuevoProducto->siguiente = auxiliar;
                nuevoProducto->anterior = auxiliar->anterior;
                auxiliar->anterior->siguiente = nuevoProducto;
                auxiliar->anterior = nuevoProducto;
            }
            cout << "\nProducto insertado antes del producto con codigo " << codigoInsertar << "." << endl;
            return;
        }
        auxiliar = auxiliar->siguiente;
    }

    cout << "\nProducto con codigo " << codigoInsertar << " no encontrado, no se pudo insertar." << endl;
}

void editarProducto() {
    int codigoEditar;
    cout << "\nIngrese el codigo del producto a editar: ";
    cin >> codigoEditar;

    NodoProducto* auxiliar = listaProductos;
    while (auxiliar != NULL) {
        if (auxiliar->codigo == codigoEditar) {
            mostrarProducto(auxiliar);

            int nuevoCodigo, nuevoPrecio, nuevaCantidad;
            string nuevoNombreArt, nuevoNombreProv;

            cout << "\nIngrese el nuevo codigo del producto: ";
            cin >> nuevoCodigo;
            cout << "Ingrese el nuevo nombre del articulo: ";
            cin.ignore();
            getline(cin, nuevoNombreArt);
            cout << "Ingrese el nuevo precio unitario: ";
            cin >> nuevoPrecio;
            cout << "Ingrese la nueva cantidad: ";
            cin >> nuevaCantidad;
            cout << "Ingrese el nuevo nombre del proveedor: ";
            cin.ignore();
            getline(cin, nuevoNombreProv);

            auxiliar->codigo = nuevoCodigo;
            auxiliar->nombreArt = nuevoNombreArt;
            auxiliar->precioUnit = nuevoPrecio;
            auxiliar->cantidad = nuevaCantidad;
            auxiliar->nombreProv = nuevoNombreProv;

            cout << "\nProducto editado exitosamente." << endl;
            return;
        }
        auxiliar = auxiliar->siguiente;
    }

    cout << "\nProducto no encontrado, no se pudo editar." << endl;
}

void borrarProducto() {
    int codigoBorrar;
    cout << "\nIngrese el codigo del producto a borrar: ";
    cin >> codigoBorrar;

    NodoProducto* auxiliar = listaProductos;
    while (auxiliar != NULL) {
        if (auxiliar->codigo == codigoBorrar) {
            if (auxiliar->anterior == NULL) {
                listaProductos = auxiliar->siguiente;
                if (auxiliar->siguiente != NULL) {
                    auxiliar->siguiente->anterior = NULL;
                }
            } else {
                auxiliar->anterior->siguiente = auxiliar->siguiente;
                if (auxiliar->siguiente != NULL) {
                    auxiliar->siguiente->anterior = auxiliar->anterior;
                }
            }
            delete auxiliar;
            cout << "\nProducto con codigo " << codigoBorrar << " eliminado." << endl;
            return;
        }
        auxiliar = auxiliar->siguiente;
    }

    cout << "\nProducto con codigo " << codigoBorrar << " no encontrado, no se pudo borrar." << endl;
}

void destruirLista() {
    NodoProducto* auxiliar = listaProductos;
    while (auxiliar != NULL) {
        NodoProducto* siguiente = auxiliar->siguiente;
        delete auxiliar;
        auxiliar = siguiente;
    }
    listaProductos = NULL;
    cout << "\nLista de productos destruida." << endl;
}

void ordenarLista() {
    if (listaProductos == NULL) {
        cout << "\nLa lista está vacia." << endl;
        return;
    }

    NodoProducto* actual = listaProductos;
    NodoProducto* siguiente = actual->siguiente;
    NodoProducto* temp;

    while (actual != NULL) {
        siguiente = actual->siguiente;
        while (siguiente != NULL) {
            if (actual->codigo > siguiente->codigo) {
                // Intercambiar los nodos actual y siguiente
                if (actual->anterior == NULL) {
                    listaProductos = siguiente;
                    siguiente->anterior = NULL;
                } else {
                    actual->anterior->siguiente = siguiente;
                    siguiente->anterior = actual->anterior;
                }

                actual->siguiente = siguiente->siguiente;
                siguiente->siguiente = actual;
                actual->anterior = siguiente;
                if (actual->siguiente != NULL) {
                    actual->siguiente->anterior = actual;
                }
                temp = actual;
                actual = siguiente;
                siguiente = temp;
            }
            siguiente = siguiente->siguiente;
        }
        actual = actual->siguiente;
    }

    cout << "\nLista de productos ordenada por codigo." << endl;
}

void guardarArchivo() {
    ofstream archivoSalida("lista1.txt");
    if (archivoSalida.is_open()) {
        NodoProducto* auxiliar = listaProductos;
        while (auxiliar != NULL) {
            archivoSalida << "Codigo: " << auxiliar->codigo << endl;
            archivoSalida << "Nombre del articulo: " << auxiliar->nombreArt << endl;
            archivoSalida << "Precio unitario: " << auxiliar->precioUnit << endl;
            archivoSalida << "Cantidad: " << auxiliar->cantidad << endl;
            archivoSalida << "Nombre del proveedor: " << auxiliar->nombreProv << endl;
            archivoSalida << "--------------------------\n";
            auxiliar = auxiliar->siguiente;
        }
        archivoSalida.close();
        cout << "\nDatos guardados en el archivo lista1.txt." << endl;
    } else {
        cout << "\nNo se pudo abrir el archivo lista1.txt para guardar los datos." << endl;
    }
}

void mostrarLista() {
    NodoProducto* auxiliar = listaProductos;
    cout << "\nLISTA DE PRODUCTOS:\n";
    while (auxiliar != NULL) {
        mostrarProducto(auxiliar);
        cout << "--------------------------\n";
        auxiliar = auxiliar->siguiente;
    }
}

int main() {
    int opcion;
    do {
        cout << "\nMENU:\n";
        cout << "1. Insertar producto al final de la lista\n";
        cout << "2. Insertar producto al principio de la lista\n";
        cout << "3. Insertar producto en orden por codigo\n";
        cout << "4. Buscar un producto por codigo\n";
        cout << "5. Insertar producto antes de otro por codigo\n";
        cout << "6. Editar un producto por codigo\n";
        cout << "7. Borrar un producto por codigo\n";
        cout << "8. Destruir la lista de productos\n";
        cout << "9. Ordenar la lista de productos por codigo\n";
        cout << "10. Guardar los datos en un archivo\n";
        cout << "11. Mostrar la lista de productos\n";
        cout << "12. Salir\n";
        cout << "Ingrese una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                insertarUltimo();
                break;
            case 2:
                insertarCabeza();
                break;
            case 3:
                insertarEnOrden();
                break;
            case 4:
                buscarProducto();
                break;
            case 5:
                insertarAntesDe();
                break;
            case 6:
                editarProducto();
                break;
            case 7:
                borrarProducto();
                break;
            case 8:
                destruirLista();
                break;
            case 9:
                ordenarLista();
                break;
            case 10:
                guardarArchivo();
                break;
            case 11:
                mostrarLista();
                break;
            case 12:
                break;
            default:
                cout << "Opcion no válida. Por favor, seleccione una opcion válida." << endl;
        }
    } while (opcion != 12);

    return 0;
}

