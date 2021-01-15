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
	try {
		TheMain themain(argc, argv);
		if (argc == 1) {
			themain.unArgument();  //pentru citirea comenzii de la tastatura
		}
		else if (argc == 4&&( strcmp(argv[1], "import")|| strcmp(argv[1], "IMPORT")))
		{
			themain.importIn();  //pentru citirea comenzii din fisiere transmise ca argumentele liniei de comanda
		}
		else if (argc <= 6&&argc>=2)
		{ 
			themain.comenziFisier();  //6 argumente maxime: 1 e MYsql.exe, celelalte 5 (max!) sunt fisierele cu comenzi
		}
	}
	catch (exceptii& e) {
		cerr << "Exceptie: " << e.what() << endl;
		e.set_mesaj_exceptie(e.what());
		cout << endl << e.get_mesaj_exceptie() << endl;
	}
}
