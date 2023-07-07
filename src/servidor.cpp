#include <string>
#include <ostream>
#include <sstream>
#include <algorithm>
#include "servidor.h"
#include "mensagem.h"
#include "canalt.h"

using namespace std;

Servidor::Servidor(int dono_id, string nome)
{
	this->nome = nome;
	this->usuario_dono_id = dono_id;
	this->descricao = "";
	this->convite = "";
	this->participantes_id.push_back(dono_id);
}

string Servidor::get_nome()
{
	return this->nome;
}

int Servidor::get_usuario_dono_id()
{
	return this->usuario_dono_id;
}

string Servidor::get_descricao()
{
	return this->descricao;
}

string Servidor::get_convite()
{
	return this->convite;
}

void Servidor::set_descricao(string descricao)
{
	this->descricao = descricao;
}

void Servidor::set_convite(string convite)
{
	this->convite = convite;
}

void Servidor::add_participante(int id)
{
	this->participantes_id.push_back(id);
}

void Servidor::remove_participante(int id)
{
	auto i = this->participantes_id.begin();
	while (i != this->participantes_id.end()) {
		if (*i == id) {
			this->participantes_id.erase(i);
			return;
		}
		++i;
	}
}

string Servidor::imprimir_participantes(vector<Usuario>& usuarios)
{
	stringstream ss;
	for (auto& user : usuarios) {
		if (this->eh_participante(user.get_id()))
			ss << "-" << user.get_id() << " " << user.get_nome() << endl;
	}

	if (ss.str().empty())
		return "Ninguém está nesse servidor ainda, entre e convide seus amigos!";
	return ss.str();
}

bool Servidor::eh_participante(int id)
{
	for (auto& p_id : this->participantes_id) {
		if (p_id == id)
			return true;
	}
	return false;
}

void Servidor::add_canal_texto(CanalTexto& canal)
{
	this->canais_texto.push_back(canal);
}

void Servidor::remove_canal_texto(string canal)
{
	auto contador = this->canais_texto.begin();
	while (contador != this->canais_texto.end()) {
		//Caso o nome seja encontrado na lista de canais, ele é deletado.
		if (contador->get_nome() == canal) {
			this->canais_texto.erase(contador);
			return;
		}
		++contador;
	}
}

bool Servidor::eh_canal_texto(string canal)
{
	for (auto& textchannel : this->canais_texto) {
		if (textchannel.get_nome() == canal)
			return true;
	}
	return false;
}

string Servidor::imprimir_canais_texto()
{
	stringstream ss;
	for (auto& textchannel : this->canais_texto) {
		ss << "-> " << textchannel.get_nome() << endl;
	}

	if (ss.str().empty())
		return "Não existem canais de texto neste servidor, caso seja o dono, experimente adicionar um!";
	return ss.str();
}

void Servidor::enviar_mensagem(Mensagem& mensagem, string nome_canal)
{
	for (auto& textchannel : this->canais_texto) {
		if (textchannel.get_nome() == nome_canal)
			textchannel.add_mensagem(mensagem);
	}
}

string Servidor::imprimir_mensagens(string canal_texto, vector<Usuario>& usuarios)
{
	for (auto& textchannel : this->canais_texto) {
		if (canal_texto == textchannel.get_nome())
			return textchannel.listar_mensagens(usuarios);
	}
	return "Este canal de texto não existe!";
}



