#pragma once
#include<string>
#include<vector>
#include <iostream>
#include "Ksiazka.h"
using namespace std;

struct DaneKlienta {
	int nr;
	string imie;
	string nazwisko;
	int nr_tel;
};

class Biblioteka {
private:
	vector<DaneKlienta> listaKlientow;
	vector<Ksiazka>books;
	int liczbaKlientow;

public:
	Biblioteka() : liczbaKlientow(0) {}
	Biblioteka(const string file) {

	}
}
	DaneKlienta getClient(int idx) {
	DaneKlienta Client = listaKlientow[idx];
	return Client;
}

/*void usun(int idx) {
listaKlientow.erase(idx);
}*/

~Biblioteka() {
}
int get_liczbaKlientow() {
	return liczbaKlientow;
}

void wypiszKlientow() {
	DaneKlienta Client;
	for (const auto& Client : listaKlientow) {
		cout << endl << endl << "Klient nr: " << Client.nr << endl << Client.imie << ' ' << Client.nazwisko << ' ' << Client.nr_tel << endl;
	}
}
void updateFile() {

	static const char* const file = "clients.txt";
	ofstream fout;
	fout.open(file);
	if (!fout) {
		cerr << "Error in opening the output file" << endl;
	}

	DaneKlienta Client;
	int liczba = 0;
	for (const auto& Client : listaKlientow) {
		fout << liczba << endl << Client.imie << endl << Client.nazwisko << endl << Client.nr_tel << endl;
		++liczba;
	}
}

void noweZgloszenie() {
	DaneKlienta nowyKlient;

	cout << "Imie: ";
	cin >> nowyKlient.imie;

	cout << "Nazwisko: ";
	cin >> nowyKlient.nazwisko;

	cout << "Nr telefonu: ";
	cin >> nowyKlient.nr_tel;

	nowyKlient.nr = liczbaKlientow;
	++liczbaKlientow;

	listaKlientow.push_back(nowyKlient);
	cout << "Nowe zgloszenie dodane." << endl;
}

void wypiszKlienta(int idx) {
	cout << endl << endl << "IMIE NAZWISKO NUMER" << endl << listaKlientow[idx].imie << ' ' << listaKlientow[idx].nazwisko << ' ' << listaKlientow[idx].nr_tel << endl;
}

};