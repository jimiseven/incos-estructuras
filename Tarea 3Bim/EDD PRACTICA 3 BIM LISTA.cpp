#include<iostream>
#include<string.h>
#include<fstream>
#include<stdlib.h>

using namespace std;

struct nodold
{
	int dato;
	struct nodold *siguiente;
	struct nodold *anterior;
};

struct nodold*ld;

struct nodold *crear_nodo()
{

	int x;
	struct nodold *nuevo;
	
	cout<<"\nINGRESE UN NUMERO ENTERO A LA LISTA: ";
	cin>>x;
	
	nuevo = new struct nodold;
	if(nuevo==NULL) {
    	cout<<"Error: Memoria insuficiente o usuario sin privilegios";
    	return NULL;
	}
	nuevo->dato = x;
    nuevo->siguiente = NULL;
    nuevo->anterior = NULL;
    
    return nuevo;
}

struct nodold *crear_nodo_x(int x)
{
	struct nodold *nuevo;
	nuevo = new struct nodold;
	if(nuevo == NULL)
	{
		cout<<"ERROR: MEMORIA INSUFICIENTE O USUARIO SIN PRIVILEGIOS! ";
		return NULL;
	}
	nuevo->dato = x;
	nuevo->siguiente  = NULL;
	nuevo->anterior = NULL;
	return nuevo; 
}

void insertar_cabeza_x(int x)
{
	struct nodold *nuevo;
	nuevo = crear_nodo_x(x);
	if(ld!=NULL)
	{
		ld->anterior = nuevo;
		nuevo->siguiente =ld;
	}
	ld = nuevo;
}

void insertar_cabeza()
{
	struct nodold *nuevo;
	nuevo = crear_nodo();
	if(ld!=NULL)
	{
		ld->anterior = nuevo;
		nuevo->siguiente =ld;
	}
	ld = nuevo;
}

void insertar_en_orden(){
	
	struct nodold *nuevo, *auxiliar;
	auxiliar = ld;
	
	nuevo = crear_nodo();
	
	while(auxiliar!=NULL && nuevo->dato > auxiliar->dato && auxiliar->siguiente != NULL) {
		auxiliar = auxiliar->siguiente;
	}
	
	if(auxiliar==ld)
	{
		if(ld != NULL)
		{
    		ld->anterior = nuevo;
    		nuevo->siguiente=ld;   	
		}
	    ld=nuevo;
	} 
	else 
	{
		if(nuevo->dato <= auxiliar->dato) 
		{
			nuevo->siguiente = auxiliar;
			nuevo->anterior = auxiliar->anterior;
			auxiliar->anterior->siguiente = nuevo;
			auxiliar->anterior =nuevo;
	    } 
		else 
		{
			if(nuevo->dato > auxiliar->dato) 
			{
				auxiliar->siguiente = nuevo;
				nuevo->anterior = auxiliar;
			} 
			/*
			else 
			{
				nuevo->ant = auxiliar;
				auxiliar->sig = nuevo;
		    }
		    */
		}
	}
} 

void insertar_en_orden_x(int x){
	
	struct nodold *nuevo, *auxiliar;
	auxiliar = ld;
	
	nuevo = crear_nodo_x(x);
	
	while(auxiliar!=NULL && nuevo->dato > auxiliar->dato && auxiliar->siguiente != NULL) {
		auxiliar = auxiliar->siguiente;
	}
	
	if(auxiliar==ld)
	{
		if(ld != NULL)
		{
    		ld->anterior = nuevo;
    		nuevo->siguiente=ld;   	
		}
	    ld=nuevo;
	} 
	else 
	{
		if(nuevo->dato <= auxiliar->dato) 
		{
			nuevo->siguiente = auxiliar;
			nuevo->anterior = auxiliar->anterior;
			auxiliar->anterior->siguiente = nuevo;
			auxiliar->anterior =nuevo;
	    } 
		else 
		{
			if(nuevo->dato > auxiliar->dato) 
			{
				auxiliar->siguiente = nuevo;
				nuevo->anterior = auxiliar;
			} 
			/*
			else 
			{
				nuevo->ant = auxiliar;
				auxiliar->sig = nuevo;
		    }
		    */
		}
	}
}  

void mostrar_lista()
{
	struct nodold *auxiliar = ld;
	cout <<"\nLISTA DOBLE: ";
	while(auxiliar !=NULL)
	{
		if(auxiliar->anterior!=NULL) cout<<auxiliar->anterior->dato<<"<-";
		cout<<auxiliar->dato<<", ";
		auxiliar = auxiliar->siguiente;	
	}
	cout<<"\n";
}

void abrir_archivo()
{
	char cadena[99];
	int entero;
	ifstream archivo_de_entrada;
	archivo_de_entrada.open("lista_nodo_texto.txt", ios::in);
	if(archivo_de_entrada.fail())
	{
		cout<<"archivo no encontrado...";
		return;
	}
	
	while(!archivo_de_entrada.eof())
	{
		archivo_de_entrada>>cadena;
		cout<<cadena<<endl;
		
		//entero = atoi(cadena);
		//insertar_cabeza_x(entero);
		//insertar_en_orden_x(entero);
	}
	
	archivo_de_entrada.close();
	
}

void abrir_archivo_x()
{
	char cadena[99];
	string str;
	int entero;
	ifstream archivo_de_entrada;
	archivo_de_entrada.open("libro1.csv", ios::in);
	if(archivo_de_entrada.fail())
	{
		cout<<"archivo CSV no encontrado...";
		return;
	}
	
	while(!archivo_de_entrada.eof())
	{
		getline(archivo_de_entrada,str);
		strcpy(cadena, str.c_str());
		cout<<cadena<<endl;
		
		//entero = atoi(cadena);
		//insertar_cabeza_x(entero);
		//insertar_en_orden_x(entero);
	}
	
	archivo_de_entrada.close();
	
}

int main(){
	abrir_archivo_x();
	//mostrar_lista();
	return 0;
	 
	/*
	insertar_cabeza();
	mostrar_lista();
	insertar_cabeza();
	mostrar_lista();
	insertar_cabeza();
	mostrar_lista();
	*/
	
	insertar_en_orden();
	mostrar_lista();
	insertar_en_orden();
	mostrar_lista();
}
