#pragma once
#include "clase.h"
#include <iostream>
#include<string>
#include <algorithm>
#include <regex>
#include <fstream>
//#include <stdio.h>
#include<new>
#pragma warning(disable : 4996)
#define OUT 0  
#define IN 1  
using namespace std;

class exceptii
{
	string mesaj_exceptie;
public:
	exceptii(string mesaj)
	{
		this->mesaj_exceptie = mesaj;
	}
	string get_mesaj_exceptie()
	{
		return mesaj_exceptie;
	}
};

class Coloana
{
private:
	friend class Parsing;
	friend class Baza;
	friend class Rand;
	friend class Tabela;
	friend class LDD;
	friend class LMD;
	string nume_coloana;
	string tip;
	int dimensiune;
	char* valoare_implicita;
public:
	Coloana() //constructor implicit
	{
		nume_coloana = "";
		tip = "";
		dimensiune = 0;
		valoare_implicita = nullptr;
	}

	Coloana(string n, string t, int d) //constructor cu parametri
	{
		nume_coloana = n;
		tip = t;
		if (d > 0)
		{
			dimensiune = d;
		}
		else
		{
			dimensiune = 0;
		}
		valoare_implicita = nullptr;
	}

	Coloana(string nume_coloana, string tip, int dimensiune, string valoare_implicita) //constructor cu parametri
	{
		this->nume_coloana = nume_coloana;
		this->tip = tip;
		if (dimensiune > 0)
			this->dimensiune = dimensiune;
		else this->dimensiune = 0;
		if (valoare_implicita.length() > 0)
		{
			this->valoare_implicita = new char[valoare_implicita.length() + 1];
			strcpy_s(this->valoare_implicita, valoare_implicita.length() + 1, valoare_implicita.c_str());
		}
		else
		{
			this->valoare_implicita = nullptr;
		}
	}

	Coloana(const Coloana& c) //constructor de copiere
	{
		this->nume_coloana = c.nume_coloana;
		this->tip = c.tip;
		if (c.dimensiune > 0)
			this->dimensiune = c.dimensiune;
		else this->dimensiune = 0;

		if (c.valoare_implicita != nullptr)
		{
			this->valoare_implicita = new char[strlen(c.valoare_implicita) + 1];
			strcpy_s(this->valoare_implicita, strlen(c.valoare_implicita) + 1, c.valoare_implicita);
		}
		else
		{
			this->valoare_implicita = nullptr;
		}
	}

	~Coloana() //destructor
	{
		if (this->valoare_implicita != nullptr)
		{
			delete[] this->valoare_implicita;
		}
	}

	Coloana operator=(const Coloana& c) //operator=
	{
		if (this->valoare_implicita != nullptr)
		{
			delete[] this->valoare_implicita;
		}
		this->nume_coloana = c.nume_coloana;
		this->tip = c.tip;
		if (c.dimensiune > 0)
			this->dimensiune = c.dimensiune;
		else this->dimensiune = 0;

		if (c.valoare_implicita != nullptr)
		{
			this->valoare_implicita = new char[strlen(c.valoare_implicita) + 1];
			strcpy_s(this->valoare_implicita, strlen(c.valoare_implicita) + 1, c.valoare_implicita);
		}
		else
		{
			this->valoare_implicita = nullptr;
		}
		return *this;
	}

	char& operator[](int index) //operatorul pentru indexare
	{
		if (index >= 0 && index < strlen(valoare_implicita))
		{
			return valoare_implicita[index];
		}
		throw exception("index invalid");
	}

	Coloana operator+(int valoare) //operator+
	{
		if (valoare > 0)
		{
			Coloana copie = *this;
			copie.dimensiune += valoare;
			return copie;
		}
		else
		{
			throw 1;
		}
	}

	Coloana operator++() //operator++ 1)
	{
		this->dimensiune++;
		return *this;
	}

	Coloana operator++(int i) //operator++ 2)
	{
		Coloana copie = *this;
		this->dimensiune++;
		return copie;
	}

	explicit operator int() //operator de cast explicit
	{
		return dimensiune;
	}

	bool operator!() //operator!
	{
		return dimensiune > 0;
	}

	bool operator==(Coloana& c) //operator==
	{
		Coloana d = (Coloana&)c;
		if (this->dimensiune == d.dimensiune)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	string getnume_coloana()
	{
		return nume_coloana;
	}

	void setnume_coloana(string nume_coloana)
	{
		const char* n = nume_coloana.c_str();
		if (strlen(n) > 0)
		{
			this->nume_coloana = nume_coloana;
		}
		else
			nume_coloana = "";
	}

	string gettip()
	{
		return tip;
	}

	void settip(string tip)
	{
		const char* t = tip.c_str();
		if (strlen(t) > 0)
		{
			this->tip = tip;
		}
		else
			tip = "";
	}

	int getdimensiune()
	{
		return dimensiune;
	}

	void setdimensiune(int dimensiune)
	{
		if (dimensiune > 0)
		{
			this->dimensiune = dimensiune;
		}
	}

	char* getvaloare_implicita()
	{
		if (valoare_implicita != nullptr)
		{
			char* k = new char[strlen(this->valoare_implicita) + 1];
			strcpy_s(k, strlen(this->valoare_implicita) + 1, this->valoare_implicita);
			return k;
		}
		return nullptr;
	}

	void setvaloare_implicita(const char* valoare_implicita)
	{
		if (valoare_implicita != nullptr)
		{
			this->valoare_implicita = new char[strlen(valoare_implicita) + 1];
			strcpy_s(this->valoare_implicita, strlen(valoare_implicita) + 1, valoare_implicita);
		}
		else
		{
			cout << "Nu s-a modificat valoarea implicita. Introduceti o valoare concreta." << endl;
		}
	}

	void afisare_atribute(string atribut)  //Metoda de afisare a atributelor
	{
		if (atribut == "nume_coloana") {
			cout << "Nume coloana: " << nume_coloana << endl;
		}
		else if (atribut == "tip") {
			cout << "Tip: " << tip << endl;
		}
		else if (atribut == "dimensiune") {
			cout << "Dimensiune: " << dimensiune << endl;
		}
		else if (atribut == "valoare_implicita") {
			if (valoare_implicita != nullptr)
			{
				cout << "Valoare implicita: ";
				cout << valoare_implicita;
			}
			else {
				cout << "Nu avem valoare implicita!";
			}
			cout << endl;
		}
		else {
			cout << "Dati un parametru corect!" << endl;
		}
	}

	void nume_majuscule() //metoda de prelucrare a atributului nume_coloana: il transforma in majuscule si il afiseaza
	{
		cout << "Nume coloana initial: " << nume_coloana << endl;
		transform(nume_coloana.begin(), nume_coloana.end(), nume_coloana.begin(), ::toupper);
		cout << "Nume coloana cu majuscule: " << nume_coloana << endl;
	}
	void nume_litereMici() //metoda de prelucrare a atributului nume_coloana: il transforma in litere mici si il afiseaza
	{
		cout << "Nume coloana initial: " << nume_coloana << endl;
		transform(nume_coloana.begin(), nume_coloana.end(), nume_coloana.begin(), ::tolower);
		cout << "Nume coloana cu litere mici: " << nume_coloana << endl;
	}

	friend ostream& operator<<(ostream&, const Coloana&);
	friend istream& operator>>(istream&, Coloana&);
	friend ifstream& operator>>(ifstream& in, Coloana& c);
};

ostream& operator<<(ostream& out, const Coloana& c)
{
	out << c.nume_coloana << endl;
	out << c.tip << endl;
	out << c.dimensiune << endl;
	if (c.valoare_implicita != nullptr)
	{
		out << c.valoare_implicita << endl;
	}
	out << endl;
	return out;
}

istream& operator>>(istream& in, Coloana& c)
{
	in >> ws;
	cout << "nume coloana = ";
	in >> ws;
	getline(in, c.nume_coloana);
	cout << "tip = ";
	in >> ws;
	getline(in, c.tip);
	cout << "dimensiune = ";
	in >> ws;
	in >> c.dimensiune;
	char buffer[100];
	cout << "valoare implicita: ";
	in >> ws;
	in.getline(buffer, 99);
	if (c.valoare_implicita != nullptr)
	{
		delete[] c.valoare_implicita;
	}
	c.valoare_implicita = new char[strlen(buffer) + 1];
	strcpy_s(c.valoare_implicita, strlen(buffer) + 1, buffer);
	return in;
}

ifstream& operator>>(ifstream& in, Coloana& c)
{
	in >> ws;
	getline(in, c.nume_coloana);
	in >> ws;
	getline(in, c.tip);
	in >> ws;
	in >> c.dimensiune;
	char buffer[100];
	in >> ws;
	in.getline(buffer, 99);
	if (c.valoare_implicita != nullptr)
	{
		delete[] c.valoare_implicita;
	}
	c.valoare_implicita = new char[strlen(buffer) + 1];
	strcpy_s(c.valoare_implicita, strlen(buffer) + 1, buffer);
	in >> ws;
	return in;
}

class Rand
{
private:
	friend class Parsing;
	friend class Baza;
	friend class Coloana;
	friend class Tabela;
	friend class LDD;
	friend class LMD;
	int nr_coloane = 0;
	string* valori;
public:
	Rand() //constructor implicit
	{
		nr_coloane = 0;
		valori = nullptr;
	}

	Rand(int n) //constructor cu parametri
	{
		if (n > 0)
		{
			nr_coloane = n;
		}
		else
		{
			nr_coloane = 0;
		}
		valori = nullptr;
	}

	Rand(int n, string* valori) //constructor cu parametri
	{
		if (n > 0 && valori != nullptr)
		{
			nr_coloane = n;
			this->valori = new string[n];
			for (int i = 0; i < n; i++)
			{
				this->valori[i] = valori[i];
			}
		}
		else
		{
			this->valori = nullptr;
			nr_coloane = 0;
		}
	}

	Rand(const Rand& r) //constructor de copiere
	{
		if (r.valori != nullptr && r.nr_coloane > 0)
		{
			this->nr_coloane = r.nr_coloane;
			this->valori = new string[r.nr_coloane];
			for (int i = 0; i < r.nr_coloane; i++)
			{
				this->valori[i] = r.valori[i];
			}
		}
		else {
			this->nr_coloane = 0;
			this->valori = nullptr;
		}
	}

	~Rand() //destructor
	{
		if (valori != nullptr)
		{
			delete[] valori;
		}
	}

	Rand& operator=(const Rand& r) //operator=
	{
		if (valori != nullptr)
		{
			delete[] valori;
		}
		if (r.valori != nullptr && r.nr_coloane > 0)
		{
			this->nr_coloane = r.nr_coloane;
			this->valori = new string[r.nr_coloane];
			for (int i = 0; i < r.nr_coloane; i++)
			{
				this->valori[i] = r.valori[i];
			}
		}
		else {
			this->nr_coloane = 0;
			this->valori = nullptr;
		}
		return *this;
	}

	string& operator[](int index) //operatorul pentru indexare
	{
		if (index >= 0 && index < nr_coloane)
		{
			return valori[index];
		}
		throw exception("index invalid");
	}

	Rand operator+(int valoare) //operator+
	{
		if (valoare > 0)
		{
			Rand copie = *this;
			copie.nr_coloane += valoare;
			return copie;
		}
		else
		{
			throw 1;
		}
	}

	Rand operator++() //operator++ 1)
	{
		this->nr_coloane++;
		return *this;
	}

	Rand operator++(int i) //operator++ 2)
	{
		Rand copie = *this;
		this->nr_coloane++;
		return copie;
	}

	explicit operator int() //operator de cast explicit
	{
		return nr_coloane;
	}

	bool operator!() //operator!
	{
		return nr_coloane > 0;
	}

	bool operator==(Rand& r) //operator==
	{
		Rand d = (Rand&)r;
		if (this->nr_coloane == d.nr_coloane)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void set_valori(string* vals, int nr)
	{
		if (vals != nullptr && nr > 0)
		{
			if (this->valori != nullptr)
			{
				delete[] this->valori;
			}
			this->nr_coloane = nr;
			this->valori = new string[nr];
			for (int i = 0; i < nr; i++)
			{
				valori[i] = vals[i];
			}
		}
	}

	string* get_valori()
	{
		if (valori != nullptr && nr_coloane > 0)
		{
			string* copie = new string[nr_coloane];
			for (int i = 0; i < nr_coloane; i++)
			{
				copie[i] = valori[i];
			}
			return copie;
		}
		return nullptr;
	}

	int getnr_coloane()
	{
		return nr_coloane;
	}

	void setnrcoloane(int nr_coloane)
	{
		if (nr_coloane > 0)
		{
			this->nr_coloane = nr_coloane;
		}
		else
		{
			nr_coloane = 0;
		}
	}

	void afisare_atribute(string atribut)  //metoda de afisare a atributelor
	{
		if (atribut == "nr_coloane") {
			cout << "Numar coloane: " << nr_coloane << endl;
		}
		else if (atribut == "valori") {
			cout << "Randurile: " << endl;
			if (valori != nullptr)
			{
				for (int i = 0; i < nr_coloane; i++)
				{
					cout << valori[i] << " ";
				}
			}
			else {
				cout << "Nu avem randuri!" << endl;
			}
		}
		else {
			cout << "Dati un parametru corect!" << endl;
		}
	}

	string nr_coloane_string()  //metoda de prelucrare a atributului nr_coloane
	{
		string nrColoaneString;
		nrColoaneString = to_string(this->nr_coloane);
		return nrColoaneString;
	}

	friend ostream& operator<<(ostream&, Rand);
	friend istream& operator>>(istream&, Rand&);
	friend ifstream& operator>>(ifstream& in, Rand& r);
	friend ofstream& operator<<(ofstream& out, Rand r);
};

ostream& operator<<(ostream& out, Rand r)
{
	//out << "Numar coloane: ";//<< r.nr_coloane << endl;
	//out << r.nr_coloane << endl;
	if (r.valori != nullptr)
	{
		//out << "Randuri: " << endl;
		for (int i = 0; i < r.nr_coloane; i++)
		{
			out << r.valori[i] << " " << endl;
		}
		out << endl;

	}
	return out;
}

ofstream& operator<<(ofstream& out, Rand r)
{
	string y = to_string(r.nr_coloane);
	const char* ux = y.c_str();
	out << ux << endl;
	if (r.valori != nullptr)
	{
		for (int i = 0; i < r.nr_coloane; i++)
		{
			const char* ux = r.valori[i].c_str();
			out << ux << " " << endl;
		}
		out << endl;
	}
	return out;
}

istream& operator>>(istream& in, Rand& r)
{
	cout << "numar coloane = ";
	in >> r.nr_coloane;
	if (r.valori != nullptr)
	{
		delete[] r.valori;
	}
	if (r.nr_coloane > 0)
	{
		r.valori = new string[r.nr_coloane];
		for (int i = 0; i < r.nr_coloane; i++)
		{
			cout << "valori[" << i << "] = ";
			in >> r.valori[i]; in >> ws;
		}
	}
	else
	{
		r.nr_coloane = 0;
		r.valori = nullptr;
	}
	return in;
}

ifstream& operator>>(ifstream& in, Rand& r)
{
	in >> r.nr_coloane;
	if (r.valori != nullptr)
	{
		delete[] r.valori;
	}
	if (r.nr_coloane > 0)
	{
		r.valori = new string[r.nr_coloane];
		for (int i = 0; i < r.nr_coloane; i++)
		{
			cout << "valori[" << i << "] = ";
			in >> r.valori[i]; in >> ws;
		}
	}
	else
	{
		r.nr_coloane = 0;
		r.valori = nullptr;
	}
	return in;
}

class Tabela
{
private:
	friend class Parsing;
	friend class Baza;
	friend class LMD;
	friend class Coloana;
	friend class Rand;
	Rand* tabela; //O tabela reprezinta un vector de randuri
	string nume_tabela;
	friend class LDD;
	friend class LMD;
	int nr_randuri;
	Coloana* coloane; //structural, o tabela contine un vector de coloane
	int nrC;
	static int nrTabele;
public:

	Tabela()  //constructor implicit
	{
		nume_tabela = "";
		nr_randuri = 0;
		tabela = nullptr;
		coloane = nullptr;
		nrC = 0;
	}

	Tabela(string nume_tabela)  //constructor cu parametri
	{
		nr_randuri = 0;
		tabela = nullptr;
		coloane = nullptr;
		nrC = 0;
		if (nume_tabela != "")
		{
			this->nume_tabela = nume_tabela;
		}
		else
		{
			nume_tabela = "";
		}
	}

	Tabela(Coloana* coloane, int nrC, string nume_tabela)  //constructor cu parametri
	{
		this->nume_tabela = nume_tabela;
		tabela = nullptr; nr_randuri = 0;
		if (coloane != nullptr && nrC > 0)
		{
			this->nrC = nrC;
			this->coloane = new Coloana[nrC];
			for (int i = 0; i < nrC; i++)
			{
				this->coloane[i] = coloane[i];
			}
		}
		else {
			this->nrC = 0;
			this->coloane = nullptr;
		}
	}

	Tabela(const Tabela& t) //constructor de copiere
	{
		this->nrTabele = t.nrTabele;
		this->nume_tabela = t.nume_tabela;
		if (t.tabela != nullptr && t.nr_randuri > 0)
		{
			this->nr_randuri = t.nr_randuri;
			this->tabela = new Rand[t.nr_randuri];
			for (int i = 0; i < t.nr_randuri; i++)
			{
				this->tabela[i] = t.tabela[i];
			}
		}
		else
		{
			this->tabela = nullptr;
			this->nr_randuri = 0;
		}
		if (t.coloane != nullptr && t.nrC > 0)
		{
			this->nrC = t.nrC;
			this->coloane = new Coloana[t.nrC];
			for (int i = 0; i < nrC; i++)
			{
				this->coloane[i] = t.coloane[i];
			}
		}
		else {
			this->nrC = 0;
			this->coloane = nullptr;
		}
	}
	~Tabela() //destructor
	{
		if (tabela != nullptr)
		{
			delete[] tabela;
			tabela = nullptr;
		}
		if (coloane != nullptr)
		{
			delete[] coloane;
		}
	}

	Tabela& operator=(const Tabela& t) //operator=
	{
		if (tabela != nullptr)
		{
			delete[] tabela;
			tabela = nullptr;
		}
		if (coloane != nullptr)
		{
			delete[] coloane;
		}
		this->nrTabele = t.nrTabele;
		this->nume_tabela = t.nume_tabela;
		if (t.tabela != nullptr && t.nr_randuri > 0)
		{
			this->nr_randuri = t.nr_randuri;
			this->tabela = new Rand[t.nr_randuri];
			for (int i = 0; i < t.nr_randuri; i++)
			{
				this->tabela[i] = t.tabela[i];
			}
		}
		else
		{
			this->tabela = nullptr;
			this->nr_randuri = 0;
		}
		if (t.coloane != nullptr && t.nrC > 0)
		{
			this->nrC = t.nrC;
			this->coloane = new Coloana[t.nrC];
			for (int i = 0; i < nrC; i++)
			{
				this->coloane[i] = t.coloane[i];
			}
		}
		else {
			this->nrC = 0;
			this->coloane = nullptr;
		}

		return *this;
	}

	Rand& operator[](int index) //operatorul pentru indexare
	{
		if (index >= 0 && index < nr_randuri)
		{
			return tabela[index];
		}
		throw exception("index invalid");
	}

	Tabela operator+(int valoare) //operator+
	{
		if (valoare > 0)
		{
			Tabela copie = *this;
			copie.nr_randuri += valoare;
			return copie;
		}
		else throw 1;
	}

	Tabela operator++() //operator++ 1)
	{
		this->nr_randuri++;
		return *this;
	}

	Tabela operator++(int i) //operator++ 2)
	{
		Tabela copie = *this;
		this->nr_randuri++;
		return copie;
	}

	explicit operator int() //operator de cast explicit
	{
		return nr_randuri;
	}

	bool operator!() //operator!
	{
		return nr_randuri > 0;
	}

	bool operator==(Tabela& c) //operator==
	{
		Tabela d = (Tabela&)c;
		if (this->nr_randuri == d.nr_randuri)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	static int get_nrTabele()
	{
		return nrTabele;
	}

	int getnr_randuri()
	{
		return nr_randuri;
	}

	void setnr_randuri(int nr_randuri)
	{
		if (nr_randuri > 0)
			this->nr_randuri = nr_randuri;
	}

	string getnume_tabela()
	{
		return nume_tabela;
	}

	void setnume_tabela(string nume_tabela)
	{
		const char* t = nume_tabela.c_str();
		if (strlen(t) > 0)
		{
			this->nume_tabela = nume_tabela;
		}
		else
			nume_tabela = "";
	}

	void setColoane(Coloana* coloane, int nrC)
	{
		if (coloane != nullptr && nrC > 0)
		{
			if (this->coloane != nullptr)
			{
				delete[] this->coloane;
			}
			this->coloane = new Coloana[nrC];
			for (int i = 0; i < nrC; i++)
			{
				this->coloane[i] = coloane[i];
			}
			this->nrC = nrC;
		}
	}

	Rand* gettabela()
	{
		if (tabela != nullptr && nr_randuri > 0)
		{
			Rand* copie = new Rand[nr_randuri];
			for (int i = 0; i < nr_randuri; i++)
			{
				copie[i] = tabela[i];
			}
			return copie;
		}
		return nullptr;
	}

	void setranduri(Rand* tabela, int nr_randuri)
	{
		if (tabela != nullptr && nr_randuri > 0)
		{
			if (this->tabela != nullptr)
			{
				delete[] this->tabela;
			}
			this->nr_randuri = nr_randuri;
			this->tabela = new Rand[nr_randuri];
			for (int i = 0; i < nr_randuri; i++)
			{
				this->tabela[i] = tabela[i];
			}

		}
	}

	void nume_majuscule() //metoda de prelucrare a atributului nume_tabela: transforma in majuscule si il afiseaza
	{
		cout << "Nume tabela initial: " << nume_tabela << endl;
		transform(nume_tabela.begin(), nume_tabela.end(), nume_tabela.begin(), ::toupper);
		cout << "Nume tabela cu majuscule: " << nume_tabela << endl;
	}
	void nume_litereMici() //metoda de prelucrare a atributului nume_tabela: transforma in litere mici si il afiseaza
	{
		cout << "Nume tabela initial: " << nume_tabela << endl;
		transform(nume_tabela.begin(), nume_tabela.end(), nume_tabela.begin(), ::tolower);
		cout << "Nume tabela cu litere mici: " << nume_tabela << endl;
	}
	void afisare_tabela()  //metoda de afisare a tabelei
	{
		cout << "Nume tabela: ";
		cout << nume_tabela << endl;
		cout << "Numar coloane: ";
		cout << nrC << endl;
		if (coloane != nullptr)
		{
			cout << "Coloane: " << endl;
			for (int i = 0; i < nrC; i++)
			{
				cout << coloane[i] << " ";
			}
			cout << endl;
		}
		cout << "Nr tabele: ";
		cout << Tabela::nrTabele << endl;
	}

	void serializare(ofstream& f)
	{
		f.write((char*)&nr_randuri, sizeof(nr_randuri));		
		f.write((char*)&tabela[0].nr_coloane, sizeof(tabela[0].nr_coloane));		
		for (int j = 0; j < tabela[0].nr_coloane; j++)
		{
			int length = tabela[0].valori[j].length();
			f.write((char*)&length, sizeof(length));	
			length++;
			f.write(tabela[0].valori[j].c_str(), length);
		}

		f.write((char*)&nrC, sizeof(nrC));   //scrie nrc adica 2
		f.write((char*)&nr_randuri, sizeof(nr_randuri));
	}

	void deserializare(ifstream& f)
	{
		f.read((char*)&nr_randuri, sizeof(nr_randuri));
		f.seekg(0, ios::beg);
		if (tabela != nullptr)
			delete[] tabela;
		tabela = new Rand[nr_randuri];
		for (int i = 0; i < nr_randuri; i++)
		{
			int x = 0;
			//cout << "Rand " << i + 1 << endl;
			f.read((char*)&x, sizeof(x));
			f.read((char*)&tabela[i].nr_coloane, sizeof(tabela[i].nr_coloane));
			if (tabela[i].valori != nullptr)
				delete[] tabela[i].valori;
			tabela[i].valori = new string[tabela[i].nr_coloane];
			for (int j = 0; j < tabela[i].nr_coloane; j++)
			{
				//cout << "nr col: " << tabela[i].nr_coloane<<endl;
				int length = 0;
				f.read((char*)&length, sizeof(length));
				length++;
				char* aux = new char[length];
				f.read(aux, length);
				this->tabela[i].valori[j] = aux;
				//cout << "val " << i << " " << j << " " << tabela[i].valori[j] << endl;
				if (aux != nullptr)
					delete[] aux;
			}
			f.read((char*)&nrC, sizeof(nrC));
			f.read((char*)&x, sizeof(x));
		}
		f.seekg(0, ios::end);
		if (!f.is_open()) cout << "Fisierul binar nu s-a deschis!" << endl;
	}

	friend ostream& operator<<(ostream&, const Tabela&);
	friend istream& operator>>(istream&, Tabela&);
	friend ofstream& operator<<(ofstream& out, const Tabela& t);
	friend ifstream& operator>>(ifstream&, Tabela&);
};

int Tabela::nrTabele = 0;

ostream& operator<<(ostream& out, const Tabela& t)
{
	//out << "Nume tabela: ";
	//out << t.nume_tabela << endl;
	if (t.coloane != nullptr)
	{
		out << "Coloane: " << endl;
		for (int i = 0; i < t.nrC; i++)
		{
			out << t.coloane[i] << " ";
		}
		out << endl;
	}
	//out << "Numar randuri: ";
	//out << t.nr_randuri << endl;
	//out << "Randuri: " << endl;
	if (t.tabela != nullptr)
	{
		for (int i = 0; i < t.nr_randuri; i++)
		{
			out << t.tabela[i] << " ";
		}
		out << endl;
	}
	out << "Nr tabele: ";
	out << Tabela::nrTabele << endl;
	return out;
}
istream& operator>>(istream& in, Tabela& t)
{
	cout << "nume tabela = ";
	in >> ws;
	getline(in, t.nume_tabela);
	cout << "numar coloane = ";
	in >> t.nrC;
	if (t.coloane != nullptr)
	{
		delete[] t.coloane;
	}
	if (t.nrC > 0)
	{
		t.coloane = new Coloana[t.nrC];
		for (int i = 0; i < t.nrC; i++)
		{
			cout << "coloane[" << i << "] = ";
			in >> t.coloane[i]; in >> ws;
		}
	}
	else
	{
		t.nrC = 0;
		t.coloane = nullptr;
	}
	t.nr_randuri = 0; t.tabela = nullptr;
	return in;
}

ofstream& operator<<(ofstream& f, const Tabela& t)
{
	if (f.is_open())
	{
		const char* aux = t.nume_tabela.c_str();
		f << aux << endl;
		string y = to_string(t.nrC);
		const char* ux = y.c_str();
		f << ux << endl;
		string w = to_string(t.nr_randuri);
		const char* au = w.c_str();
		f << au << endl;
		if (t.coloane != nullptr && t.nrC > 0)
		{
			for (int i = 0; i < t.nrC; i++)
			{
				f << t.coloane[i] << " ";
			}
			f << endl;
		}
		cout << "Tabela a fost salvata in fisier." << endl;
	}
	return f;
}
ifstream& operator>>(ifstream& in, Tabela& t)
{
	if (in.is_open())
	{
		in >> ws;
		getline(in, t.nume_tabela);
		in >> t.nrC;
		in >> t.nr_randuri;
		if (t.coloane != nullptr)
		{
			delete[] t.coloane;
		}
		if (t.nrC > 0)
		{
			t.coloane = new Coloana[t.nrC];
			for (int i = 0; i < t.nrC; i++)
			{
				in >> t.coloane[i]; in >> ws;
			}
		}
		else
		{
			t.nrC = 0;
			t.coloane = nullptr;
		}
		t.tabela = nullptr;
	}
	return in;
}

class Baza
{
private:
	friend class Parsing;
	friend class Tabela;
	friend class Coloana;
	friend class Rand;
	friend class LDD;
	friend class LMD;
	Tabela* baza; //Baza reprezinta un vector de tabele
	const char* nume_db = "Baza mea";
	int nr_tabele;

public:
	Baza() //constructor implicit
	{
		nume_db = "";
		nr_tabele = 0;
		baza = nullptr;
	}

	Baza(int t) //constructor cu parametri
	{
		if (t > 0)
		{
			nr_tabele = t;
			baza = new Tabela[nr_tabele];
		}
		else
		{
			nr_tabele = 0;
			baza = nullptr;
		}
	}

	Baza(int nr_tabele, Tabela* tabele) //constructor cu parametri
	{
		if (tabele != nullptr && nr_tabele > 0)
		{
			this->nr_tabele = nr_tabele;
			this->baza = new Tabela[nr_tabele];
			for (int i = 0; i < nr_tabele; i++)
			{
				this->baza[i] = tabele[i];
			}
		}
		else {
			this->nr_tabele = 0;
			this->baza = nullptr;
		}
	}

	Baza(const Baza& b) //constructor de copiere
	{
		this->nume_db = b.nume_db;
		if (b.baza != nullptr && b.nr_tabele > 0)
		{
			this->nr_tabele = b.nr_tabele;
			this->baza = new Tabela[b.nr_tabele];
			for (int i = 0; i < b.nr_tabele; i++)
			{
				this->baza[i] = b.baza[i];
			}
		}
		else {
			this->nr_tabele = 0;
			this->baza = nullptr;
		}
	}

	~Baza() //destructor
	{
		if (baza != nullptr)
		{
			baza = nullptr;
		}
	}

	Baza& operator=(const Baza& b) //operator=
	{
		if (baza != nullptr)
		{
			delete[] baza;
		}
		this->nume_db = b.nume_db;
		if (b.baza != nullptr && b.nr_tabele > 0)
		{
			this->nr_tabele = b.nr_tabele;
			this->baza = new Tabela[b.nr_tabele];
			for (int i = 0; i < b.nr_tabele; i++)
			{
				this->baza[i] = b.baza[i];
			}
		}
		else {
			this->nr_tabele = 0;
			this->baza = nullptr;
		}
		return *this;
	}

	Tabela& operator[](int index) //operatorul pentru indexare
	{
		if (index >= 0 && index < nr_tabele)
		{
			return baza[index];
		}
		throw exception("index invalid");
	}

	Baza operator+(int valoare) //operator+
	{
		if (valoare > 0)
		{
			Baza copie = *this;
			copie.nr_tabele += valoare;
			return copie;
		}
		else
		{
			throw 1;
		}
	}

	Baza operator++() //operator++ 1)
	{
		this->nr_tabele++;
		return *this;
	}

	Baza operator++(int i) //operator++ 2)
	{
		Baza copie = *this;
		this->nr_tabele++;
		return copie;
	}

	explicit operator int() //operator de cast explicit
	{
		return nr_tabele;
	}

	bool operator!() //operator!
	{
		return nr_tabele > 0;
	}

	bool operator==(Baza& b) //operator==
	{
		Baza d = (Baza&)b;
		if (this->nr_tabele == d.nr_tabele)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	int getnr_tabele()
	{
		return nr_tabele;
	}

	void setnr_tabele(int nr_tabele)
	{
		if (nr_tabele > 0)
		{
			this->nr_tabele = nr_tabele;
		}
		else
		{
			nr_tabele = 0;
		}
	}

	const char* get_nume()
	{
		return this->nume_db; 
		//nu avem nevoie de verificare dearece este mereu "Baza mea"
		//nu avem nevoie sa returnam o copie pentru ca nume_db nu este modificabil
	}						  

	Tabela* getbaza()
	{
		if (baza != nullptr && nr_tabele > 0)
		{
			Tabela* copie = new Tabela[nr_tabele];
			for (int i = 0; i < nr_tabele; i++)
			{
				copie[i] = baza[i];
			}
			return copie;
		}
		return nullptr;
	}

	void setbaza(Tabela* baza, int nr_tabele)
	{
		if (baza != nullptr && nr_tabele > 0)
		{
			if (this->baza != nullptr)
			{
				delete[] this->baza;
			}
			this->baza = new Tabela[nr_tabele];
			for (int i = 0; i < nr_tabele; i++)
			{
				this->baza[i] = baza[i];
			}
			this->nr_tabele = nr_tabele;
		}
	}

	void nume_majuscule() //metoda de prelucrare a atributului nume_db: transforma in majuscule si il afiseaza
	{
		cout << "Nume baza initial: " << nume_db << endl;
		string name = nume_db;
		transform(name.begin(), name.end(), name.begin(), ::toupper);
		cout << "Nume baza cu majuscule: " << name << endl;
	}

	void nume_litereMici() //metoda de prelucrare a atributului nume_db: transforma in litere mici si il afiseaza
	{
		cout << "Nume baza initial: " << nume_db << endl;
		string name = nume_db;
		transform(name.begin(), name.end(), name.begin(), ::tolower);
		cout << "Nume baza cu litere mici: " << name << endl;
	}

	friend ostream& operator<<(ostream&, Baza);
	friend istream& operator>>(istream&, Baza&);
};

ostream& operator<<(ostream& out, Baza b)
{
	out << "nume baza: " << b.nume_db << endl;
	out << "numar tabele: " << b.nr_tabele << endl;
	if (b.baza != nullptr)
	{
		out << "tabele: " << endl;
		for (int i = 0; i < b.nr_tabele; i++)
		{
			out << b.baza[i] << " ";
		}
	}
	return out;
}

istream& operator>>(istream& in, Baza& b)
{
	cout << "numar tabele = ";
	in >> b.nr_tabele;
	if (b.baza != nullptr)
	{
		delete[] b.baza;
	}
	if (b.nr_tabele > 0)
	{
		b.baza = new Tabela[b.nr_tabele];
		for (int i = 0; i < b.nr_tabele; i++)
		{
			cout << "baza[" << i << "] = ";
			in >> b.baza[i];
		}
	}
	else
	{
		b.nr_tabele = 0;
		b.baza = nullptr;
	}
	return in;
}




class LDD
{
	friend class Coloana;
	friend class Rand;
	friend class Tabela;
	friend class Baza;
	friend class Parsing;
	friend class LMD;
	string com;
	int nr_cuvinte;
	Baza b;
public:

	LDD() //constructor implicit
	{
		com = "";
		nr_cuvinte = 0;
	}

	LDD(string comanda, int nr_cuvinte) //constructor cu parametri
	{
		this->com = comanda;
		this->nr_cuvinte = nr_cuvinte;
	}

	LDD(string comanda) //constructor cu parametri
	{
		this->com = comanda;
		int state = OUT;
		unsigned wc = 0;
		for (int i = 0; i < comanda.length(); i++)
		{
			if (comanda[i] == ' ' || comanda[i] == '=' || comanda[i] == ',' || comanda[i] == '(' || comanda[i] == ')')
				state = OUT;
			else if (state == OUT)
			{
				state = IN;
				++wc;
			}
		}
		this->nr_cuvinte = wc;
	}

	LDD(const LDD& l) //constructor de copiere
	{
		this->com = l.com;
		this->nr_cuvinte = l.nr_cuvinte;
	}

	~LDD() //destructor
	{

	}

	LDD& operator=(const LDD& l)
	{
		this->com = l.com;
		this->nr_cuvinte = l.nr_cuvinte;
		return *this;
	}

	bool check_nume(string expr)  //metoda de prelucrare a atributului baza
	{
		bool flag = false;
		for (int j = 0; j < b.nr_tabele; j++)
		{
			if (expr == b.baza[j].nume_tabela)
			{
				flag = true;
			}
		}
		string nume_fisier = expr + ".txt";  ifstream f; f.open(nume_fisier);
		//iau numele tabelei scris in comanda si adaug txt la final
		//pentru a vedea daca am deja un fisier asociat
		//unei tabele cu acest nume
		if (f.is_open())
		{											               			
			flag = true; //daca am gasit numele fisierului, am deja tabela			
		}
		else {
			cout << "Fisierul nu exista" << endl; //tabela nu exista
			flag = false;
		}
		return flag;
	}

	bool delimitariCorecte(string exp, int& p, int& v)  //metoda de prelucrare a sintaxei
	{
		bool flag = true;
		int nr = 0;

		for (int j = 0; j < exp.length(); j++)  //parcurg expresia
		{ 
			if (exp[j] == '(') //daca e o paranteza deschisa
			{
				nr++;
				p++; 
			}
			else 
			{
				if (exp[j] == ')') //daca e o paranteza inchisa
					nr--;   
				if (exp[j] == ',') 
				{
					if (nr == 0) 
					{ 
						cout << "Virgula incorecta!" << endl;
						flag = false;
						break;
					}
					else v++;
				}
			}
			if (nr < 0) 
			{ 
				flag = false; 
				break; 
			}
		}
		if (nr < 0) //daca sunt mai multe paranteze inchise
		{   
			flag = false;
			cout << "Parantezele nu corespund." << endl;
		}
		for (int j = 0; j < exp.length() - 1; j++) 
		{
			if (exp[j] == ',' && exp[j + 1] == ',') //daca virgulele sunt consecutive
			{
				cout << "Virgulele sunt consecutive, sintaxa gresita!" << endl;
				flag = false;
				break;
			}
		}
		return flag;
	}

	bool structura_tabela(string* cuvinte, int c) //metoda verifica daca structura tabelei este corecta, respectiv tipul de data introdus
	{
		bool flag = false;
		for (int i = 0; i < c; i++)
		{
			if (cuvinte[i * 4 + 4] == "integer" || cuvinte[i * 4 + 4] == "float" || cuvinte[i * 4 + 4] == "text")
			{
				flag = true;
			}
			else return false;
			regex ok("[1-9][0-9]*");
			regex text("necunoscut", regex_constants::icase);
			if (regex_match(cuvinte[i * 4 + 5], ok) == false)
			{
				return false;
			}
			if (cuvinte[i * 4 + 4] == "integer" || cuvinte[i * 4 + 4] == "float")
			{
				if (stoi(cuvinte[i * 4 + 6]) != 0) 
					return false;
				else 
					flag = true;
			}
			else if (cuvinte[i * 4 + 4] == "text") {
				if (regex_match(cuvinte[i * 4 + 6], text) == false) 
					return false;
				else 
					flag = true;
			}
		}
		return flag;
	}

	void set_baza(Baza b)  //la crearea bazei, o asociam obiectului de tip LDD pentru a gestiona comenzile
	{ 
		this->b = b;
	}

	Baza get_baza()
	{
		return this->b;
	}

	void CREATE_TABLE(string* cuvinte, int k) //k ia 2 valori: 1 daca avem un create table cu o sincura coloana, 2 daca tabela are doua sau mai multe coloane
	{		
		if (check_nume(cuvinte[2]) == false)  //check_name e actualizat
		{
			Coloana* col = nullptr; int nr = 0;
			if (k == 1)
			{							//tabelelor ar trebui sa fie separata de cea a datelor) (adica cand facem create nu ar trebui sa initializam randuri, alea aparand cand facem insert)
				Coloana c(cuvinte[3], cuvinte[4], stoi(cuvinte[5]), cuvinte[6]);  //creez o coloana
				col = new Coloana[1]; //creez vector de coloane, randurile
				nr = 1;
				col[0] = c;
			}
			else if (k == 2)
			{
				int p = 0, v = 0, m = 3; //p=paranteze, v=virgule, m=m e folosit pentru a lua din 4 in 4 cuvintele, pentru fiecare coloana, incepand de la cuvant[3], adica al 4-lea din create table
				delimitariCorecte(com, p, v); 
				col = new Coloana[p - 1]; //daca numarul de perechi de paranteze este p => numarul de coloane va fi p-1
				nr = p - 1;
				for (int i = 0; i < p - 1; i++) //pentru gestionarea mai multor coloane
				{
					Coloana c(cuvinte[m], cuvinte[m + 1], stoi(cuvinte[m + 2]), cuvinte[m + 3]);
					m += 4;
					col[i] = c;
				}
			}
			else throw("Nu s-a recunoscut comanda!");

			if (structura_tabela(cuvinte, nr) == true)
			{
				Tabela x(col, nr, cuvinte[2]);  //creez tabela
				Tabela* tabele = new Tabela[1]; //creez vector de tabele
				tabele[0] = x; //salvez tabela
				Baza b(1, tabele); //creez baza
				set_baza(b); //asociez parsingului
				string nume_fisier = cuvinte[2] + ".txt";  ofstream f; f.open(nume_fisier); //creez numele fisierului (nume tabela si extensie txt)
				f << x; //scriu in fisier
				cout << x; //afisez la consola
				f.close();
				delete[] tabele;
				delete[]col;
			}
			else 
			{
				cout << "Structura tabelei nu este corecta!" << endl;
			}
		}
		else
		{
			cout << "Tabela exista deja!" << endl;
		}
	}

	void DROP_TABLE(string* cuvinte)
	{
		string nume_fisier = cuvinte[2] + ".txt";  ifstream f; f.open(nume_fisier); //creez numele fisierului pe care il caut (nume tabela si extensie txt)
		if (check_nume(cuvinte[2]) == true || f.is_open())  //verific daca gasesc fisierul 
		{
			f.close();
			if (remove(nume_fisier.c_str()) != 0) //sterg fisierul text
				perror("Eroare stergere fisier.");
			else
				puts("Stergere structura tabela efectuata.");
			nume_fisier = cuvinte[2] + ".bin";  ifstream f; f.open(nume_fisier); //creez numele fisierului pe care il caut (nume tabela si extensie bin)
			if (f.is_open())
			{
				f.close();
				if (remove(nume_fisier.c_str()) != 0) //sterg fisierul binar
					perror("Eroare stergere fisier binar.");
				else
					puts("Stergere continut tabela efectuata.");
			}
		}
		else 
		{
			perror("Tabela nu exista.");
		}
		f.close();
	}
	void DISPLAY_TABLE(string* cuvinte)
	{
		string nume_fisier = cuvinte[2] + ".txt";  ifstream f; f.open(nume_fisier);
		if (check_nume(cuvinte[2]) == true || f.is_open())
		{
			cout << "Afisare tabela:" << endl;
			Tabela t;
			f >> t;
			t.afisare_tabela();
		}
		f.close();
	}

	void CREATE_INDEX(string* cuvinte)
	{

	}
	void DROP_INDEX(string* cuvinte)
	{

	}

	friend ostream& operator<<(ostream&, LDD);
	friend istream& operator>>(istream&, LDD&);
};

ostream& operator<<(ostream& out, LDD l)
{
	out << "comanda: " << l.com << endl;
	out << "numar cuvinte: " << l.nr_cuvinte << endl;
	//out << "nume tabela: " << p.nume_tabela << endl;
	return out;
}

istream& operator>>(istream& in, LDD& l)
{
	cout << "comanda = ";
	in >> l.com;
	cout << "numar cuvinte = ";
	in >> l.nr_cuvinte;
	//cout << "nume tabela = ";
	//in >> p.nume_tabela;
	return in;
}

class LMD
{
	friend class Coloana;
	friend class Rand;
	friend class Tabela;
	friend class Baza;
	friend class Parsing;
	friend class LDD;
	string coma;
	Baza b;
	int nr_cuvinte;
public:

	LMD() //constructor implicit
	{
		coma = "";
		nr_cuvinte = 0;
	}

	LMD(string co, int nr) //constructor cu parametri
	{
		this->coma = co;
		this->nr_cuvinte = nr;
	}


	LMD(const LMD& m) //constructor de copiere
	{
		this->coma = m.coma;
		this->nr_cuvinte = m.nr_cuvinte;
	}

	~LMD() //destructor
	{

	}

	LMD& operator=(const LMD& m)
	{
		this->coma = m.coma;
		this->nr_cuvinte = m.nr_cuvinte;
		return *this;
	}

	LMD(string coma) //constructor cu parametri
	{
		this->coma = coma;
		int state = OUT;
		unsigned wc = 0;
		for (int i = 0; i < coma.length(); i++)
		{
			if (coma[i] == ' ' || coma[i] == '=')
				state = OUT;
			else if (state == OUT)
			{
				state = IN;
				++wc;
			}
		}
		this->nr_cuvinte = wc;
	}

	void set_baza(Baza b) //la crearea bazei, o asociam obiectului de tip LMD pentru a gestiona comenzile
	{  
		this->b = b;
	}

	Baza get_baza()
	{
		return this->b;
	}

	bool check_nume(string expr)  //metoda de prelucrare a atributului baza
	{
		bool flag = false;
		for (int j = 0; j < b.nr_tabele; j++)
		{
			if (expr == b.baza[j].nume_tabela)
			{
				flag = true;
			}
		}
		string nume_fisier = expr + ".txt";  ifstream f; f.open(nume_fisier);
		//iau numele tabelei scris in comanda si adaug txt la final
		//pentru a vedea daca am deja un fisier asociat
		//unei tabele cu acest nume
		if (f.is_open()) 
		{											            
			flag = true; //daca am gasit numele fisierului, am deja tabela		
		}
		else {
			cout << "Fisierul nu exista" << endl; //tabela nu mai exista
			flag = false;
		}
		return flag;
	}

	bool structura_corecta(const Tabela& t, string* cuvinte)
	{
		bool flag = false;
		if (nr_cuvinte == (4 + t.nrC))
		{
			flag = true;
		}
		else return false;
		for (int i = 0; i < t.nrC; i++) //pentru fiecare coloana
		{
			if (t.coloane[i].dimensiune < cuvinte[i + 4].length())
			{
				cout << "Dimensiunea valorii introduse depaseste spatiul alocat coloanei." << endl;
				return false;
			}
			if (egalitate(t.coloane[i].tip, "integer"))
			{
				try {
					return stoi(cuvinte[i + 4]);
				}
				catch (...) {
					cout << "Nu ati introdus un intreg." << endl;
				}
				regex ok("[0-9]+");
				if (regex_match(cuvinte[i + 4], ok) == false)
				{
					return false;
				}
			}
			else if (egalitate(t.coloane[i].tip, "text"))
			{
				flag = true;
			}
			else if (egalitate(t.coloane[i].tip, "float"))
			{
				regex ok("[0-9]+(.[0-9]+)?");
				if (regex_match(cuvinte[i + 4], ok) == false)
				{
					return false;
				}
			}
			else {
				cout << "Tabela nu a fost creata corect." << endl;
				return  false;
			}
		}
		return flag;
	}

	int egalitate(string s1, string s2) 
	{  //pentru a verifica daca o comanda primita este una din cele trei, convertesc s1 si s2 in litere mici
		transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
		transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
		if (s1.compare(s2) == 0)
			return 1; //la fel
		return 0; //diferite
	}

	void INSERT_INTO(string* cuvinte)
	{
		string nume_fisier = cuvinte[2] + ".txt";  ifstream f; f.open(nume_fisier); //caut fisierul tabelei
		if (check_nume(cuvinte[2]) == true && f.is_open())
		{
			Tabela t; //creez tabela
			f >> t; //pe care o citesc din fisier
			int nrRanduri = t.nr_randuri;
			f.close();
			if (structura_corecta(t, cuvinte) == true) //verific daca structura este buna
			{
				Rand r1(t.nrC, nullptr); //creez randul pe care vreau sa-l inserez
				Rand* rows = new Rand[1]; //si vectorul de randuri, pentru ca tabela mea are Rand* tabela
				string* vals = new string[t.nrC];  //un rand are valori asociate= nr coloane
				for (int i = 0; i < t.nrC; i++)
				{
					vals[i] = cuvinte[i + 4]; //salvez valorile in tabela
				}
				r1.set_valori(vals, t.nrC); //setez valorile randului
				rows[0] = r1;  //pun randul in vector
				t.nr_randuri++;
				t.setranduri(rows, t.nr_randuri); //pun randul in tabela

				ofstream scriu_text; scriu_text.open(nume_fisier, ios::out | ios::trunc);
				scriu_text << t;
				scriu_text.close();

				ofstream f(t.nume_tabela + ".bin", ios::binary | ios::out | ios::app);
				t.serializare(f); //creez fisierul binar
				f.close();

				ifstream g(t.nume_tabela + ".bin", ios::binary | ios::in | ios::ate);
				g.seekg(-4, ios::end);
				Tabela xx; //creez o tabela dummy
				xx.setnume_tabela(t.nume_tabela);
				xx.deserializare(g);
				cout << "XX este: " << endl << xx << endl;
				g.close();
				delete[] rows;
				delete[] vals;
			}
		}
		else
		{
			cout << "Tabela nu exista!" << endl;
		}
		f.close();
	}

	void SELECT_ALL(string* cuvinte)
	{
		int valoare = 5;
		string nume_fisier = cuvinte[3] + ".txt";  ifstream f; f.open(nume_fisier);
		string nume_f = cuvinte[3] + ".bin"; ifstream g; g.open(nume_f, ios::in | ios::app);
		if (check_nume(cuvinte[3]) == true && f.is_open())
		{
			//f.close();
			string text_file;
			string buffer;
			f >> text_file;
			while (!f.eof())
			{
				//cout << text_file << " ";
				f >> text_file;
				buffer.append(text_file + ' ');
			}
			//cout << endl;
			//cout << buffer;
			cout << endl;
			string* word = new string[100];
			int i = 0, k = 0, vb = 0; 
			while (i < buffer.length())
			{
				if (buffer[i] == ' ')
				{
					i++;
					if (vb == 1) k++;
					vb = 0;
				}
				else {
					word[k] += buffer[i];  vb = 1;
				}
				if (vb == 1)  i++;
			}
			cout << word[2];
			cout << endl;
			string columns;
			columns.append(word[2]+' ');
			for (i = 2; i < word[i].length()-4; i++)
			{
				cout << word[i + 4];
				columns.append(word[i + 4]+' ');
				
			}
			cout << endl;
			cout << columns;
			cout << endl;
			string* cuv = new string[100];
			int j = 0, q = 0, v = 0;
			while (j < columns.length())
			{
				if (columns[j] == ' ')
				{
					j++;
					if (v == 1) q++;
					v = 0;
				}
				else {
					cuv[q] += columns[j];  v = 1;
				}
				if (v == 1)  j++;
			}
			//cout << cuv[0];
			cout << endl;
			/*string* wordo = every_word();
			for (i = 0; i < wordo[i].length(); i++)
			{
				if (wordo[i] == "where")
				{
					cout << wordo[i + 1];
				}
			}*/
			g.seekg(-4, ios::end);
			Tabela xx;
			xx.deserializare(g);
			cout << xx;
			g.close();
		}
		//Trebuie gestionat operatorul de la linia 1071
	}

	/*string* every_word()  //metoda de prelucraee a atributului comanda: imparte string-ul in vector de string-uri (pentru fiecare cuvant)
	{
		string* cuvinte = new string[nr_cuvinte];  //aloc vector de cuvinte regasite in comanda data
		int i = 0, k = 0, vb = 0;  //contorul cuvintelor 
		while (i < this->coma.length())
		{
			if (this->coma[i] == ' ' || this->coma[i] == '=')
			{
				i++;
				if (vb == 1) k++;
				vb = 0;
			}
			else {
				cuvinte[k] += this->coma[i];  vb = 1;
			}
			if (vb == 1)  i++;
		}
		return cuvinte;
	}*/

	void SELECT(string* cuvinte)
	{

	}

	void UPDATE(string* cuvinte)
	{

	}

	void DELETE_FROM(string* cuvinte)
	{
		if (check_nume(cuvinte[2]) == true)
		{

		}
		else
		{
			cout << "Tabela nu exista!" << endl;
		}
	}
	friend ostream& operator<<(ostream&, LMD);
	friend istream& operator>>(istream&, LMD&);
};

ostream& operator<<(ostream& out, LMD m)
{
	out << "comanda: " << m.coma;
	out << "nr cuvinte: " << m.nr_cuvinte;
	return out;
}

istream& operator>>(istream& in, LMD& m)
{
	cout << "comanda = ";
	in >> m.coma;
	cout << "numar cuvinte = ";
	in >> m.nr_cuvinte;
	return in;
}

class Parsing
{
private:
	friend class Baza;
	friend class Tabela;
	friend class Rand;
	friend class LDD;
	friend class LMD;
	string comanda;
	int nr_cuvinte;
	string nume_tabela;
	//Baza b;
	LMD m; LDD d;
public:
	Parsing() //constructor implicit
	{
		comanda = "";
		nr_cuvinte = 0;
	}

	Parsing(string comanda, int nr_cuvinte, string nume_tabela) //constructor cu parametri
	{
		this->comanda = comanda;
		this->nr_cuvinte = nr_cuvinte;
		this->nume_tabela = nume_tabela;
	}

	Parsing(string comanda) //constructor cu parametri
	{
		this->comanda = comanda;
		int state = OUT;
		unsigned wc = 0;
		for (int i = 0; i < comanda.length(); i++)
		{
			if (comanda[i] == ' ' || comanda[i] == '=' || comanda[i] == ',' || comanda[i] == '(' || comanda[i] == ')')
				state = OUT;
			else if (state == OUT)
			{
				state = IN;
				++wc;
			}
		}
		this->nr_cuvinte = wc;
	}

	Parsing(const Parsing& p) //constructor de copiere
	{
		this->comanda = p.comanda;
		this->nr_cuvinte = p.nr_cuvinte;
		this->nume_tabela = p.nume_tabela;
	}

	~Parsing() //destructor
	{

	}

	Parsing& operator=(const Parsing& p)
	{
		this->comanda = p.comanda;
		this->nr_cuvinte = p.nr_cuvinte;
		this->nume_tabela = p.nume_tabela;
		return *this;
	}

	Parsing operator+(int valoare) //operator+
	{
		if (valoare > 0)
		{
			Parsing copie = *this;
			copie.nr_cuvinte += valoare;
			return copie;
		}
		else
		{
			throw 1;
		}
	}

	Parsing operator++() //operator++ 1)
	{
		this->nr_cuvinte++;
		return *this;
	}

	Parsing operator++(int i) //operator++ 2)
	{
		Parsing copie = *this;
		this->nr_cuvinte++;
		return copie;
	}

	explicit operator int() //operator de cast explicit
	{
		return nr_cuvinte;
	}

	bool operator!() //operator!
	{
		return nr_cuvinte > 0;
	}

	bool operator==(Parsing& p) //operator==
	{
		Parsing d = (Parsing&)p;
		if (this->nr_cuvinte == d.nr_cuvinte)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	string getcomanda()
	{
		return comanda;
	}

	void setcomanda(string comanda)
	{
		const char* c = comanda.c_str();
		if (strlen(c) > 0)
		{
			this->comanda = comanda;
		}
		else
			comanda = "";
	}

	int getnr_cuvinte()
	{
		return nr_cuvinte;
	}

	void setnr_cuvinte(int nr_cuvinte)
	{
		if (nr_cuvinte > 0)
		{
			this->nr_cuvinte = nr_cuvinte;
		}
		else
		{
			nr_cuvinte = 0;
		}
	}

	string getnume_tabela()
	{
		return nume_tabela;
	}

	void setnume_tabela(string nume_tabela)
	{
		const char* t = nume_tabela.c_str();
		if (strlen(t) > 0)
		{
			this->nume_tabela = nume_tabela;
		}
		else
			nume_tabela = "";
	}

	void setLDD(LDD d)
	{
		this->d = d;
	}
	void setLMD(LMD m)
	{
		this->m = m;
	}

	int egalitate(string s1, string s2) {  //pentru a verifica daca o comanda primita este una din cele trei convertesc s1 si s2 in litere mici
		transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
		transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
		if (s1.compare(s2) == 0)
			return 1; //la fel
		return 0; //diferite
	}

	bool matchcom() //metoda de prelucrare a atributului comanda: verifica sintaxa
	{  
		regex create1("\\s*create\\s+table\\s+\\w+\\s*\\((\\s*\\w+.?\\w*\\s*(,)){3}\\s*\\w+.?\\w*\\s*\\)\\s*", regex_constants::icase);
		regex drop("\\s*drop\\s+table\\s+\\w+\\s*", regex_constants::icase);
		regex display("\\s*display\\s+table\\s+\\w+\\s*", regex_constants::icase);
		regex create2("\\s*create\\s+table\\s+\\w+\\s*\\(\\s*((\\s*(\\(){1}\\s*\\w+.?\\w*\\s*(?:,\\s*\\w+.?\\w*\\s*){3})\\s*\\)\\s*,\\s*){1,19}((\\s*(\\(){1}\\s*\\w+.?\\w*\\s*(?:,\\s*\\w+.?\\w*\\s*){3})\\s*\\)\\s*)\\)\\s*", regex_constants::icase);
		regex insert("\\s*(insert)(\\s+)(into)(\\s+)(\\w+)(\\s+)(values)\\s*((\\s*(\\()\\s*(\\w+.?\\w*\)\\s*(?:,\\s*(\\w+.?\\w*)\\s*){0,19})\\s*\\)\\s*)", regex_constants::icase);
		regex select("\\s*select\\s*(((\\s*\\(\\s*\\w+\\s*(?:,\\s*\\w+\\s*){0,19})\\s*\\)\\s*)|all)\\s*from\\s*\\w+\\s*(where\\s*\\w+\\s*=\\s*\\s*(\\w+.?\\w*)\\s*)?", regex_constants::icase);
		regex update("\\s*update\\s+\\w+\\s+set\\s+\\w+\\s*=\\s*(\\w+.?\\w*)\\s+where\\s+\\w+\\s*=\\s*(\\w+.?\\w*)\\s*", regex_constants::icase);
		regex delete_from("\\s*delete\\s+from\\s+\\w+\\s+where\\s+\\w+\\s*=\\s*(\\w+.?\\w*)\\s*", regex_constants::icase);
		regex create_indx("\\s*create\\s+index\\s+(\\s*if\\s+not\\s+exists\\s+)?\\w+\\s+on\\s+\\w+\\s*\\(\\s*\\w+\\s*\\)\\s*", regex_constants::icase);
		regex drop_indx("\\s*drop\\s+index\\s+\\w+\\s*", regex_constants::icase);
		bool match = false;  string* cuvinte = fiecare_cuvant();
		if (regex_match(comanda, create1))
		{
			match = true; d.CREATE_TABLE(cuvinte, 1);
		}
		if (regex_match(comanda, create2))
		{
			match = true; d.CREATE_TABLE(cuvinte, 2);
		}
		if (regex_match(comanda, drop))
		{
			match = true; d.DROP_TABLE(cuvinte);
		}
		if (regex_match(comanda, display))
		{
			match = true; d.DISPLAY_TABLE(cuvinte);
		}
		if (regex_match(comanda, insert))
		{
			match = true;
			m.INSERT_INTO(cuvinte);
		}
		if (regex_match(comanda, select))
		{
			match = true;
			m.SELECT_ALL(cuvinte);
		}
		if (regex_match(comanda, update))
		{
			match = true;
			m.UPDATE(cuvinte);
		}
		if (regex_match(comanda, delete_from))
		{
			match = true;
		}
		if (regex_match(comanda, create_indx))
		{
			match = true;
		}
		if (regex_match(comanda, drop_indx))
		{
			match = true;
		}
		cout << (match ? "Sintaxa corecta. " : "Eroare de sintaxa!") << endl;
		return match;
	}

	string* fiecare_cuvant()  //metoda de prelucrare a atributului comanda: imparte string-ul in vector de string-uri pentru a putea delimita cuvintele din comanda primita
	{
		string* cuvinte = new string[nr_cuvinte];
		int i = 0, k = 0, vb = 0;
		while (i < this->comanda.length())
		{
			if (this->comanda[i] == ' ' || this->comanda[i] == '=' || this->comanda[i] == ',' || this->comanda[i] == '(' || this->comanda[i] == ')')
			{
				i++;
				if (vb == 1) k++;
				vb = 0;
			}
			else {
				cuvinte[k] += this->comanda[i];  vb = 1;
			}
			if (vb == 1)  i++;
		}
		return cuvinte;
	}


	void afisare_parametri(int k, int p, string* cuvinte)  //metoda de afisare a atributelor
	{
		for (int i = 0; i < p - 1; i++) {
			cout << "Nume coloana " << i + 1 << ": " << cuvinte[k] << endl;
			cout << "Tip coloana " << i + 1 << ": " << cuvinte[k + 1] << endl;
			cout << "Dimensiune coloana " << i + 1 << ": " << cuvinte[k + 2] << endl;
			cout << "Valoare implicita coloana " << i + 1 << ": " << cuvinte[k + 3] << endl;
		}
	}
	friend ostream& operator<<(ostream&, Parsing);
	friend istream& operator>>(istream&, Parsing&);
};


ostream& operator<<(ostream& out, Parsing p)
{
	out << "comanda: " << p.comanda << endl;
	out << "numar cuvinte: " << p.nr_cuvinte << endl;
	out << "nume tabela: " << p.nume_tabela << endl;
	return out;
}

istream& operator>>(istream& in, Parsing& p)
{
	cout << "comanda = ";
	in >> p.comanda;
	cout << "numar cuvinte = ";
	in >> p.nr_cuvinte;
	cout << "nume tabela = ";
	in >> p.nume_tabela;
	return in;
}