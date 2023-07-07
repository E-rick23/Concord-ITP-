#ifndef PRINCIPAL_H
#define PRINCIPAL_H
#include <ostream>
#include <sstream>
#include <istream>
#include "sistema.h"

using namespace std;

class principal {
private:
	Sistema *sistema;
	stringstream ss;
	bool sair = false;

public:
	principal(Sistema& sistema);

	string processar_linha(string linha);
	void iniciar(istream& in, ostream& out);
};
#endif