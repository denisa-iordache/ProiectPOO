#ProiectPOO
#include <iostream>
#include<string>
#include <algorithm>
using namespace std;

//utilizabil mai tarziu pentru a gestiona erorile
typedef enum { COMANDA_NERECUNOSCUTA = 0, COMANDA_CORECTA = 1 } StatusComanda;
typedef enum { CREARE = 0, DROP = 1, DISPLAY = 2, NECUNOSCUT = 3 } Functie;

class Coloana
{
//public:
private:
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
	}

	Coloana(string nume_coloana, string tip, int dimensiune, char* valoare_implicita) //constructor cu parametri
	{
		this->nume_coloana = nume_coloana;
		this->tip = tip;
		this->dimensiune = dimensiune;
		if (valoare_implicita != nullptr)
		{
			this->valoare_implicita = new char[strlen(valoare_implicita) + 1];
			strcpy_s(this->valoare_implicita, strlen(valoare_implicita) + 1, valoare_implicita);
		}
	}

	Coloana(const Coloana& c) //constructor de copiere
	{
		this->nume_coloana = c.nume_coloana;
		this->tip = c.tip;
		this->dimensiune = c.dimensiune;
		if (c.valoare_implicita != nullptr)
		{
			this->valoare_implicita = new char[strlen(c.valoare_implicita) + 1];
			strcpy_s(this->valoare_implicita, strlen(c.valoare_implicita) + 1, c.valoare_implicita);
		}
	}

	~Coloana() //destructor
	{
		if (valoare_implicita != nullptr)
		{
			delete[] valoare_implicita;
		}
	}

	Coloana operator=(const Coloana& c) //operator=
	{
		if (valoare_implicita != nullptr)
		{
			delete[] valoare_implicita;
		}
		this->nume_coloana = c.nume_coloana;
		this->tip = c.tip;
		this->dimensiune = c.dimensiune;
		if (c.valoare_implicita != nullptr)
		{
			this->valoare_implicita = new char[strlen(c.valoare_implicita) + 1];
			strcpy_s(this->valoare_implicita, strlen(c.valoare_implicita) + 1, c.valoare_implicita);
		}
		return *this;
	}

	char& operator[](int index) //operatorul pentru indexare
	{
		if (index >= 0 && index < strlen(valoare_implicita))
		{
			return valoare_implicita[index];
		}
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

	string getnume_coloana()
	{
		return nume_coloana;
	}

	void setnume_coloana(string nume_coloana)
	{
			this->nume_coloana = nume_coloana;
	}

	string gettip()
	{
		return tip;
	}

	void settip(string tip)
	{
		this->tip = tip;
	}

	int getdimensiune()
	{
		return dimensiune;
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

		this->valoare_implicita = new char[strlen(valoare_implicita) + 1];
		strcpy_s(this->valoare_implicita, strlen(valoare_implicita) + 1, valoare_implicita);
	}

	friend ostream& operator<<(ostream&, Coloana);
	friend istream& operator>>(istream&, Coloana&);

};

ostream& operator<<(ostream& out, Coloana c)
{
	out << "nume coloana: " << c.nume_coloana << endl;
	out << "tip: " << c.tip << endl;
	out << "dimensiune: " << c.dimensiune << endl;
	out << "valoare implicita: ";
	if (c.valoare_implicita != nullptr)
	{
		out << c.valoare_implicita;
	}
	out << endl;
	return out;
}

istream& operator>>(istream& in, Coloana& c)
{
	cout << "nume coloana = ";
	in >> c.nume_coloana;
	cout << "tip = ";
	in >> c.tip;
	cout << "dimensiune = ";
	in >> c.dimensiune;
	string buffer;
	cout << "valoare implicita: ";
	in >> buffer;
	if (c.valoare_implicita != nullptr)
	{
		delete[] c.valoare_implicita;
	}
	c.valoare_implicita = new char[buffer.length() + 1];
	strcpy_s(c.valoare_implicita, buffer.length() + 1, buffer.c_str());
	return in;
}

class Rand
{
public:
//private:
	Coloana* coloane; //Un rand reprezinta un vector de coloane
	int nr_coloane;
	string inregistrare;
public:
	Rand() //constructor implicit
	{
		nr_coloane = 0;
		coloane = nullptr;
		inregistrare = "";
	}

	Rand(int nr_coloane, Coloana* coloane, string inregistrare) //constructor cu parametri
	{
		this->inregistrare = inregistrare;
		if (coloane != nullptr && nr_coloane > 0)
		{
			this->nr_coloane = nr_coloane;
			this->coloane = new Coloana[nr_coloane];
			for (int i = 0; i < nr_coloane; i++)
			{
				this->coloane[i] = coloane[i];
			}
		}
	}

	Rand(const Rand& r) //constructor de copiere
	{
		this->inregistrare = r.inregistrare;
		if (r.coloane != nullptr && r.nr_coloane > 0)
		{
			this->nr_coloane = r.nr_coloane;
			this->coloane = new Coloana[r.nr_coloane];
			for (int i = 0; i < r.nr_coloane; i++)
			{
				this->coloane[i] = r.coloane[i];
			}
		}
	}
	
	~Rand()
	{
		if (coloane != nullptr)
		{
			delete[] coloane;
		}
	}

	Rand& operator=(const Rand& r) //operator=
	{
		if (coloane != nullptr)
		{
			delete[] coloane;
		}
		this->inregistrare = r.inregistrare;
		if (r.coloane != nullptr && r.nr_coloane > 0)
		{
			this->nr_coloane = r.nr_coloane;
			this->coloane = new Coloana[r.nr_coloane];
			for (int i = 0; i < r.nr_coloane; i++)
			{
				this->coloane[i] = r.coloane[i];
			}
		}
		return *this;
	}

	Coloana& operator[](int index) //operatorul pentru indexare
	{
		if (index >= 0 && index < nr_coloane)
		{
			return coloane[index];
		}
	}

	bool operator!() //operator!
	{
		return nr_coloane > 0;
	}

	/*int getnr_coloane()
	{
		return nr_coloane;
	}

	string getinregistrare()
	{
		return inregistrare;
	}

	void setinregistrare(string inregistrare)
	{
		this->inregistrare = inregistrare;
	}

	Coloana* getcoloane()
	{
		return coloane;
	}

	void setcoloane(Coloana* c)
	{
		coloane = c;
	}*/

	friend ostream& operator<<(ostream&, Rand);
	friend istream& operator>>(istream&, Rand&);
};

ostream& operator<<(ostream& out, Rand r)
{
	out << "inregistrare: " << r.inregistrare << endl;
	out << "numar coloane: " << r.nr_coloane << endl;
	out << "coloane: ";
	if (r.coloane != nullptr)
	{
		for (int i = 0; i < r.nr_coloane; i++)
		{
			out << r.coloane[i] << " ";
		}
	}
	return out;
}

istream& operator>>(istream& in, Rand& r)
{
	cout << "inregistrare = ";
	in >> r.inregistrare;
	cout << "numar coloane = ";
	in >> r.nr_coloane;
	if (r.coloane != nullptr)
	{
		delete[] r.coloane;
	}
	if (r.nr_coloane > 0)
	{
		r.coloane = new Coloana[r.nr_coloane];
		for (int i = 0; i < r.nr_coloane; i++)
		{
			cout << "coloana[" << i << "] = ";
			in >> r.coloane[i];
		}
	}
	else
	{
		r.nr_coloane = 0;
		r.coloane = nullptr;
	}
	return in;
}


class Tabela
{
public:
//private:
	Rand* randuri; //O tabela reprezinta un vector de randuri
	int nr_randuri;
	string nume_tabela;
public:
	Tabela() //constructor implicit
	{
		nume_tabela = "";
		nr_randuri = 0;
		randuri = nullptr;
	}

	Tabela(int nr_randuri, Rand* randuri, string nume_tabela) //constructor cu parametri
	{
		this->nume_tabela = nume_tabela;
		if (randuri != nullptr && nr_randuri > 0)
		{
			this->nr_randuri = nr_randuri;
			this->randuri = new Rand[nr_randuri];
			for (int i = 0; i < nr_randuri; i++)
			{
				this->randuri[i] = randuri[i];
			}
		}
	}

	Tabela(const Tabela& t) //constructor de copiere
	{
		this->nume_tabela = t.nume_tabela;
		if (t.randuri != nullptr && t.nr_randuri > 0)
		{
			this->nr_randuri = t.nr_randuri;
			this->randuri = new Rand[t.nr_randuri];
			for (int i = 0; i < t.nr_randuri; i++)
			{
				this->randuri[i] = t.randuri[i];
			}
		}
	}

	~Tabela()
	{
		if (randuri != nullptr)
		{
			delete[] randuri;
		}
	}

	Tabela& operator=(const Tabela& t)
	{
		if (randuri != nullptr)
		{
			delete[] randuri;
		}
		this->nume_tabela = t.nume_tabela;
		if (t.randuri != nullptr && t.nr_randuri > 0)
		{
			this->nr_randuri = t.nr_randuri;
			this->randuri = new Rand[t.nr_randuri];
			for (int i = 0; i < t.nr_randuri; i++)
			{
				this->randuri[i] = t.randuri[i];
			}
		}
		return *this;
	}

	Rand& operator[](int index) //operatorul pentru indexare
	{
		if (index >= 0 && index < nr_randuri)
		{
			return randuri[index];
		}
	}

	bool operator!() //operator!
	{
		return nr_randuri > 0;
	}

	/*int getnr_randuri()
	{
		return nr_randuri;
	}

	string getnume_tabela()
	{
		return nume_tabela;
	}

	void setnume_tabela(string nume_tabela)
	{
		this->nume_tabela = nume_tabela;
	}

	Rand* getranduri()
	{
		return randuri;
	}

	void setranduri(Rand* r)
	{
		randuri = r;
	}*/

	friend ostream& operator<<(ostream&, Tabela);
	friend istream& operator>>(istream&, Tabela&);

};

ostream& operator<<(ostream& out, Tabela t)
{
	out << "nume tabela: " << t.nume_tabela << endl;
	out << "numar randuri: " << t.nr_randuri << endl;
	out << "randuri: ";
	if (t.randuri != nullptr)
	{
		for (int i = 0; i < t.nr_randuri; i++)
		{
			out << t.randuri[i] << " ";
		}
	}
	return out;
}

istream& operator>>(istream& in, Tabela& t)
{
	cout << "nume tabela = ";
	in >> t.nume_tabela;
	cout << "numar randuri = ";
	in >> t.nr_randuri;
	if (t.randuri != nullptr)
	{
		delete[] t.randuri;
	}
	if (t.nr_randuri > 0)
	{
		t.randuri = new Rand[t.nr_randuri];
		for (int i = 0; i < t.nr_randuri; i++)
		{
			cout << "rand[" << i << "] = ";
			in >> t.randuri[i];
		}
	}
	else
	{
		t.nr_randuri = 0;
		t.randuri = nullptr;
	}
	return in;
}

class Baza
{
public:
//private:
	Tabela* tabele; //Baza reprezinta un vector de tabele
	int nr_tabele;
	string nume_db;
public:
	Baza() //constructor implicit
	{
		nume_db = "";
		nr_tabele = 0;
		tabele = nullptr;
	}

	Baza(int nr_tabela, Tabela* tabele, string nume_db) //constructor cu parametri
	{
		this->nume_db = nume_db;
		if (tabele != nullptr && nr_tabele > 0)
		{
			this->nr_tabele = nr_tabele;
			this->tabele = new Tabela[nr_tabele];
			for (int i = 0; i < nr_tabele; i++)
			{
				this->tabele[i] = tabele[i];
			}
		}
	}

	Baza(const Baza& b) //constructor de copiere
	{
		this->nume_db = b.nume_db;
		if (b.tabele != nullptr && b.nr_tabele > 0)
		{
			this->nr_tabele = b.nr_tabele;
			this->tabele = new Tabela[b.nr_tabele];
			for (int i = 0; i < b.nr_tabele; i++)
			{
				this->tabele[i] = b.tabele[i];
			}
		}
	}

	~Baza()
	{
		if (tabele != nullptr)
		{
			delete[] tabele;
		}
	}

	Baza& operator=(const Baza& b)
	{
		if (tabele != nullptr)
		{
			delete[] tabele;
		}
		this->nume_db = b.nume_db;
		if (b.tabele != nullptr && b.nr_tabele > 0)
		{
			this->nr_tabele = b.nr_tabele;
			this->tabele = new Tabela[b.nr_tabele];
			for (int i = 0; i < b.nr_tabele; i++)
			{
				this->tabele[i] = b.tabele[i];
			}
		}
		return *this;
	}

	Tabela& operator[](int index) //operatorul pentru indexare
	{
		if (index >= 0 && index < nr_tabele)
		{
			return tabele[index];
		}
	}

	bool operator!() //operator!
	{
		return nr_tabele > 0;
	}

	/*int getnr_tabele()
	{
		return nr_tabele;
	}

	string getnume_db()
	{
		return nume_db;
	}

	void setnume_db(string nume_db)
	{
		this->nume_db = nume_db;
	}

	Tabela* gettabele()
	{
		return tabele;
	}

	void settabele(Tabela* t)
	{
		tabele = t;
	}*/

	friend ostream& operator<<(ostream&, Baza);
	friend istream& operator>>(istream&, Baza&);
};

ostream& operator<<(ostream& out, Baza b)
{
	out << "nume baza: " << b.nume_db << endl;
	out << "numar tabele: " << b.nr_tabele << endl;
	out << "tabele: ";
	if (b.tabele != nullptr)
	{
		for (int i = 0; i < b.nr_tabele; i++)
		{
			out << b.tabele[i] << " ";
		}
	}
	return out;
}

istream& operator>>(istream& in, Baza& b)
{
	cout << "nume baza = ";
	in >> b.nume_db;
	cout << "numar tabele = ";
	in >> b.nr_tabele;
	if (b.tabele != nullptr)
	{
		delete[] b.tabele;
	}
	if (b.nr_tabele > 0)
	{
		b.tabele = new Tabela[b.nr_tabele];
		for (int i = 0; i < b.nr_tabele; i++)
		{
			cout << "tabela[" << i << "] = ";
			in >> b.tabele[i];
		}
	}
	else
	{
		b.nr_tabele = 0;
		b.tabele = nullptr;
	}
	return in;
}

class Parsing
{
private:
	string comanda;
	int nr_cuvinte;
	StatusComanda status;
	Functie functie;
	string nume_tabela;
	Baza b;
public:

	Parsing(string comanda)
	{
		this->status = StatusComanda(0);
		this->functie = Functie(3);
		this->comanda = comanda;
		int spatii = 0;
		for (int i = 0; i < comanda.length(); i++) //numar spatiile dintr-un string, pentru a sti cate cuvinte am
		{
			int c = comanda[i];
			if (isspace(c))
				spatii++;
		}
		this->nr_cuvinte = spatii + 1;
	}
	int egalitate(string s1, string s2) {  //pentru a verifica daca o comanda primita este una din cele trei
		//convertesc s1 si s2 in litere mici
		transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
		transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
		if (s1.compare(s2) == 0)
			return 1; //la fel
		return 0; //diferite
	}

	string* fiecare_cuvant()
	{
		string* cuvinte = new string[nr_cuvinte];  //aloc vector de cuvinte regasite in comanda data
		int k = 0;  //contorul cuvintelor
		for (int i = 0; i < this->comanda.length(); i++)
		{
			if (this->comanda[i] != ' ')
			{
				cuvinte[k] += this->comanda[i];
			}
			else {
				k++;
			}
		}
		return cuvinte;
	}

	void atribuie_comanda()
	{
		string* cuvinte = fiecare_cuvant();
		if (egalitate(cuvinte[0], "create")) {
			if (nr_cuvinte == 1)
				cout <<
				"Daca doriti sa creati tabel, tastati \n\n CREATE TABLE nume_tabel [DACA NU EXISTA] \n\t((nume_coloana_1, tip, dimensiune, valoare_implicita),	\n\t(nume_coloana_2, tip, dimensiune, valoare_implicita), ...) " << endl << endl;
			status = StatusComanda(1);
			if (nr_cuvinte > 1 && egalitate(cuvinte[1], "table")) {
				cout << "Comanda recunoscuta, doriti sa creati tabel." << endl;
				this->functie = Functie(0);
				CREATE_TABLE(cuvinte);
			}
			else {
				cout << "Nu ati tastat continuarea corecta a comenzii" << endl;
				status = StatusComanda(0);
			}
		}
		else {
			if (egalitate(cuvinte[0], "drop")) {
				if (nr_cuvinte == 1)
					cout <<
					"Daca doriti sa stergeti tabelul, tastati \n\n DROP TABLE table_name " << endl << endl;
				status = StatusComanda(1);
				if (nr_cuvinte > 1 && egalitate(cuvinte[1], "table")) {
					cout << "Comanda recunoscuta, doriti sa stergeti tabel." << endl;
					this->functie = Functie(1);
					DROP_TABLE(cuvinte);
				}
				else {
					cout << "Nu ati tastat continuarea corecta a comenzii" << endl;
					status = StatusComanda(0);
				}
			}
			else {
				if (egalitate(cuvinte[0], "display")) {
					if (nr_cuvinte == 1)
						cout <<
						"Daca doriti sa afisati tabelul, tastati \n\n DISPLAY TABLE table_name " << endl << endl;
					status = StatusComanda(1);
					if (nr_cuvinte > 1 && egalitate(cuvinte[1], "table")) {
						cout << "Comanda recunoscuta, doriti sa afisati tabel." << endl;
						this->functie = Functie(2);
						DISPLAY_TABLE(cuvinte);
					}
					else {
						cout << "Nu ati tastat continuarea corecta a comenzii!" << endl;
						status = StatusComanda(0);
					}
				}
				else
				{
					cout << "Comanda nerecunoscuta!" << endl;
					status = StatusComanda(1);
				}
			}
			if (egalitate(cuvinte[0], "exit"))
			{
				if (nr_cuvinte == 1)
					cout <<"Daca doriti sa creati tabel, tastati \n\n CREATE TABLE nume_tabel [DACA NU EXISTA] \n\t((nume_coloana_1, tip, dimensiune, valoare_implicita),	\n\t(nume_coloana_2, tip, dimensiune, valoare_implicita), ...) " << endl << endl;
			}
		}
	}

	void check_nume(string* cuvinte)
	{
		if (nr_cuvinte > 2 && (cuvinte[2] != ""))
		{
			nume_tabela = cuvinte[2];
			cout << "Numele tabelei este " << nume_tabela << endl;
		}
		else
		{
			cout << "Nu ati introdus nume tabela!" << endl;
		}
	}

	void CREATE_TABLE(string* cuvinte)
	{
		check_nume(cuvinte);
		if (this->functie == 0)
		{
			check_nume(cuvinte);
			//verificare daca avem [DACA NU EXISTA]
			if (nr_cuvinte > 5 &&
				(cuvinte[3] != "") && egalitate(cuvinte[3], "daca") &&
				(cuvinte[4] != "") && egalitate(cuvinte[4], "nu") &&
				(cuvinte[5] != "") && egalitate(cuvinte[5], "exista")) {
				cout << "Ok!" << endl;
			}
			else { //mai e de facut
				cout << "Nu ati tastat continuarea/continuarea corecta a comenzii" << endl;
				status = StatusComanda(0);
			}
				//sa salvam numele coloanei si sa tranmitem constr de copiere
			// si macar o coloana
			// apoi citim din coloana: nume, tip, dimensiune, val implicita
			//fa ce trebuie //ar trebui sa ne trimita la clasa tabela
		}

		//parcurg vectorul de tabele din clasa baza si din fiecare obiect de tipul tabela verific atributul nume_tabela, daca e egal cu numele tabelei pe care incerc sa o creez, nu o creez, deja exista
		//daca tabela nu exista o creez, face tabela cu propr de la tastatura in grupe de cate 3 pt fiecare coloana, din fiecare grup iau fiecare cuvant si sa l duc intr un obiect de tipul coloana
		for (int i = 0; i < b.nr_tabele; i++)
		{
			if (cuvinte[2] == b.tabele[i].nume_tabela)
			{
				cout << "Tabela exista deja. Tastati alt nume." << endl;
			}

		}
	}


	void DROP_TABLE(string* cuvinte)
	{
		if (this->functie == 1)
		{
			check_nume(cuvinte);
			for (int i = 0; i < b.nr_tabele; i++)
			{
				if (cuvinte[2] == b.tabele[i].nume_tabela)
				{
					cout << "Tabela a fost stearsa cu succes. Tastati alt nume." << endl;
				}

			}
		}

	}
	//cand verific numele coloanei si salvez

	void DISPLAY_TABLE(string* cuvinte)
	{
		if (this->functie == 2)
		{
			check_nume(cuvinte);
			//fa ce trebuie
			for (int i = 0; i < b.nr_tabele; i++)
			{
				if (cuvinte[2] == b.tabele[i].nume_tabela)
				{
					cout << "Afiseaza tabela." << endl;
				}

			}
		}

	}
};

int main()
{
	string comm;
	cout << "Introduceti comanda: ";
	while (comm != "exit") {
		cin >> ws; //sterge din buffer white spaces sau enter-uri
		getline(cin, comm);
		Parsing pp(comm);
		pp.atribuie_comanda();
	} //dupa ce tastez exit dupa ce recunosc comanda sa nu tastez exit si sa ma trimita implicit la creare tabela
		//Tabela table....
	//  1. sa gestionez cand tastez exit
	//  2. sa afisez, pentru momentul in care nu e introdusa
	//  una din cele 3 comenzi, daca utilizatorul doreste
	//  ghid (cum sa tasteze comenzile)

	//gestionare spatii repetate in comanda; cred ca e facut
	//termin create table + destructor la parsing(dar nu am pointer)

}
