// JDR.Prog.Parcial.Ej2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "conio.h"
#include "stdio.h"
#include "stdlib.h"
#include "fstream"
#include "string"
#include "iostream"


using namespace std;

class Persona {
private:
	string Nombre;
	string Apellido;
	int Legajo;
	int Nota;
public:
	Persona(string, string, int, int);	
	void Mostrar();
};

Persona::Persona(string nombre, string apellido, int legajo, int nota) {
	this->Nombre = nombre;
	this->Apellido = apellido;
	this->Legajo = legajo;
	this->Nota = nota;
}

void Persona::Mostrar() {
	cout << this->Nombre << "-" << this->Apellido << "-" << this->Legajo << "-" << this->Nota << endl;
}

void crearArchivo();
void agregar();
void actualizar();
void eliminar();
void leer();

int main()
{
	crearArchivo();

	int op;

	do {
		cout << "Menu" << endl;
		cout << "1-Agregar registro" << endl;
		cout << "2-Modificar registro" << endl;
		cout << "3-Eliminar registro" << endl;
		cout << "4-Leer archivo" << endl;
		cout << "5-Salir" << endl;

		cin >> op;
		switch (op) {
		case 1:
			agregar();
			break;
		case 2:
			actualizar();
			break;
		case 3:
			eliminar();
			break;
		case 4:
			leer();
			break;
		}
	} 
	while (op != 5);

	_getch();

    return 0;
}

void crearArchivo() {
	ofstream file;
	file.open("Datos.txt", ios::out);

	if (file.fail()) {
		cout << "Error al crear el archivo" << endl;
		return;
	}	
}

void agregar() {
	ofstream file;

	file.open("Datos.txt", ios::out | ios::app);

	if (file.fail()) {
		cout << "Error al abrir el archivo" << endl;
		return;
	}
	else {
		int legajo, nota;
		string nombre, apellido;

		cout << "Ingrese legajo distinto de 0(cero)" << endl;
		cin >> legajo;

		while (legajo != 0) {
			cout << "Ingrese nota" << endl;
			cin >> nota;

			cout << "Ingrese nombre" << endl;
			cin >> nombre;

			cout << "Ingrese apellido" << endl;
			cin >> apellido;

			file << legajo << " " << nombre << " " << apellido << " " << nota << endl;

			cout << "Ingrese legajo distinto de 0(cero)" << endl;
			cin >> legajo;
		}

		file.close();
	}

}

void actualizar() {
	int aux, legajo, nota;
	string nombre, apellido;
	ifstream file;

	file.open("Datos.txt", ios::in);

	if (file.fail()) {
		cout << "Error al abrir el archivo" << endl;
		return;
	}

	ofstream newFile;
	newFile.open("nuevosDatos.txt", ios::out | ios::app);
	if (newFile.fail()) {
		cout << "Error al abrir el archivo" << endl;
		return;
	}

	cout << "Ingrese el legajo a modificar" << endl;
	cin >> aux;

	file >> legajo >> nombre >> apellido >> nota;

	while (!file.eof()) {
		if (aux == legajo) {
			cout << "Ingrese la nueva nota" << endl;
			cin >> nota;

			newFile << aux << " " << nombre << " " << apellido << " " << nota << endl;
		}
		else {
			newFile << legajo << " " << nombre << " " << apellido << " " << nota << endl;
		}

		file >> legajo >> nombre >> apellido >> nota;
	}

	file.close();
	newFile.close();
	remove("Datos.txt");
	rename("nuevosDatos.txt", "Datos.txt");
}

void eliminar() {
	int aux, legajo, nota;
	string nombre, apellido;
	ifstream file;

	file.open("Datos.txt", ios::in);

	if (file.fail()) {
		cout << "Error al abrir el archivo" << endl;
		return;
	}

	ofstream newFile;
	newFile.open("nuevosDatos.txt", ios::out | ios::app);
	if (newFile.fail()) {
		cout << "Error al abrir el archivo" << endl;
		return;
	}

	cout << "Ingrese el legajo a eliminar" << endl;
	cin >> aux;

	file >> legajo >> nombre >> apellido >> nota;

	while (!file.eof()) {
		if (aux != legajo) {
			newFile << legajo << " " << nombre << " " << apellido << " " << nota << endl;
		}
		else {
			cout << "Registro eliminado" << endl;
		}

		file >> legajo >> nombre >> apellido >> nota;
	}

	file.close();
	newFile.close();
	remove("Datos.txt");
	rename("nuevosDatos.txt", "Datos.txt");
}

void leer() {
	int legajo, nota;
	string nombre, apellido;
	ifstream file;

	file.open("Datos.txt", ios::in);

	if (file.fail()) {
		cout << "Error al abrir el archivo" << endl;
		return;
	}

	file >> legajo >> nombre >> apellido >> nota;

	while (!file.eof()) {

		Persona* p = new Persona(nombre, apellido, legajo, nota);
		p->Mostrar();

		file >> legajo >> nombre >> apellido >> nota;
	}

	file.close();
}



