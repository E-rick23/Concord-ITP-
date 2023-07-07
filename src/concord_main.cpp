#include <iostream>
#include <list>
#include <vector>
#include <string>
#include "sistema.h"
#include "principal.h"

using namespace std;

int main()
{
	cout << "Bem vindo! Digite um comando para começar (ou 'help' para ajuda): ";

	Sistema sistema; //Inicializando o Sistema

	principal principal(sistema); //Inicializando o processo principal do sistema.

	principal.iniciar(cin, cout); //Esse comando lê o cin e o cout, executando o método correto e imprimindo as mensagens em seguida.
	
	return 0;
}