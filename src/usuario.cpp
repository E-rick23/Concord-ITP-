#include <string>
#include "usuario.h"

using namespace std;

Usuario::Usuario(int id, string nome, string email, string senha)
{
	this->id = id;
	this->nome = nome;
	this->email = email;
	this->senha = senha;
}

int Usuario::get_id()
{
	return this->id;
}

string Usuario::get_nome()
{
	return this->nome;
}

string Usuario::get_email()
{
	return this->email;
}

string Usuario::get_senha()
{
	return this->senha;
}

bool Usuario::same_pw(string linha)
{
	return this->senha == linha;
}
