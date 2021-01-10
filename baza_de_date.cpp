#include "clase.h"
#include <iostream>
#include<string>
#include <algorithm>
#include <regex>
#include <fstream>
#include <stdio.h>
#include<exception>
#include<new>
#pragma warning(disable : 4996)
#define OUT 0  
#define IN 1  
using namespace std;


int main(int argc, char* argv[])
{
	//pentru citirea comenzii de la tastatura
	if (argc == 1) {
		try {
			string comm = "";
			cout << "Introduceti comanda: ";
			while (comm != "exit") {
				cin >> ws;
				getline(cin, comm);
				Parsing pp(comm);
				//pp.set_baza(b);
				LMD m(pp.getcomanda(), pp.getnr_cuvinte()); 
				LDD d(pp.getcomanda(), pp.getnr_cuvinte());
				pp.setLDD(d);
				pp.setLMD(m);
				pp.matchcom();
				cout << "nr: " << pp.getnr_cuvinte() << endl;

			}
			/*comm = "";
			cout << "Dati nume: "; getline(cin, comm);
			Parsing pp;
			pp.test(comm);*/
		}
		catch (exception& e) {
			std::cerr << "some other standard exception caught: " << e.what() << '\n';
		}
	}

	//pentru citirea comenzii din fisiere transmise ca argumentele liniei de comanda
	else {
		try
		{
			if (argc <= 6) //6 argumente maxime: 1 e MYsql.exe, celelalte 5sunt fisierele cu comenzi
			{  
				for (int i = 1; i < argc; i++) //de la arg 1 pana la final am fisierele
				{ 
					char* comm = new char[strlen(argv[i]) + 1]; //iau acest argument (nume fisier)
					strcpy(comm, argv[i]);
					string name = comm;  //salvez in name
					ifstream g(name);  //ca sa pot deschide fisierul trimis ca argument
					string c; //comanda pe care o voi citi
					int k = 0;
					while (!g.eof()) //cat timp nu se incheie fisierul
					{  
						getline(g, c); //citesc comanda de pe fiecare linie
						Parsing pp(c);
						cout << "Comanda " << k + 1 << endl;
						pp.matchcom();  //verific comanda
						g >> ws;  //citesc spatiul
						c = "";  //golesc comanda
						cout << endl;
						k++;
						cout << "Apasati o tasta pentru a continua." << endl;
						getchar();
					}
					g.close();
				}
			}
		}
		catch (exception& e) 
		{
			cerr << "Exceptie: " << e.what() << '\n';
		}
	}
}
