#include <iostream>
#include <string>
#include<vector>
#include<fstream>
#include <conio.h>
using namespace std;

bool empty(std::ifstream& pFile) {
	return pFile.peek() == std::ifstream::traits_type::eof();
}

int CoZrobic() {
	int co;
	cout << endl << "Wybierz\n1 jesli naprawa\n2 Jesli Przeglad\n3 Jesli to i to: ";
	cin >> co;
	return co;
}

int getIndx() {
	int nr;
	cout << "NUMER: ";
	cin >> nr;
	return nr;
}

string getString() {
	string nazwa;
	cout << "NAZWA KSIAZKI: ";
	cin >> nazwa;
	return nazwa;
}

struct DaneKlienta {
	int nr;
	string imie;
	string nazwisko;
	int nr_tel;
};

class Biblioteka;

class Ksiazka {
private:
	string dostepnosc;
	string nazwa;
	 string file;
	vector<DaneKlienta> listaOczekujacych;
public:
	Ksiazka() {
	}
	void wypiszListe() {
		int i = 1;
		cout << endl << "Lista Oczekujacych na ksiazke: "<<nazwa<<endl;
		DaneKlienta Client;
		for (const auto& Client : listaOczekujacych) {
			cout << endl << "Osoba " << i<<endl  << "Klient nr: " << Client.nr << endl << Client.imie << ' ' << Client.nazwisko << ' ' << Client.nr_tel << endl;
			++i;
		}


	}
	void stworzListe(string file) {
		ifstream plik;
		plik.open(file);
		if (!plik) {
			cerr << "Error in opening the file" << endl;
		}
		DaneKlienta Client;
		while (plik >> Client.nr >> Client.imie >> Client.nazwisko >> Client.nr_tel) {
			listaOczekujacych.push_back(Client);
		}
	}
	void nowyDoListy(DaneKlienta dane) {
		listaOczekujacych.push_back(dane);
	}
	void powiadomDostepnosc() {}
	void usunZListy(int idx) {
		vector<DaneKlienta>::iterator it;
		it = listaOczekujacych.begin() + idx;
		listaOczekujacych.erase(it);
	}
	void zmienDostepnosc() {}
	void updateLista(const string file) {
		ofstream fout;
		fout.open(file);
		if (!fout) {
			cerr << "Error in opening the output file" << endl;
		}
		DaneKlienta Client;
		for (const auto& Client : listaOczekujacych) {
			fout << Client.nr << endl << Client.imie << endl << Client.nazwisko << endl << Client.nr_tel << endl << endl;
		}
	}
	

	friend Biblioteka;
};


class Biblioteka {
private:
	vector<DaneKlienta> listaKlientow;
	vector<Ksiazka>books;
	int liczbaKlientow;

public:
	
	Biblioteka() : liczbaKlientow(0) {}
	Biblioteka(const string file, const string file2) {
		liczbaKlientow = 0;
		ifstream plik;
		plik.open(file);
		if (!plik) {
			cerr << "Error in opening the file" << endl;
		}
		DaneKlienta Client;
		while (plik >> Client.nr >> Client.imie >> Client.nazwisko >> Client.nr_tel) {
			listaKlientow.push_back(Client);
			liczbaKlientow++;
		}

		ifstream plik2;
		plik2.open(file2);
		if (!plik2) {
			cerr << "Error in opening the file" << endl;
		}
		Ksiazka book;
		while (plik2 >> book.dostepnosc >> book.nazwa >> book.file) {
			book.listaOczekujacych.clear();
			book.stworzListe(book.file);
			books.push_back(book);
		}

	}
	DaneKlienta getClient(int idx) {
		DaneKlienta Client = listaKlientow[idx];
		return Client;
	}
	void wypiszDostepnosc() {
		Ksiazka book;
		for (const auto& book : books) {
			cout << "Nazwa ksiazki: " << book.nazwa << endl;
			cout << "Czy jest dostepna: " << book.dostepnosc << endl<<endl;

		}
	}

	void wypiszKsiazki() {
		Ksiazka book;
		for (auto& book : books) {
			cout << endl<< "Nazwa ksiazki: " << book.nazwa << endl;
			cout << "Czy jest dostepna: " << book.dostepnosc << endl << endl;
			if (book.dostepnosc == "nie") {
				book.wypiszListe();
			}
		}

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

		static const char* const file = "Clients.txt";
		ofstream fout;
		fout.open(file);
		if (!fout) {
			cerr << "Error in opening the output file" << endl;
		}

		DaneKlienta Client;
		int liczba = 0;
		for (const auto& Client : listaKlientow) {
			fout << liczba << endl << Client.imie << endl << Client.nazwisko << endl << Client.nr_tel << endl<<endl;
			++liczba;
		}

		static const char* const file2 = "Books.txt";
		ofstream fout2;
		fout2.open(file2);
		if (!fout2) {
			cerr << "Error in opening the file" << endl;
		}
		Ksiazka book;
		for (const auto& book : books) {
			fout2 << book.dostepnosc << endl << book.nazwa << endl << book.file << endl << endl;
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

	void dodajDoListy(string ksiazka, int idx) {
		int index_ksiazki=0;
		int i = 0;
		Ksiazka book;
		for (const auto& book : books) {
			if (book.nazwa == ksiazka) {
				index_ksiazki = i;
			}
			i++;
		}
		DaneKlienta Klient = listaKlientow[idx];
		books[index_ksiazki].nowyDoListy(Klient);
		string plik;
		plik = books[index_ksiazki].file;
		books[index_ksiazki].updateLista(plik);
		if (books[index_ksiazki].dostepnosc == "tak") {
			books[index_ksiazki].dostepnosc = "nie";
		}
	}
	void oddajKsiazke(int idx) {
		DaneKlienta Klient = listaKlientow[idx];
		DaneKlienta Wliscie;
		Ksiazka book;
		int index=0;
		for (auto& book : books) {
			index = 0;
			for (auto& Wliscie : book.listaOczekujacych) {
				if (Wliscie.nr == Klient.nr) {
					cout << endl;
					book.wypiszListe();
					if (index != 0) {
						book.usunZListy(index);
						book.updateLista(book.file);
						cout << endl<< "Osoba usunieta z listy oczekujacych byla w kolejce numerem: " << (index+1) <<endl;
						if (book.listaOczekujacych.size() == 1) {
							cout << "Powiadom 1 osobe w kolejce ze ksiazka jest dostepna dla niego";
						}
						book.updateLista(book.file);
						
					}
					else if (index == 0) {
						book.usunZListy(index);
						if (book.listaOczekujacych.empty()) {
							book.dostepnosc = "tak";
							cout << book.nazwa << " jest dostepna do wypozyczenia" << endl;
							book.updateLista(book.file);
							
						}
						else {
							cout << "Powiadom 2 osobe w kolejce ze ksiazka jest dostepna dla niego";
							book.updateLista(book.file);
							
						}
					}
	
				}
				index++;
			}
		}
	}

};



int main() {
	int wybor;
	do {
		Biblioteka biblioteka("Clients.txt", "Books.txt");
		system("CLS");
		cout << "Menu:" << endl;
		cout << "1. Dodanie czytelnika" << endl;
		cout << "2. Wyswietlenie Dostepnosci Ksiazki" << endl;
		cout << "3. Zapis na liste oczekujacych na ksiazke" << endl;
		cout << "4. Oddanie ksiazki (zmiana stanu dostepnosci i powiadomienie klientow o jej dostepnosci ktorzy sa zapisani na liscie)" << endl;
		cout << "0. Wyjdz" << endl;
		cout << "Wybierz opcje: ";
		cin >> wybor;
		int idx;
		string ksiazka_wybor;
		switch (wybor) {


		case 1: //dodannie klienta do Biblioteki 
			biblioteka.noweZgloszenie();
			system("CLS");
			cout << "Dodano nowego Klienta";
			_getch();
			biblioteka.updateFile();
			break;


		case 2: //wypisanie dostepnosci ksiazek
			system("CLS");
			biblioteka.wypiszDostepnosc();
			cout << endl << endl;
			_getch();
			break;


		case 3:
		system("CLS");
		cout << "Wybierz klienta dla ktorego chcesz dodac do listy ksiazki: " << endl;
		biblioteka.wypiszKlientow();
		cout << endl << endl;
		idx = getIndx();
		system("CLS");
		cout << "Klient nr: " << idx;
		cout << endl << "Wybierz ksiazke do ktorej ma klient zostac dodany do listy oczekujacych" << endl;
		biblioteka.wypiszKsiazki();
		cout << endl << endl;
		ksiazka_wybor = getString();
		biblioteka.dodajDoListy(ksiazka_wybor, idx);
		system("CLS");
		cout << "Dodano klienta do listy oczekujacych dla ksiazki: " <<ksiazka_wybor<<endl;
		biblioteka.wypiszKlienta(idx);
		biblioteka.updateFile();
		_getch();
		break;


		case 4:
			system("CLS");
			biblioteka.wypiszKlientow();
			cout << endl << endl << "Wybierz klienta ktory ma oddac ksiazke: " << endl;
			idx = getIndx();
			system("CLS");
			cout << "Klient nr: " << idx;
			biblioteka.wypiszKlienta(idx);
			biblioteka.oddajKsiazke(idx);
			biblioteka.updateFile();
			_getch();
			system("CLS");
			break;

		case 0:
			cout << "Zakonczono program." << endl;
			break;

		default:
			cout << "Nieprawidlowa opcja. Sprobuj ponownie." << endl;
			_getch();

		}

	} while (wybor != 0);

	system("pause");
	return 0;
}




