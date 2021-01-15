#pragma once
#include "clase.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include<list>
#include <algorithm>
#include <regex>
#include <fstream>
#include<new>
#pragma warning(disable : 4996)
#define OUT 0  
#define IN 1  
using namespace std;

class exceptii: public exception
{
	string mesaj_exceptie;
public:
	exceptii(string mesaj)
	{
		this->mesaj_exceptie = mesaj;
	}
	void set_mesaj_exceptie(string mesaj)
	{
		this->mesaj_exceptie = mesaj;
	}
	string get_mesaj_exceptie()
	{
		return mesaj_exceptie;
	}
};

class FisierBinar {  //o clasa abstracta (fără atribute) ce tcontine minim 2 metode virtuale pure
public:
	virtual void serializare(ofstream& fisier, int k)=0; //scriereInFisier
	virtual void deserializare(ifstream& fisier)=0; //citireDinFisier
	virtual void citireCSV( ifstream& csv) = 0; 
};

class Coloana
{
private:
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

	void afisare_atribute()  //metoda de afisare a atributelor
	{
		cout << "Nume coloana: " << nume_coloana << endl;
		cout << "Tip: " << tip << endl;
		cout << "Dimensiune: " << dimensiune << endl;
		if (valoare_implicita != nullptr)
		{
			cout << "Valoare implicita: ";
			cout << valoare_implicita;
		}
		else cout << "Nu avem valoare implicita!";
			cout << endl;
	}

	void nume_majuscule() //metoda de prelucrare a atributului nume_coloana (transforma in majuscule si il afiseaza)
	{
		cout << "Nume coloana initial: " << nume_coloana << endl;
		transform(nume_coloana.begin(), nume_coloana.end(), nume_coloana.begin(), ::toupper);
		cout << "Nume coloana cu majuscule: " << nume_coloana << endl;
	}
	void nume_litereMici() //metoda de prelucrare a atributului nume_coloana (transforma in litere mici si il afiseaza)
	{
		cout << "Nume coloana initial: " << nume_coloana << endl;
		transform(nume_coloana.begin(), nume_coloana.end(), nume_coloana.begin(), ::tolower);
		cout << "Nume coloana cu litere mici: " << nume_coloana << endl;
	}

	friend ostream& operator<<(ostream&, const Coloana&);
	friend istream& operator>>(istream&,  Coloana&);
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
		if (n > 0&&valori!=nullptr)
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

	~Rand()
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
			string* copie= new string[nr_coloane];
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
};

ostream& operator<<(ostream& out, Rand r)
{
	if(r.valori!=nullptr)
	{
		for (int i = 0; i < r.nr_coloane; i++)
		{
			out << r.valori[i] << " ";
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
	if (r.valori != nullptr)
	{
		delete[] r.valori;
	}
	if (r.nr_coloane > 0)
	{
		r.valori = new string[r.nr_coloane];
		for (int i = 0; i < r.nr_coloane; i++)
		{
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

class Tabela: public FisierBinar
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
	//Index index; 
public:

	Tabela()  //constructor implicit
	{
		nume_tabela = "";
		nr_randuri = 0;
		tabela = nullptr;
		coloane = nullptr;
		nrC = 0;
		nrTabele++;
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
		nrTabele++;
	}

	Tabela(Coloana* coloane, int nrC, string nume_tabela)  //constructor cu parametri
	{
		nrTabele++;
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
	~Tabela()
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
		nrTabele--;
	}

	Tabela& operator=(const Tabela& t)
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
		else {
			this->tabela = nullptr; this-> nr_randuri =0;
		}
	}
/*	void setranduri(list<Rand>vec) 
	{
		if (vec.size()>0)
		{
			if (this->tabela != nullptr)
			{
				delete[] this->tabela;
			}
			this->nr_randuri = vec.size();
			this->tabela = new Rand[nr_randuri];
			list<Rand>::iterator it;   int i = 0;
			for (it = vec.begin(); it != vec.end(); it++)
			{
				this->tabela[i++] = *it;
			}
		}
		else {
			this->tabela = nullptr; this->nr_randuri = 0;
		}
	}*/

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
				cout << endl<<"Coloana " << i + 1 << ": " << endl;
				coloane[i].afisare_atribute();
			}
			cout << endl;
		}
	}

	void afisSEL_Where(string* cuvinte, vector<int> v, int nrc, int rand)
	{
		for (int i = 0; i < nrc; i++) 
			cout << cuvinte[1 + i] << " ";
		if(nrc>0) cout << endl;
		for (int i = 0; i < v.size(); i++)
			cout << tabela[rand].valori[v[i]] << " ";
		cout << endl;
	}

	void afisareSEL_Where(string* cuvinte, list<int> l, int nrc, int rand)
	{
		for (int i = 0; i < nrc; i++) 
			cout << cuvinte[1 + i] << " ";
		if (nrc > 0) cout << endl;
		for (list<int>::iterator it = l.begin(); it != l.end(); it++)
			cout << tabela[rand].valori[*it];
		cout << endl;
	}

	void afisare_select()
	{
		cout << "Nume tabela: ";
		cout << nume_tabela << endl;
		if (coloane != nullptr)
			for (int j = 0; j < nrC; j++)
				cout << coloane[j].getnume_coloana() << " ";
			cout << endl;
			for (int i = 0; i < nr_randuri; i++)
				cout << tabela[i];
	}

	void afisare_update()
	{
		cout << "Nume tabela: ";
		cout << nume_tabela << endl;
		if (coloane != nullptr)
			for (int j = 0; j < nrC; j++)
			cout << coloane[j].getnume_coloana() << " ";
		cout << endl;
	}

	void serializare(ofstream& f, int k) override
	{
		f.write((char*)&nr_randuri, sizeof(nr_randuri));		
		
			f.write((char*)&tabela[k].nr_coloane, sizeof(tabela[k].nr_coloane));	
			for (int j = 0; j < tabela[k].nr_coloane; j++)
			{
				int length = tabela[k].valori[j].length();
				f.write((char*)&length, sizeof(length));			//scrie marimea unei valori 2 (1,0) si valoarea 1,marimea 4 (i,0,n, 0) valoarea ion
				length++;
				f.write(tabela[k].valori[j].c_str(), length);
			}
		f.write((char*)&nrC, sizeof(nrC));   //scrie nrc adica 2
		f.write((char*)&nr_randuri, sizeof(nr_randuri));
	}

	 void deserializare(ifstream& f) override
	 {
		f.read((char*)&nr_randuri, sizeof(nr_randuri));
		f.seekg(0, ios::beg);
		if(tabela!=nullptr)
		delete[] tabela;
		tabela = new Rand[nr_randuri];
		for (int i = 0; i < nr_randuri; i++)
		{
			int x = 0;
			f.read((char*)&x, sizeof(x));
			f.read((char*)&tabela[i].nr_coloane, sizeof(tabela[i].nr_coloane));
			if(tabela[i].valori!=nullptr)
			delete[] tabela[i].valori;
			tabela[i].valori = new string[tabela[i].nr_coloane];
			for (int j = 0; j < tabela[i].nr_coloane; j++)
			{
				int length = 0;
				f.read((char*)&length, sizeof(length));
				length++;
				char* aux = new char[length];
				f.read(aux, length);
				this->tabela[i].valori[j] = aux;
				if(aux!=nullptr)
				delete[] aux;
			}   //nr rand nr col lungimeval val nr rand
			f.read((char*)&nrC, sizeof(nrC));
			f.read((char*)&x, sizeof(x));
		}
		f.seekg(0, ios::end);
		if (!f.is_open()) cout << "Fisierul binar nu s-a deschis!" << endl;
	 }
	
	 string* fiecare_cuvant(string linie)  //metoda de prelucraee a atributului comanda: imparte string-ul in vector de string-uri (pentru fiecare cuvant)
	 {
		 string* cuvinte = new string[nrC];  //aloc vector de cuvinte regasite in comanda data
		 int i = 0, k = 0, vb = 0;  //contorul cuvintelor 
		 while (i < linie.length())
		 {
			 if (linie[i] == ',')
			 {
				 i++;
				 if (vb == 1) k++;
				 vb = 0;
			 }
			 else {
				 cuvinte[k] += linie[i];  vb = 1;
			 }
			 if (vb == 1)  i++;
		 }
		 return cuvinte;
	 }


	 int egalitate(string s1, string s2) {  //pentru a verifica daca o comanda primita este una din cele trei
		 transform(s1.begin(), s1.end(), s1.begin(), ::tolower);   //convertesc s1 si s2 in litere mici
		 transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
		 if (s1.compare(s2) == 0)
			 return 1; //la fel
		 return 0; //diferite
	 }
	 int nrVirgule(string exp)  //metoda de prelucrare a sintaxei
	 {
		 int v = 0;
		 for (int j = 0; j < exp.length(); j++)//parcurg expresia
				 if (exp[j] == ',')  v++; 
		 return v;
	 }
	 bool structura_corecta(string* cuvinte)
	 {
		 bool flag = false;
		 for (int i = 0; i < nrC; i++) //pentru fiecare coloana, 
		 {
			 if (coloane[i].getdimensiune()< cuvinte[i].length())
			 {
				 cout << "Dimensiunea valorii introduse depaseste spatiul alocat coloanei." << endl;
				 return false;
			 }
			 if (egalitate(coloane[i].gettip(), "integer"))
			 {
				 regex ok("[0-9]+");
				 if (regex_match(cuvinte[i], ok) == false)
				 {
					 return false;
				 }
			 }
			 else if (egalitate(coloane[i].gettip(), "text"))
			 {
				 flag = true;
			 }
			 else if (egalitate(coloane[i].gettip(), "float"))
			 {
				 regex ok("[0-9]+(.[0-9]+)?");
				 if (regex_match(cuvinte[i], ok) == false)
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
	 void citireCSV(ifstream& csv) override //obiectul care va apela metoda trebuie citit in prealabil din fisierul txt asociat, in care se gaseste structura tabelei
	 {
		 int randuriInitiale = this->nr_randuri;
		 int count = 0;
		 string le;
		 size_t n;   bool vb = true;
		 while (getline(csv, le)) 
		 { 
			 int v = nrVirgule(le);
			 if (v != nrC - 1) {
				 cout << "Numarul cuvintelor de pe linia " << count + 1 << " este diferit de " << nrC << "!" << endl;
				 vb = false; count++;
			 }
			 else count++; 
		 }
		 if (vb == true) {
			 Rand* tab = new Rand[count];
			 string* randuri = new string[count];
			 le = "";
			 csv.clear();
			 csv.seekg(0);
			 for (int i = 0; i < count; i++)
			 {
				 getline(csv, le);
				 randuri[i] = le;
			 }
			 string* fiecare_linie;  Rand* copie = nullptr;
			 ifstream cit(nume_tabela + ".bin", ios::binary | ios::in | ios::app);
			 cit.seekg(-4, ios::end);
			 this->deserializare(cit);
			 cit.close();
			 if (this->tabela != nullptr && nr_randuri > 0)
			 {
				 copie = new Rand[nr_randuri + count];
				 for (int i = 0; i < nr_randuri; i++)
				 {
					 copie[i] = tabela[i];
					 copie[i].set_valori(tabela[i].valori, tabela[i].nr_coloane);
				 }
			 }
			 else {
				 copie = new Rand[count];
				 copie->set_valori(nullptr, 0);
			 }
			 for (int i = 0; i < count; i++)
			 {
				 fiecare_linie = fiecare_cuvant(randuri[i]);
				 tab[i].setnrcoloane(nrC);
				 tab[i].set_valori(fiecare_linie, nrC);
				 copie[nr_randuri] = tab[i];
				 this->nr_randuri++;
			 }
			 bool ok = true;
			 for (int i = 0; i < count; i++)
			 {
				 if (structura_corecta(copie[i].valori) == false) {
					 cout << "Randul " << i + 1 << " nu corespunde structurii tabelei!" << endl;
					 ok = false;
				 }
			 }
			 if (ok == true)
			 {
				 this->setranduri(copie, nr_randuri);
				 ofstream an(nume_tabela + ".bin", ios::binary | ios::out | ios::app);
				 for(int i=randuriInitiale;i<nr_randuri;i++)
				 this->serializare(an,i); //ii fac fisierul binar
				 an.close();
				 ofstream scriu_text; scriu_text.open(nume_tabela + ".txt", ios::out | ios::trunc);
				 scriu_text << *this; //scriu t aici, unde va avea nr randuri +1
				 scriu_text.close();
				 ifstream g; g.open(nume_tabela + ".txt", ios::in);
				 g >> *this;
				 g.close();
				 ifstream h(nume_tabela + ".bin", ios::binary | ios::in | ios::app);
				 h.seekg(-4, ios::end);
				 this->deserializare(h);
				 cout << "this e " << endl << *this << endl;
				 h.close();
			 }
			 else this->nr_randuri = randuriInitiale;
		 }
		 else cout << "Nu s-au adaugat cele " << count << " randuri din cauza incompatibilitatii datelor." << endl;
	 }

	friend ostream& operator<<(ostream&, const Tabela&);
	friend istream& operator>>(istream&, Tabela&);
	friend ofstream& operator<<(ofstream& out, const Tabela& t);
	friend ifstream& operator>>(ifstream&, Tabela&);

};
int Tabela::nrTabele = 0;

ostream& operator<<(ostream& out, const Tabela& t)
{
	out << "Nume tabela: ";
	out << t.nume_tabela << endl;
	if (t.coloane != nullptr)
	{
		out << "Coloane: " << endl;
		for (int i = 0; i < t.nrC; i++)
		{
			out << t.coloane[i];
		}
		out << endl;
	}
	out << "Numar randuri: ";
	out << t.nr_randuri << endl;
	if (t.tabela != nullptr)
	{
		out << "Randuri: " << endl;
		for (int i = 0; i < t.nr_randuri; i++)
		{
			out << t.tabela[i];
		}
		out << endl;
	}
	out << "Numar tabele: ";
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
				f << t.coloane[i];
			}
			f << endl;
		}
		cout <<endl<< "Structura tabelei a fost salvata/actualizata in fisierul "<<t.nume_tabela<<".txt." << endl;
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
			t.tabela = new Rand;
			t.tabela->setnrcoloane(t.nrC);
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
	const char* nume_db="Baza mea";
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
		return this->nume_db; //nu e nevoie de verificare, fiind mereu "Baza mea"
	}						  //si nici nevoie sa returnam o copie, pentru ca nu e modificabil

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

	void nume_majuscule() //metoda de prelucrare a atributului nume_db (transforma in majuscule si il afiseaza)
	{
		cout << "Nume baza initial: " << nume_db << endl;
		string name = nume_db;
		transform(name.begin(), name.end(), name.begin(), ::toupper);
		cout << "Nume baza cu majuscule: " << name << endl;
	}
	void nume_litereMici() //metoda de prelucrare a atributului nume_db (transforma in litere mici si il afiseaza)
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

class LDD; class LMD;


class Parsing
{
protected:
	string comanda;
	int nr_cuvinte;
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
	}

	~Parsing() //destructor
	{

	}

	Parsing& operator=(const Parsing& p)
	{
		this->comanda = p.comanda;
		this->nr_cuvinte = p.nr_cuvinte;
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
	bool delimitariCorecte(string exp, int& p, int& v)  //metoda de prelucrare a sintaxei
	{
		bool flag = true;
		int nr = 0;

		for (int j = 0; j < exp.length(); j++) { //parcurg expresia
			if (exp[j] == '(') {
				nr++; p++; // e o paranteza deschisa
			}
			else {
				if (exp[j] == ')')
					nr--;   // e o paranteza inchisa
				if (exp[j] == ',') {
					if (nr == 0) { cout << "Virgula incorecta!" << endl; flag = false; break; }
					else v++;
				}
			}
			if (nr < 0) { flag = false; break; }
		}
		if (nr < 0) {   // Sunt mai multe paranteze inchise
			flag = false;
			cout << "Parantezele nu corespund." << endl;
		}
		for (int j = 0; j < exp.length() - 1; j++) {
			if (exp[j] == ',' && exp[j + 1] == ',') //virgule consecutive
			{
				cout << "Virgulele sunt consecutive, sintaxa gresita!" << endl;
				flag = false;
				break;
			}
		}
		return flag;
	}
	int getnr_cuvinte()
	{
		return nr_cuvinte;
	}

	virtual bool matchcom() {  //metoda de prelucrare a atributului comanda: verifica sintaxa
		regex exx("\\s*exit\\s*", regex_constants::icase);
		bool match = false;  string* cuvinte = fiecare_cuvant();
		if (regex_match(comanda, exx))
		{
			return true;
		}
		return match;
	}

	virtual string nume_comanda_txt(string c)
	{
		string nume; int k = 0;
		for (int i = 1; i < 100; i++)
		{
			string x = to_string(i);
			nume = c + x;
			if (check_nume(nume) == true)
			{
				x = to_string(i + 1);
				nume = c + x;
			}
			else return nume;
		}
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

	bool check_nume(string expr)
	{
		bool flag = false;
		string nume_fisier = expr + ".txt";  ifstream f; f.open(nume_fisier);
		if (f.is_open()) {
			flag = true;
			f.close();
		}
		else	flag = false;
		return flag;
	}
	
	int egalitate(string s1, string s2) {  //pentru a verifica daca o comanda primita este una din cele trei
		transform(s1.begin(), s1.end(), s1.begin(), ::tolower);   //convertesc s1 si s2 in litere mici
		transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
		if (s1.compare(s2) == 0)
			return 1; //la fel
		return 0; //diferite
	}

	string* fiecare_cuvant()  //metoda de prelucraee a atributului comanda: imparte string-ul in vector de string-uri (pentru fiecare cuvant)
	{
		string* cuvinte = new string[nr_cuvinte];  //aloc vector de cuvinte regasite in comanda data
		int i = 0, k = 0, vb = 0;  //contorul cuvintelor 
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

	friend ostream& operator<<(ostream&, Parsing);
	friend istream& operator>>(istream&, Parsing&);
};

class LDD: public Parsing
{
	friend class Coloana;
	friend class Rand;
	friend class Tabela;
		
public:

	LDD() //constructor implicit
	{
		comanda = "";
		nr_cuvinte = 0;
	}

	LDD(string comanda, int nr_cuvinte) //constructor cu parametri
	{
		this->comanda = comanda;
		this->nr_cuvinte = nr_cuvinte;
	}

	LDD(string comanda) //constructor cu parametri
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

	LDD(const LDD& l) //constructor de copiere
	{
		this->comanda = l.comanda;
		this->nr_cuvinte = l.nr_cuvinte;
	}

	~LDD() //destructor
	{

	}

	LDD& operator=(const LDD& l)
	{
		this->comanda = l.comanda;
		this->nr_cuvinte = l.nr_cuvinte;
		return *this;
	}

	bool matchcom() override
	{  //metoda de prelucrare a atributului comanda: verifica sintaxa
		regex create1("\\s*create\\s+table\\s+\\w+\\s*(\\s+if\\s+not\\s+exists\\s*)?\\(((\\s*\\w+.?\\w*\\s*(,)){3}\\s*\\w+.?\\w*\\s*)\\s*", regex_constants::icase);
		regex create1fara("\\s*create\\s+table\\s+\\w+\\s*\\(((\\s*\\w+.?\\w*\\s*(,)){3}\\s*\\w+.?\\w*\\s*)\\s*", regex_constants::icase);
		regex drop("\\s*drop\\s+table\\s+\\w+\\s*", regex_constants::icase);
		regex display("\\s*display\\s+table\\s+\\w+\\s*", regex_constants::icase);
		regex create2("\\s*create\\s+table\\s+\\w+\\s*(\\s+if\\s+not\\s+exists\\s*)?\\(\\s*((\\s*(\\(){1}\\s*\\w+.?\\w*\\s*(?:,\\s*\\w+.?\\w*\\s*){3})\\s*\\)\\s*,\\s*){1,19}((\\s*(\\(){1}\\s*\\w+.?\\w*\\s*(?:,\\s*\\w+.?\\w*\\s*){3})\\s*\\)\\s*)\\)\\s*", regex_constants::icase);
		regex create2fara("\\s*create\\s+table\\s+\\w+\\s*\\(\\s*((\\s*(\\(){1}\\s*\\w+.?\\w*\\s*(?:,\\s*\\w+.?\\w*\\s*){3})\\s*\\)\\s*,\\s*){1,19}((\\s*(\\(){1}\\s*\\w+.?\\w*\\s*(?:,\\s*\\w+.?\\w*\\s*){3})\\s*\\)\\s*)\\)\\s*", regex_constants::icase);
		regex create_indx("\\s*create\\s+index\\s+(\\s*if\\s+not\\s+exists\\s+)?\\w+\\s+on\\s+\\w+\\s*\\(\\s*\\w+\\s*\\)\\s*", regex_constants::icase);
		regex drop_indx("\\s*drop\\s+index\\s+\\w+\\s*", regex_constants::icase);
		regex exx("\\s*exit\\s*", regex_constants::icase);
		bool match = false;  string* cuvinte = fiecare_cuvant();  
		if (regex_match(comanda, create1fara))
		{
			CREATE_TABLE(cuvinte, 1, 0); return true;
		}
		if (regex_match(comanda, create2fara))
		{
			CREATE_TABLE(cuvinte, 2, 0); return true;
		}
		if (regex_match(comanda, create1))
		{
			CREATE_TABLE(cuvinte, 1, 3); return true;
		}
		if (regex_match(comanda, create2))
		{
			CREATE_TABLE(cuvinte, 2, 3); return true;
		}
		if (regex_match(comanda, drop))
		{
			DROP_TABLE(cuvinte); return true;
		}
		if (regex_match(comanda, display))
		{
			DISPLAY_TABLE(cuvinte); return true;
		}
		if (regex_match(comanda, create_indx))
		{
			CREATE_INDEX(cuvinte);
			return true;
		}
		if (regex_match(comanda, drop_indx))
		{
			cout << "Sintaxa corecta, urmeaza implementarea!" << endl;
			return true;
		}
		if (regex_match(comanda, exx))
		{
			return true;
		}
		return match;
	}

	string nume_comanda_txt(string c="DISPLAY_") override
	{
		string nume; int k = 0;
		for (int i = 1; i < 100; i++)
		{
			string x = to_string(i);
			nume = c + x;
			if (check_nume(nume) == true)
			{
				x = to_string(i + 1);
				nume = c + x;
			}
			else return nume;
		}
	}

	bool structura_tabela(string* cuvinte, int c, int ine)
	{
		bool flag = false;
		for (int i = 0; i < c; i++)
		{
			if (cuvinte[i * 4 + 4+ine] == "integer" || cuvinte[i * 4 + 4+ine] == "float" || cuvinte[i * 4 + 4+ine] == "text")
			{
				flag = true;
			}
			else {
				cout << "Dati un tip de data valid (text/integer/float)." << endl;
				flag= false;
			}
			regex ok("[1-9][0-9]*");
			regex text("necunoscut", regex_constants::icase);
			if (regex_match(cuvinte[i * 4 + 5+ine], ok) == false)
			{
				cout << "Dimensiunea coloanei "<<i+1<<" trebuie sa fie un numar natural!" << endl;
				flag= false;
			}
			else {
				if ((stoi(cuvinte[i * 4 + 5+ine]) > 0 && (cuvinte[i * 4 + 4+ine] == "integer" || cuvinte[i * 4 + 4+ine] == "float"))||(stoi(cuvinte[i * 4 + 5+ine]) > 10 && cuvinte[i * 4 + 4+ine] == "text"))
				{
					flag = true;
				}
				else {
					cout << "Dimensiunea data a coloanei " << i + 1 << " nu este suficient de mare!" << endl;
					flag= false;
				}
			}
			if (cuvinte[i * 4 + 4+ine] == "integer" || cuvinte[i * 4 + 4+ine] == "float")
			{
				if (stoi(cuvinte[i * 4 + 6+ine]) != 0) 
				{ 
					cout << "Valoarea implicita acceptata pentru integer si float este 0." << endl;
					flag= false; 
				}
				else flag = true;
			}
			else if (cuvinte[i * 4 + 4+ine] == "text") {
				if (regex_match(cuvinte[i * 4 + 6+ine], text) == false)
				{
					cout << "Valoarea implicita acceptata pentru text este \"necunoscut\"." << endl;
					flag= false;
				}
				else flag = true;
			}
		}
		return flag;
	}

	void CREATE_TABLE(string* cuvinte, int k, int ine) //k e 1 sau 2: 1 daca e un create cu o singura coloana per tabel
	{												  // 2 daca are 2 sau mai multe coloane, pentru ca abordarea e putin diferita
		if (check_nume(cuvinte[2])==false)  
		{
			Coloana* col = nullptr; int nr = 0;
			if (k == 1)
			{							//tabelelor ar trebui sa fie separata de cea a datelor) (adica cand facem create nu ar trebui sa initializam randuri, alea aparand cand facem insert)
				Coloana c(cuvinte[3+ine], cuvinte[4+ine], stoi(cuvinte[5+ine]), cuvinte[6+ine]);  //creez o coloana ; stoi transforma string-ul din comanda si il face int, pt ca dimensiunea trebuie sa fie numar
				col = new Coloana[1]; //creez vector de coloane, randurile
				nr = 1;
				col[0] = c;
			}
			else if (k == 2)
			{
				int p = 0, v = 0, m = 3; //aici am paranteze si virgule initializate cu 0, sa mi le numere functia urmatoare
				delimitariCorecte(comanda, p, v);   //m e folosit pentru a lua din 4 in 4 cuvintele, pentru fiecare coloana, incepand de la cuvant[3], adica al 4-lea din create table
				col = new Coloana[p - 1];  //daca am p perechi paranteze, am p-1 coloane in comanda, o pereche de paranteze fiind cea ce le cuprinde pe toate
				nr = p - 1;
				for (int i = 0; i < p - 1; i++)
				{
					Coloana c(cuvinte[m+ine], cuvinte[m + 1+ine], stoi(cuvinte[m + 2+ine]), cuvinte[m + 3+ine]);
					m += 4;   //ce am facut si mai sus, doar ca aici am  mai multe coloane, nu una
					col[i] = c;
				}
			}
			else throw("Nu s-a recunoscut comanda!");
			if (structura_tabela(cuvinte, nr,ine) == true)
			{
				Tabela x(col, nr, cuvinte[2]);  //creez tabela, cu vector randuri, nr randuri care cred ca ar trebui sa fie tot p-1? asa ar avea sens, acum vad sii numele e in cuvinte[2]
				Tabela* tabele = new Tabela[1]; //am vectori de tabele
				tabele[0] = x; //salvez tabela aici
				Baza b(1, tabele);  //creez baza
				b.setbaza(tabele, 1);
				string nume_fisier = cuvinte[2] + ".txt";  ofstream f; f.open(nume_fisier); //filehandler fisier(nume,tip)
				f << x;  //il scriu
				f.close(); //NEVER FORGET TO CLOSE IT //fisier.inchi
				delete[] tabele;
				delete[]col;
			}
			else {
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
		if (f.is_open())  //verific in vectorul bazei, sau daca gasesc fisierul
		{
			f.close(); //daca nu-l inchid aici, n am permisiune sa l sterg ulterior
			if (remove(nume_fisier.c_str()) != 0) //sterg
				perror("Eroare stergere fisier.");
			else
				puts("Stergere structura tabela efectuata.");
			nume_fisier = cuvinte[2] + ".bin";  ifstream f; f.open(nume_fisier);
			if (f.is_open())
			{
				f.close(); //daca nu-l inchid aici, n am permisiune sa l sterg ulterior
				if (remove(nume_fisier.c_str()) != 0) //sterg
					perror("Eroare stergere fisier binar.");
				else
					puts("Stergere continut tabela efectuata.");
			}
		}
		else {
			perror("Tabela nu exista.");
		}
		f.close();
	}
	void DISPLAY_TABLE(string* cuvinte)
	{
		string nume_fisier = cuvinte[2] + ".txt";  ifstream f; f.open(nume_fisier);
		if (f.is_open())
		{
			Tabela t;
			f >> t;
			string nume = nume_comanda_txt("DISPLAY_");
			nume += ".txt";
			const char* aux = nume.c_str();
			ofstream out(nume);
			streambuf* coutbuf = cout.rdbuf(); //salvare buffer
			cout.rdbuf(out.rdbuf()); //redirectionare cout catre fisier
			t.afisare_tabela();
			cout.rdbuf(coutbuf); //resetare catre standard output 
			cout << "Afisare tabela:" << endl<<endl; //afisam si la consola
			t.afisare_tabela();
			cout << "Continutul anterior a fost salvat in fisierul " << nume << endl;
		}
		else cout << "Tabela nu exista!" << endl;
		f.close();
	}
			
	void CREATE_INDEX(string* cuvinte)
	{
		/* CREATE INDEX [IF NOT EXISTS] index_name ON table_name (column_name)
		•	Indexul trebuie să permită căutarea rapidă a datelor ca răspuns la 
		comenzile SELECT cu clauza WHERE unde condiția este indexul
•	Prin utilizarea indexului, se va defini un fișier binar asociat acestuia 
în care este stocată valoarea coloanei index și poziția înregistrării
aferente (offset-ul) în fișierul binar asociat tabelei respective
•	Pentru comenzile SELECT cu clauza WHERE pe coloana index căutarea
se va face în index și apoi sunt extrase înregistrările aferente 
(fără index, căutarea înregistrărilor se va face secvențial în fișierul binar)
*/			//Index index(cuvinte[2], cuvinte[4], cuvinte[5]);
			Tabela x;
			string nume_fisier = cuvinte[2] + ".txt";  ofstream f; f.open(nume_fisier); //filehandler fisier(nume,tip)
			f << x;  //il scriu
			f.close();
			//daca tabela nu are date, atunci merge cheie primara

	}
	void DROP_INDEX(string* cuvinte)
	{

	}

};

class Index
{
	set<string> s;
	string numeIndex;
	string numeTabela;
	string numeColoana;
public:
	Index() {	}
	Index(string numeIndex, string numeTabela, string numeColoana)
	{
		this->s = s;
		this->numeIndex = numeIndex;
		this->numeTabela = numeTabela;
		this->numeColoana = numeColoana;
	}
	void setSet(set<string> s)
	{
		this->s = s;
	}
};

class LMD: public Parsing
{
	friend class Coloana;
	friend class Rand;
	friend class Tabela;
public:

	LMD() //constructor implicit
	{
		comanda = "";
		nr_cuvinte = 0;
	}

	LMD(string co, int nr) //constructor cu parametri /*, string nume_tabela*/
	{
		this->comanda = co;
		this->nr_cuvinte = nr;
	}

	LMD(const LMD& m) //constructor de copiere
	{
		this->comanda = m.comanda;
		this->nr_cuvinte = m.nr_cuvinte;
	}
	LMD(string comanda) //constructor cu parametri
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

	~LMD() //destructor
	{

	}

	LMD& operator=(const LMD& m)
	{
		this->comanda = m.comanda;
		this->nr_cuvinte = m.nr_cuvinte;
		return *this;
	}

	bool matchcom() override
	{  //metoda de prelucrare a atributului comanda: verifica sintaxa
		regex insert("\\s*(insert)(\\s+)(into)(\\s+)(\\w+)(\\s+)(values)\\s*((\\s*(\\()\\s*(\\w+.?\\w*\)\\s*(?:,\\s*(\\w+.?\\w*)\\s*){0,19})\\s*\\)\\s*)", regex_constants::icase);
		regex selectwhere("\\s*select\\s*(((\\s*\\(\\s*[a-z_]+\\s*(?:,\\s*\\w+\\s*){0,19})\s*\\)\\s*))\\s*from\\s+\\w+\\s*(where\\s*[a-z_]+\\s*=\\s*(([a-z_]+)|([0-9](.[0-9])?)\\w*)\\s*)?", regex_constants::icase);
		regex selectall("\\s*select\\s+all\\s+from\\s+\\w+\\s*", regex_constants::icase);
		regex select("\\s*select\\s*(((\\s*\\(\\s*[a-z_]+\\s*(?:,\\s*\\w+\\s*){0,19})\\s*\\)\\s*))\\s*from\\s+\\w+\\s*", regex_constants::icase);
		regex selectallwhere("\\s*select\\s+all\\s+from\\s+\\w+\\s*(where\\s*[a-z_]+\\s*=\\s*(([a-z_]+)|([0-9](.[0-9])?)\\w*)\\s*)?", regex_constants::icase);
		regex update("\\s*update\\s+\\w+\\s+set\\s+\\w+\\s*=\\s*((\\w+\\s*)|([0-9]+(.[0-9]+)?))\\s+where\\s+\\w+\\s*=\\s*((\\w+\\s*)|([0-9]+(.[0-9]+)?))\\s*", regex_constants::icase);
		regex delete_from("\\s*delete\\s+from\\s+\\w+\\s+where\\s+\\w+\\s*=\\s*(([a-z_]+\\s*)|([0-9]+(.[0-9]+)?))\\s*", regex_constants::icase);
		regex exx("\\s*exit\\s*", regex_constants::icase);
		bool match = false;  string* cuvinte = fiecare_cuvant();  
		if (regex_match(comanda, insert))
		{
			INSERT_INTO(cuvinte);  return true;
		}
		if (regex_match(comanda, select))
		{
			int p = 0, v = 0;
			delimitariCorecte(comanda, p, v);
			SELECT(cuvinte, v + 1);
			return true;
		}
		if (regex_match(comanda, selectall))
		{
			SELECT_ALL(cuvinte);  return true;
		}
		if (regex_match(comanda, selectwhere))
		{
			int p = 0, v = 0;
			delimitariCorecte(comanda, p, v);
			SELECT_WHERE(cuvinte, v + 1);
			return true;
		}
		if (regex_match(comanda, update))
		{
			UPDATE(cuvinte); return true;
		}
		if (regex_match(comanda, delete_from))
		{
			DELETE_FROM(cuvinte); return true;
		}
		if (regex_match(comanda, exx))
		{
			return true;
		}
		if (regex_match(comanda, selectallwhere))
		{
			SELECT_ALL_WHERE(cuvinte); return true;
		}
		return match;
	}

	string nume_comanda_txt(string c="SELECT_") override
	{
		string nume; int k = 0;
		for (int i = 1; i < 100; i++)
		{
			string x = to_string(i);
			nume = c + x;
			if (check_nume(nume) == true)
			{
				x = to_string(i + 1);
				nume = c + x;
			}
			else return nume;
		}
	}

	bool structura_corecta(const Tabela& t, string* cuvinte)
	{
		bool flag = false;
		if (nr_cuvinte == (4 + t.nrC))
		{
			flag = true;
		}
		else return false;
		for (int i = 0; i < t.nrC; i++) //pentru fiecare coloana, 
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

	void INSERT_INTO(string* cuvinte)
	{
		string nume_fisier = cuvinte[2] + ".txt";  ifstream f; f.open(nume_fisier);  //caut fisierul tabelei
		if (f.is_open())
		{
			Tabela t; //creez tabela
			f >> t; //pe care o citesc din fisier , cu nr randuri 1
			int nrRanduri = t.nr_randuri;
			f.close();  Rand* copy = nullptr;
			if (t.nr_randuri > 0)
			{
				ifstream des(t.nume_tabela + ".bin", ios::binary | ios::in | ios::ate);
				if (des.is_open())
				{
					des.seekg(-4, ios::end);
					t.deserializare(des);
					des.close();
					copy = new Rand[t.nr_randuri + 1];
					for (int i = 0; i < t.nr_randuri; i++)
					{
						copy[i] = t.tabela[i];
					}
				}
			}
			else copy = new Rand[1];
			if (structura_corecta(t, cuvinte) == true)  //verific daca structura e ok
			{
				Rand r1(t.nrC, nullptr);  //creez randul
				string* vals = new string[t.nrC];  //un rand are valori asociate= nr coloane
				for (int i = 0; i < t.nrC; i++)
				{
					vals[i] = cuvinte[i + 4];  //salvez valorile in tabela
				}
				if (verificare_PK(t.nume_tabela, vals[0]) == false) {
					r1.set_valori(vals, t.nrC); //le setez randului
					copy[t.nr_randuri] = r1;  //il pun in vector
					t.nr_randuri++; //nr_randuri=1;
					t.setranduri(copy, t.nr_randuri);  //pun randul in tabela
					ofstream scriu_text; scriu_text.open(nume_fisier, ios::out | ios::trunc);
					scriu_text << t; //scriu t aici, unde va avea nr randuri +1
					scriu_text.close();
					ofstream f(t.nume_tabela + ".bin", ios::binary | ios::out | ios::app);
					t.serializare(f, t.nr_randuri - 1); //ii fac fisierul binar
					f.close();
					cout << "Datele au fost adaugate. " << endl;
				}
				else cout << "Datele nu au fost adaugate. " << endl;
				delete[] copy;
				delete[] vals;
			}
		}
		else
		{
			cout << "Tabela nu exista!" << endl;
		}
		f.close();
	}
	bool verificare_PK(string nt,string val)
	{
		set<string>s;
		string nume_fisier = nt + ".txt";  ifstream f; f.open(nume_fisier);  //caut fisierul tabelei
		Tabela t; //creez tabela 
		f >> t; //pe care o citesc din fisier , cu nr randuri 1
		f.close(); 
		ifstream g(nt + ".bin", ios::binary | ios::in | ios::ate);
		if (g.is_open())
		{
			g.seekg(-4, ios::end);
			t.deserializare(g);
		}
		g.close();
		for (int i = 0; i < t.nr_randuri; i++)
		{
			s.insert(t.tabela[i].valori[0]);
		}
		bool is_in;
		is_in = s.find(val) != s.end();
		cout << (is_in ? "Nu este respectata conditia de cheie primara!" : "") << endl;
		return is_in;		
	}
	
	void SELECT_ALL(string* cuvinte)
	{
		Tabela xx; //creez o tabela dummy
		string nume_fisier = cuvinte[3] + ".txt";  ifstream f; f.open(nume_fisier);
		ifstream g(cuvinte[3] + ".bin", ios::binary | ios::in | ios::ate);
		if (f.is_open() && g.is_open())
		{
			f >> xx;
			g.seekg(-4, ios::end);
			xx.setnume_tabela(cuvinte[3]);
			xx.deserializare(g);
			string nume = nume_comanda_txt("SELECT_");
			nume += ".txt";
			const char* aux = nume.c_str();
			ofstream out(nume);
			streambuf* coutbuf = cout.rdbuf(); //salvare buffer
			cout.rdbuf(out.rdbuf()); //redirectionare cout catre fisier
			xx.afisare_select();
			cout.rdbuf(coutbuf); //resetare catre standard output 
			cout << "Continutul tabelei este: " << endl<<endl;//afisam si la consol
			xx.afisare_select();
			cout << "Continutul anterior a fost salvat in fisierul " << nume << endl;
		}
		else
		{
			if (!f.is_open()) cout << "Tabela nu este creata." << endl;
			else if(!g.is_open()) cout << "Tabela nu contine date." << endl;
		}
		f.close(); g.close();
	}

	void SELECT(string* cuvinte, int nrc)
	{
		Tabela xx;
		string nume_fisier = cuvinte[nrc + 2] + ".txt";  ifstream f; f.open(nume_fisier);
		ifstream g(cuvinte[nrc + 2] + ".bin", ios::binary | ios::in | ios::ate);
		if (f.is_open() && g.is_open())
		{
			f >> xx;
			g.seekg(-4, ios::end);
			xx.setnume_tabela(cuvinte[3]);
			xx.deserializare(g);
			list<int> l;
			int vb = 0;
			for (int i = 0; i < nrc; i++)
				for (int j = 0; j < xx.nrC; j++)
					if (cuvinte[1 + i] == xx.coloane[j].nume_coloana)
					{
						vb++; l.push_back(j);
					}
			if (vb != nrc) cout << "Coloanele cautate (sau o parte din ele) nu fac parte din tabela!" << endl;
			else {
				string nume = nume_comanda_txt("SELECT_");
				nume += ".txt";
				const char* aux = nume.c_str();
				ofstream out(nume);
				streambuf* coutbuf = cout.rdbuf(); //salvare buffer
				cout.rdbuf(out.rdbuf()); //redirectionare cout catre fisier
				int k = nrc;
				for (int i = 0; i < xx.nr_randuri; i++)
				{
					xx.afisareSEL_Where(cuvinte, l, k, i); k = 0;
				}
				cout.rdbuf(coutbuf); //resetare catre standard output 
				cout << "Continutul cerut al tabelei este: " << endl;
				k = nrc;
				for (int i = 0; i < xx.nr_randuri; i++)
				{
					xx.afisareSEL_Where(cuvinte, l, k, i); k = 0;
				}
				cout << "Continutul anterior a fost salvat in fisierul " << nume << endl;
			}
		}
		else
		{
			if (!f.is_open()) cout << "Tabela nu este creata." << endl;
			else if (!g.is_open()) cout << "Tabela nu contine date." << endl;
		}
		f.close(); g.close();
	}

	void SELECT_WHERE(string* cuvinte, int nrc)
	{
		Tabela xx; 
		string nume_fisier = cuvinte[nrc+2] + ".txt";  ifstream f; f.open(nume_fisier);
		ifstream g(cuvinte[nrc+2] + ".bin", ios::binary | ios::in | ios::ate);
		if (f.is_open() && g.is_open())
		{
			f >> xx;
			g.seekg(-4, ios::end);
			xx.setnume_tabela(cuvinte[3]);
			xx.deserializare(g);
			int  rand = 0,ok=0;
			for (int i = 0; i < xx.nrC; i++)
				if (xx.coloane[i].nume_coloana == cuvinte[4+nrc])
					for (int j = 0; j < xx.nr_randuri; j++)
						if (xx.tabela[j].valori[i] == cuvinte[5+nrc]) {
							rand = j;  ok = 1; break;
						}
			if (ok) {
				vector<int> v;
				int vb = 0;
				for (int i = 0; i < nrc; i++)
					for (int j = 0;j < xx.nrC; j++)
						if (cuvinte[1 + i] == xx.coloane[j].nume_coloana)
						{
							vb++; v.push_back(j);
						}
				if (vb != nrc) cout << "Coloanele cautate (sau o parte din ele) nu fac parte din tabela!" << endl;
				else {
					string nume = nume_comanda_txt("SELECT_");
					nume += ".txt";
					const char* aux = nume.c_str();
					ofstream out(nume);
					streambuf* coutbuf = cout.rdbuf(); //salvare buffer
					cout.rdbuf(out.rdbuf()); //redirectionare cout catre fisier
					xx.afisSEL_Where(cuvinte, v, nrc, rand);
					cout.rdbuf(coutbuf); //resetare catre standard output 
					cout << "Continutul cerut al tabelei este: " << endl;
					xx.afisSEL_Where(cuvinte, v, nrc, rand);
					cout << "Continutul anterior a fost salvat in fisierul " << nume << endl;
				}
			}
			else cout << "Conditia din clauza where nu corespunde tabelei interogate!" << endl;

		}
		else
		{
			if (!f.is_open()) cout << "Tabela nu este creata." << endl;
			else if (!g.is_open()) cout << "Tabela nu contine date." << endl;
		}
		f.close(); g.close();
	}

    void SELECT_ALL_WHERE(string* cuvinte)
{
	string nume_fisier = cuvinte[3] + ".txt";  ifstream f; f.open(nume_fisier);
	string nume_f = cuvinte[3] + ".bin"; ifstream g; g.open(nume_f, ios::in | ios::app);
	if (g.is_open() && f.is_open())
	{
		Tabela xx;
		f >> xx;
		f.close();
		g.seekg(-4, ios::end);
		xx.setnume_tabela(cuvinte[3]);
		xx.deserializare(g);
		g.close();  bool ok = false;
		for (int i = 0; i < xx.nrC; i++)
		{
			if (xx.coloane[i].nume_coloana == cuvinte[5])
			{
				for (int j = 0; j < xx.nr_randuri; j++)
				{
					if (xx.tabela[j].valori[i] == cuvinte[6])
					{
						ok = true;
						string nume = nume_comanda_txt("SELECT_");
						nume += ".txt";
						const char* aux = nume.c_str();
						ofstream out(nume);
						streambuf* coutbuf = cout.rdbuf(); //salvare buffer
						cout.rdbuf(out.rdbuf()); //redirectionare cout catre fisier
						cout << "Continutul cerut al tabelei este: " << endl;
						xx.afisare_update();
						cout << xx.tabela[j];
						cout.rdbuf(coutbuf); //resetare catre standard output 
						cout << "Continutul cerut al tabelei este: " << endl;//afisam si la consol
						xx.afisare_update();
						cout << xx.tabela[j];
						cout << "Continutul anterior a fost salvat in fisierul " << nume << endl;
					}
					else ok == false;
				}
			}
		}
		if (ok == false) cout << "Conditia din clauza where nu corespunde tabelei interogate!" << endl;
	}
	else
	{
		if (!f.is_open()) cout << "Tabela nu este creata." << endl;
		else if (!g.is_open()) cout << "Tabela nu contine date." << endl;
	}
	f.close(); g.close();
 }

	/*void DELETE_FROM(string* cuvinte)
	{
		string nume_fisier = cuvinte[2] + ".txt";  ifstream f; f.open(nume_fisier);
		string nume_f = cuvinte[2] + ".bin"; ifstream g; g.open(nume_f, ios::binary | ios::in | ios::ate);
		if (f.is_open()&&g.is_open())
		{
			Tabela xx;
			f >> xx;
			f.close();
			g.seekg(-4, ios::end);
			xx.deserializare(g);
			g.close();
			int no = xx.nr_randuri - 1;
			Rand* nou = new Rand[xx.nr_randuri - 1];    int aa = 0;  bool flag = false;
			for (int i = 0; i < xx.nrC; i++)
			{
				if (xx.coloane[i].nume_coloana == cuvinte[4])
				{
					for (int j = 0; j < xx.nr_randuri; j++)
					{
						if (xx[j].valori[i] == cuvinte[5]) //afisez randul pe care se afla valoarea pe care o caut
						{
							flag = true;
							if (xx.nr_randuri > 1) {
								for (int k = j; k < xx.nr_randuri - 1; k++)
								{
									xx[k] = xx[k + 1];
								}
								xx.nr_randuri--;
								nou[aa++] = xx[j];
							}
							else {
								if (xx.nr_randuri == 1) {    //sterg si fisierul binar
									xx.setranduri(nullptr, 0);
									if (remove(nume_f.c_str()) != 0) //sterg
										perror("Eroare stergere fisier binar.");
									else
										puts("Tabela nu mai contine nicio data. Fisierul binar asociat a fost eliminat.");
								}
							}
						}
					}
				}
			}
			if (flag == false) cout << "Conditia din clauza where nu corespunde tabelei interogate!" << endl;
			else {
				if (xx.nr_randuri > 1) xx.setranduri(nou, no);
				ofstream scriu_text; scriu_text.open(nume_fisier, ios::out | ios::trunc);
				scriu_text << xx; //scriu t aici, unde va avea nr randuri -1
				scriu_text.close();
				if (xx.nr_randuri > 1) {
					ofstream bin(xx.nume_tabela + ".bin", ios::binary | ios::out | ios::trunc);
					for (int i = 0; i < no; i++)
						xx.serializare(bin, i); //ii fac fisierul binar
					bin.close();
					cout << "Datele au fost actualizate in fisierul " << xx.nume_tabela << ".bin ." << endl;
				}
			}
		}
		else
		{
			if (!f.is_open()) cout << "Tabela nu este creata." << endl;
			else if (!g.is_open()) cout << "Tabela nu contine date." << endl;
		}
		g.close(); f.close();
	} */

 void DELETE_FROM(string* cuvinte)
 {
	 string nume_fisier = cuvinte[2] + ".txt";  ifstream f; f.open(nume_fisier);
	 string nume_f = cuvinte[2] + ".bin"; ifstream g; g.open(nume_f, ios::binary | ios::in | ios::ate);
	 if (f.is_open() && g.is_open())
	 {
		 Tabela xx;
		 f >> xx;
		 f.close();
		 g.seekg(-4, ios::end);
		 xx.deserializare(g);
		 g.close();
		 int no = xx.nr_randuri - 1;
		 Rand* nou = new Rand[no]; int rand = 0,col=0;
	     int aa = 0;  bool flag = false;
		 for (int i = 0; i < xx.nrC; i++)
		 {
			 if (xx.coloane[i].nume_coloana == cuvinte[4])
			 {
				 col = i;
				 for (int j = 0; j < xx.nr_randuri; j++)
				 {
					 if (xx[j].valori[i] == cuvinte[5]) //afisez randul pe care se afla valoarea pe care o caut
					 {
						 flag = true;  rand = j;
						 if (xx.nr_randuri > 1) {
							 for (int y = 0; y <rand; y++)
							 {
								 nou[y] = xx.tabela[y];
							 }
							 for (int y = rand + 1; y < xx.nr_randuri; y++)
							 {
								 nou[y-1] = xx.tabela[y];
							 }
							 xx.nr_randuri--;
						 }
						 else {
							 if (xx.nr_randuri == 1) {    //sterg si fisierul binar
								 xx.setranduri(nullptr, 0);
								 if (remove(nume_f.c_str()) != 0) //sterg
									 perror("Eroare stergere fisier binar.");
								 else
									 puts("Tabela nu mai contine nicio data. Fisierul binar asociat a fost eliminat.");
							 }
						 }
						 
					 }
					
				 }
			 }
		 }
		 if (flag == false) cout << "Conditia din clauza where nu corespunde tabelei interogate!" << endl;
		 else {
			 if (xx.nr_randuri > 0) xx.setranduri(nou,xx.nr_randuri);
			 ofstream scriu_text; scriu_text.open(nume_fisier, ios::out | ios::trunc);
			 scriu_text << xx; //scriu xx aici, unde va avea nr randuri -1
			 scriu_text.close();
			 if (xx.nr_randuri > 0) {
				 ofstream bin(xx.nume_tabela + ".bin", ios::binary | ios::out | ios::trunc);
				 for (int i = 0; i < no; i++)
					 xx.serializare(bin, i); //ii fac fisierul binar
				 bin.close();
				 cout << "Datele au fost actualizate in fisierul " << xx.nume_tabela << ".bin ." << endl;
			 }
		 }
	 }
	 else
	 {
		 if (!f.is_open()) cout << "Tabela nu este creata." << endl;
		 else if (!g.is_open()) cout << "Tabela nu contine date." << endl;
	 }
	 g.close(); f.close();
 }

	void UPDATE(string* cuvinte)
	{
		string nume_fisier = cuvinte[1] + ".txt";  ifstream f; f.open(nume_fisier);
		string nume_f = cuvinte[1] + ".bin"; ifstream g; g.open(nume_f, ios::binary | ios::in | ios::ate);
		if (g.is_open() && f.is_open())
		{
			Tabela xx;
			f >> xx;
			f.close();
			g.seekg(-4, ios::end);
			xx.deserializare(g);
			g.close();
			Rand* nou = new Rand[xx.nr_randuri];   int no = xx.nr_randuri;
			int k = 0;
			int ok = 0;  
			for (int i = 0; i < xx.nrC; i++)
				if (xx.coloane[i].nume_coloana == cuvinte[6])
					for (int j = 0; j < xx.nr_randuri; j++)
						if (xx.tabela[j].valori[i] == cuvinte[7]) {
							ok = 1; k = j;
						}
			if (ok == 1)
			{
				ok = 0; int col = 0;
				for (int i = 0; i < xx.nrC; i++)
					if (xx.coloane[i].nume_coloana == cuvinte[3]) {
						col = i; ok = 1; break;
					}
				if (ok == 1)
				{
					bool vf = verificare_PK(xx.nume_tabela, cuvinte[4]);
					if (col == 0&&vf==true) {
						cout << "Prin acest update nu s-ar mai respecta conditia de cheie primara!" << endl;
					}
					else if (col > 0|| (col == 0 && vf== false)) {
						for (int i = 0; i < xx.nrC; i++)
							if (xx.coloane[i].nume_coloana == cuvinte[3])
							{
								xx.tabela[k].valori[i] = cuvinte[4];
								for (int j = 0; j < xx.nr_randuri; j++)
								{
									nou[j] = xx[j];
									cout << xx.tabela[j];
								}
							}
						xx.setranduri(nou, no);
						ofstream bin(xx.nume_tabela + ".bin", ios::binary | ios::out | ios::trunc);
						for (int i = 0; i < no; i++)
							xx.serializare(bin, i); //ii fac fisierul binar
						bin.close();
						cout << "Datele au fost actualizate in fisierul " << xx.nume_tabela << ".bin ." << endl;
					}
				}
				else cout << "Coloana cautata nu corespunde tabelei interogate!" << endl;
			}
			else cout << "Conditia din clauza where nu corespunde tabelei interogate!" << endl;
		}
		else
		{
			if (!f.is_open()) cout << "Tabela nu este creata." << endl;
			else if (!g.is_open()) cout << "Tabela nu contine date." << endl;
		}
		g.close(); f.close();
	}

};

ostream& operator<<(ostream& out, Parsing p)
{
	out << "comanda: " << p.comanda << endl;
	out << "numar cuvinte: " << p.nr_cuvinte << endl;
	return out;
}

istream& operator>>(istream& in, Parsing& p)
{
	cout << "comanda = ";
	in >> p.comanda;
	cout << "numar cuvinte = ";
	in >> p.nr_cuvinte;
	cout << "nume tabela = ";
	return in;
}

class TheMain 
{
	int argc;
	char** argv;

public:

	TheMain(int arc, char** argv):argc(arc)
	{
		if (arc > 1)
		{
			this->argv = new char* [arc];
			for (int i = 0; i < arc; i++)
				argv[i] = new char[arc];
		}
		else this->argv = nullptr;
	}
	TheMain(const TheMain& tm) :argc(tm.argc)
	{
		if (tm.argc > 1)
		{
			this->argv = new char* [argc];
			for (int i = 0; i < argc; i++)
				argv[i] = new char[argc];
		}
		else this->argv = nullptr;
	}
	~TheMain()
	{
		if (argv != nullptr) {
			for (int i = 0; i < argc; ++i) {
				delete[] argv[i];
			}
			delete[] argv;
		}
	}
	TheMain& operator=(const TheMain& tm)
	{
		if (argv != nullptr) {
			for (int i = 0; i < argc; ++i) {
				delete[] argv[i];
			}
			delete[] argv;
		}
		this->argc = tm.argc;
		if (tm.argc > 1)
		{
			this->argv = new char* [argc];
			for (int i = 0; i < argc; i++)
				argv[i] = new char[argc];
		}
		else this->argv = nullptr;
	}

	void unArgument()
	{
		if (argc == 1) {
			string comm = "";
			while (comm != "exit") {
				cout << endl << "Introduceti comanda: ";
				cin >> ws;
				getline(cin, comm);
				LMD m(comm); LDD d(comm);
				bool match = false;
				match = m.matchcom();
				if (match == false)//o verific
				{
					match=d.matchcom();
					cout << (match ? "" : "Eroare de sintaxa!") << endl;
				}
			}
		}
	}
	void importIn()
	{
		string name = argv[3], nametxt = argv[2];
		int pos = name.find(".");
		string sub = name.substr(pos + 1);
		if (sub == "csv")
		{
			ifstream csv; csv.open(name); ifstream txt; txt.open(nametxt + ".txt");
			if (csv.is_open() && txt.is_open())
			{
				Tabela t;
				txt >> t;
				txt.close();
				t.citireCSV(csv);
				csv.close();
			}
			else {
				cout << "Nu s-a deschis fisierul " << name << " cautat!" << endl;
			}
			csv.close();
			txt.close();
		}
		else cout << "Nu ati introdus un fisier csv!" << endl;
	}
	void comenziFisier()
	{
		//6 argumente maxime: 1 e MYsql.exe, celelalte 5 (max!) sunt fisierele cu comenzi
		for (int i = 1; i < argc; i++)
		{  //de la arg 1 pana la final am fisierele
			char* comm = new char[strlen(argv[i]) + 1];  //iau acest argument (nume fisier)
			strcpy(comm, argv[i]);
			string name = comm;  //salvez in name
			ifstream g(name);  //ca sa pot deschide fisierul trimis ca argument
			string c; //comanda pe care o voi citi
			int k = 0;
			if (g.is_open()) {
				while (!g.eof())
				{  //cat timp nu se incheie fisierul
					getline(g, c);  //citesc comanda de pe fiecare linie
					LMD m(comm); LDD d(comm);
					cout << "Comanda " << k + 1 << endl;
					bool match = false;
					match = m.matchcom();
					if (match == false)//o verific
					{
						d.matchcom();
						cout << (match ? "" : "Eroare de sintaxa!") << endl;
					}						
					g >> ws;  //dupa, citesc spatiul
					c = "";  //golesc comanda
					cout << endl;
					k++;
					cout << "Apasati o tasta pentru a continua." << endl;
					getchar();
				}
			}
			else cout << "Nu exista fisierul cu numele " << name << "!" << endl;
			g.close(); //am terminat, inchid fisierul
		}  //acum continui pana termin fisierele
	}

};
