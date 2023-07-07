#include <istream>
#include <ostream>
#include <iostream>
#include <sstream>
#include <queue>
#include "principal.h"

using namespace std;

// Função que recebe um istringstream e lê todo texto restante até o fim da linha
string resto_de(istringstream &ss)
{
	string resto;
	getline(ss, resto, '\0'); 
	if (resto != "" && (resto[0] == ' ' || resto[0] == '\t')) {
		resto = resto.substr(1); // Eliminar o primeiro caractere caso ele seja um espaço vazio.
	}
	return resto;
}

// Recebe uma referência ao sistema que vai operar e guarda o seu endereço para executar as operações.
principal::principal(Sistema &sistema)
{
	this->sair = false;
	this->sistema = &sistema;
}

// Método que recebe os comandos do usuário e os executa, usando o método equivalente no sistema.
string principal::processar_linha(string linha)
{
	istringstream buf(linha);
	string Cchooser;
	buf >> Cchooser;

	if (Cchooser.empty()) {
		return "Digite um comando!";
	}
	if (Cchooser == "quit" ) {
		this->sair = true;
		return sistema->quit();
	}
	else if(Cchooser == "salvar"){
		 sistema->salvar();
		 return "Arquivos de servidores e usuários salvos!";
	}
	else if (Cchooser == "help") {
		return sistema->help();
	}
	else if (Cchooser == "create-user") {
		string email, senha, nome;
		buf >> email;
		buf >> senha;
		nome = resto_de(buf);
		if (email.empty() || senha.empty() || nome.empty())
			return ">>>Uso: create-user EMAIL SENHA NOME";
		return sistema->create_user(email, senha, nome);
	}
	else if (Cchooser == "login") {
		string email, senha;
		buf >> email;
		buf >> senha;
		if (email.empty() || senha.empty())
			return ">>>Uso: login EMAIL SENHA";
		return sistema->login(email, senha);
	}
	else if (Cchooser == "list-users") {
		return sistema->list_users();
	}

	int id;
	if (!(buf >> id)) {
		return "Este comando precisa ser precedido de um ID [" + Cchooser + "]...";
	}

	if (Cchooser == "disconnect") {
		return sistema->disconnect(id);
	}
	else if (Cchooser == "create-server") {
		string nome;
		buf >> nome;
		if (nome.empty())
			return ">>>Uso: create-server ID NOME";
		return sistema->create_server(id, nome);
	}
	else if (Cchooser == "set-server-desc") {
		string nome, descricao;
		buf >> nome;
		descricao = resto_de(buf);
		if (nome.empty())
			return ">>>Uso: set-server-desc ID NOME [DESCRICAO...]";
		return sistema->set_server_desc(id, nome, descricao);
	}
	else if (Cchooser == "set-server-invite-code") {
		string nome, codigo;
		buf >> nome;
		buf >> codigo;
		if (nome.empty())
			return ">>>Uso: set-server-invite-code ID NOME [CODIGO]";
		return sistema->set_server_invite_code(id, nome, codigo);
	}
	else if (Cchooser == "list-servers") {
		return sistema->list_servers(id);
	}
	else if (Cchooser == "remove-server") {
		string nome;
		buf >> nome;
		if (nome.empty())
			return ">>>Uso: remove-server ID NOME";
		return sistema->remove_server(id, nome);
	}
	else if (Cchooser == "enter-server") {
		string nome, codigo;
		buf >> nome;
		buf >> codigo;
		if (nome.empty())
			return ">>>Uso: enter-server ID NOME [CODIGO]";
		return sistema->enter_server(id, nome, codigo);
	}
	else if (Cchooser == "leave-server") {
		string nome;
		buf >> nome;
		if (nome.empty())
			return ">>>Uso: leave-server ID NOME";
		return sistema->leave_server(id, nome);
	}
	else if (Cchooser == "list-participants") {
		return sistema->list_participants(id);
	}
	else if (Cchooser == "list-channels") {
		return sistema->list_channels(id);
	}
	else if (Cchooser == "create-channel") {
		string nome;
		buf >> nome;
		if (nome.empty())
			return ">>>Uso: create-channel ID NOME";
		return sistema->create_channel(id, nome);
	}
	else if (Cchooser == "enter-channel") {
		string nome;
		buf >> nome;
		if (nome.empty())
			return ">>>Uso: enter-channel ID NOME";
		return sistema->enter_channel(id, nome);
	}
	else if (Cchooser == "leave-channel") {
		return sistema->leave_channel(id);
	}
	else if (Cchooser == "send-message") {
		string mensagem;
		mensagem = resto_de(buf);
		if (mensagem.empty())
			return ">>>Uso: send-message ID MESSAGE...";
		return sistema->send_message(id, mensagem);
	}
	else if (Cchooser == "list-messages") {
		return sistema->list_messages(id);
	}
	else {
		return ">>>Comando não reconhecido [" + Cchooser + "]...";
	}
}

/**
 * @brief Método que recebe por o "cin" e o "cout" no main ele faz o lê 1 comando por linha e o processa,
 *  devolvendo ao output o resultado de cada um.
 */
void principal::iniciar(istream &inputStream, ostream &outputStream) 
{
	string saida, linha;
	this->sair = false;
	while (!this->sair) {
		if (getline(inputStream, linha)) {
			saida = processar_linha(linha);
			outputStream << saida << endl;
		}
	}
}
