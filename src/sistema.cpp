#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <regex>
#include <fstream>
#include "sistema.h"
#include "servidor.h"
#include "usuario.h"

using namespace std;

/**
 * Concatena duas strings "Streamable"
*/
template <typename StreamableT>
string cat(StreamableT s)
{
	stringstream ss;
	ss << s;
	return ss.str();
}

/**
 * Concatena diversas variaveis "Streamable" recursivamente.
*/
template <typename StreamableHead, typename... StreamableTail>
string cat(StreamableHead h, StreamableTail... t)
{
	stringstream ss;
	ss << h;
	return ss.str() + cat(t...);
}

/**
 * @brief Valida o e-mail inserido.
 * 
 * @param email recebe o e-mail digitado pelo usuario 
 * @return true caso o e-mail seja valido
 * @return false caso o e-mail seja invalido
 */
bool email_validate(string email)
{
    const regex email_regex ("\\w+@\\w+\\.[\\w\\.]+"); //cria um formato para o e-mail
    return regex_match(email, email_regex);
}


// Comandos do programa.

string Sistema::quit()
{
	return "Encerrando o programa...";
}

string Sistema::help()
{
	string helpmi = "\n__________________________Lista de comandos___________________________\n\n --- "
					"quit - Encerra o programa.\n --- "
					"create-user <E-mail> <Senha_sem_espaços> <Nome do usuário> - Registra um novo usuário. \n --- "
					"login <E-mail> <senha> - Loga o usuário no sistema.\n --- "
					"disconnect - Desconecta o usuário atual.\n --- "
					"create-server <id> <nome-do-servidor> - Cria um novo servidor.\n --- "
					"set-server-desc <id> <nome-do-servidor> <descrição> - Altera a descrição de um servidor que você é o dono.\n --- "
					"set-server-invite-code <id> <nome-do-servidor> <código-desejado> - Adiciona um código de convite a um servidor, tornando-o privado.\n --- "
					"list-servers <id> - Lista todos os servidores criados.\n --- "
					"remove-server <id> <nome-do-servidor> - Elimina um servidor.\n --- "
					"enter-server <nome-do-servidor> <id> <nome-do-servidor> <código-de-convite> - Entra em um servidor, se ele for público, o código de convite não é necessário.\n --- "
					"leave-server <id> <nome-do-servidor> - Quando estiver dentro do servidor, desconecte-se dele.\n --- "
					"list-participants <id> - Lista todos os participantes de um servidor.\n --- "
					"list-users <id> - Lista os usuários do sistema e exibe seus status.\n --- "
					"create-channel <id> <nome> - Cria um novo canal dentro de um servidor.\n --- "
					"list-channels <id> - Lista os canais do servidor.\n --- "
					"enter-channel <id> - Entra em um canal existente.\n --- "
					"leave-channel <id> - Sai do canal.\n --- "
					"send-message <id> <mensagem> - Envia uma mensagem no canal atual.\n --- "
					"list-messages <id> - Lista todas as mensagens do canal.\n"
					"salvar - Salve os usuários e servidores registrados em arquivos.\n\n"
					"___________________________________________________\n";
	return helpmi;
}

string Sistema::create_user(const string email, const string senha, const string nome)
{
	if(!email_validate(email))
		return "Email inválido!";
	for (auto& user : this->usuarios) {
		if (email == user.get_email())
			return "Já existe uma conta registrada com esse e-mail! Tente logar!";
		if (nome == user.get_nome())
			return "Este nome de usuário já foi utilizado, tente outro!";
	}

	int id = this->usuarios.size() + 1;
	Usuario usuario(id, nome, email, senha);
	this->usuarios.push_back(usuario);
	return cat("Novo usuário registrado! Seu ID: #", id);
}

string Sistema::login(const string email, const string senha)
{
	for (auto& user : this->usuarios) {
		if (email == user.get_email() && !user.same_pw(senha))
			return "Senha incorreta, verifique sua senha e tente novamente!";

		if (email == user.get_email() && user.same_pw(senha)) {
			if (this->usuarios_logados.count(user.get_id()))
				return "Este usuário já está logado!";

			this->usuarios_logados[user.get_id()] = make_pair("","");
			return "Parabéns, você agora está Online!";
		}
	}
	return "Conta não encontrada! Verifique seu e-mail ou cadastre-se!";
}

string Sistema::disconnect(int id)
{
	if (!this->usuarios_logados.count(id))
		return "Este usuário já está desconectado...";

	this->usuarios_logados.erase(id);
	return "Usuário offline!";
}

string Sistema::create_server(int id, const string nome)
{
	if (!this->usuarios_logados.count(id))
		return "Você não está logado!";
	for (auto& server : this->servers) {
		if (nome == server.get_nome())
			return "Já existe um servidor com este nome!";
	}
	Servidor servidor(id, nome);
	this->servers.push_back(servidor);
	return "Servidor criado com sucesso!";
}

string Sistema::remove_server(int id, const string nome)
{
	if (!this->usuarios_logados.count(id))
		return "Você não está logado!";

	auto i = this->servers.begin();
	while (i != this->servers.end()) {
		if (i->get_nome() == nome) {
			if (i->get_usuario_dono_id() != id)
				return "Apenas o dono do servidor pode remover o servidor!";

			for (auto& user: this->usuarios) {
				if (this->usuarios_logados[user.get_id()].first == nome) {
					this->usuarios_logados[user.get_id()].first = "";
					this->usuarios_logados[user.get_id()].second = "";
				}
			}
			this->servers.erase(i);
			return "Servidor removido com sucesso!";
		}
		++i;
	}
	return "Este servidor não existe!";
}

string Sistema::set_server_invite_code(int id, const string nome, const string codigo)
{
	if (!this->usuarios_logados.count(id))
		return "Você não está logado!";

	for (auto& server : this->servers) {
		if (nome == server.get_nome()) {
			if (id != server.get_usuario_dono_id())
				return "Você não é o dono do servidor...";
			server.set_convite(codigo);
			if (codigo == "")
				return cat("Código de convite do servidor \"", server.get_nome(), "\" removido! O servidor agora é público!");
			return cat("Codigo de convite do servidor \"", server.get_nome(),"\" criado! Convide seus amigos! :D");
		}
	}
	return "Este servidor não existe!";
}

string Sistema::set_server_desc(int id, const string nome, const string descricao)
{
	if (!this->usuarios_logados.count(id))
		return "Você não está logado!";
	for (auto& server : this->servers) {
		if (nome == server.get_nome()) {
			if (id != server.get_usuario_dono_id())
				return "Você não é o dono do servidor...";
			server.set_descricao(descricao);
			if (descricao == "")
				return cat(" Descrição do servidor \"", server.get_nome(), "\" removida!");
			return cat("Descrição do servidor \"", server.get_nome(),"\" adicionada!");
		}
	}
	return "Este servidor não existe!";
}

string Sistema::list_servers(int id)
{
	if (this->servers.empty())
		return "Nenhum servidor foi criado ainda...";

	stringstream ss;
	for (auto& server : this->servers) {
		ss << "-> " << server.get_nome() << " [\"" << server.get_descricao() << "\"] ";
		ss << "-> Dono do servidor: " << server.get_usuario_dono_id() << endl;
	}
	return ss.str();
}

string Sistema::enter_server(int id, const string nome, const string codigo)
{
	if (!this->usuarios_logados.count(id))
		return "Você não está logado!";

	for (auto& server : this->servers) {
		if (nome == server.get_nome()) {
			if (this->usuarios_logados[id].first == nome)
				return "Este usuário já está neste servidor!";
			if (id != server.get_usuario_dono_id() && codigo != server.get_convite())
				return "Código de convite inválido, você o digitou corretamente?";
			this->usuarios_logados[id].first = nome;
			this->usuarios_logados[id].second = "";
			if (server.eh_participante(id))
				return "Você entrou no servidor com sucesso!";
			server.add_participante(id);
			return "Você entrou no servidor com sucesso! Bem-vindo!";
		}
	}
	return "Este servidor não existe!";
}

string Sistema::leave_server(int id, const string nome)
{
	if (!this->usuarios_logados.count(id))
		return "Você não está logado!";

	for (auto& server : this->servers) {
		if (nome == server.get_nome()) {
			if (id == server.get_usuario_dono_id())
				return ">>Você não pode remover o dono do servidor!";

			if (!server.eh_participante(id))
				return "Este usuário não participa deste servidor...";

			if (this->usuarios_logados[id].first == nome) {
				this->usuarios_logados[id].first = "";
				this->usuarios_logados[id].second = "";
			}
			server.remove_participante(id);
			return "O usuário foi removido do servidor!";
		}
	}
	return "Este servidor não existe!";
}

string Sistema::list_participants(int id)
{
	if (!this->usuarios_logados.count(id))
		return "Você não está logado!";

	if (this->usuarios_logados[id].first.empty())
		return "O usuário não está visualizando nenhum servidor...";

	for (auto& server : this->servers) {
		if (server.get_nome() == this->usuarios_logados[id].first)
			return server.imprimir_participantes(this->usuarios);
	}
	return "Este servidor não existe!";
}

string Sistema::list_users()
{
	if (this->usuarios.empty())
		return "Nenhum usuário encontrado!";

	stringstream ss;
	for (auto& user : this->usuarios) {
		ss << "#" << user.get_id() << " " << user.get_nome() << " [";

		if (this->usuarios_logados.count(user.get_id())) {
			ss << this->usuarios_logados[user.get_id()].first << " / ";
			ss << this->usuarios_logados[user.get_id()].second << "] ";
			ss << "Atualmente online" << endl;
		} else {
			ss << " / ] " << "Atualmente offline" << endl;
		}
	}
	return ss.str();
}

void Sistema::salvarUsuarios()
{	
	ofstream myfile;
	myfile.open("usuarios.txt", std::ios_base::app);

	int count = 0;
	for (auto& user : this->usuarios){
		count++;
	}
	myfile << "Total de usuários registrados: " << count << endl;
	for (auto& user : this->usuarios) {
		myfile << user.get_id() << endl << user.get_nome() << endl << user.get_email() << endl << user.get_senha() << endl;
	}
}

void Sistema::salvarServidores()
{
	ofstream myfile;
	myfile.open("servidores.txt", std::ios_base::app);

	int count = 0;
	for (auto& server : this->servers){
		count++;
	}
	myfile << "Total de servidores registrados: " << count << endl;

	for (auto& server : this->servers) {
		myfile << server.get_usuario_dono_id() << endl << server.get_nome() << endl << server.get_descricao() << endl << server.get_convite() << endl;
	} 
}

void Sistema::salvar(){
	salvarUsuarios();
	salvarServidores();
}

string Sistema::list_channels(int id)
{
	if (!this->usuarios_logados.count(id))
		return "Você não está logado!";

	if (this->usuarios_logados[id].first.empty())
		return "Você não está visualizando nenhum servidor!";

	for (auto& server : this->servers) {
		if (server.get_nome() == this->usuarios_logados[id].first)
			return server.imprimir_canais_texto();
	}
	return "Este servidor não existe!";
}

string Sistema::create_channel(int id, const string nome)
{
	if (!this->usuarios_logados.count(id))
		return "Você não está logado!";

	if (this->usuarios_logados[id].first.empty())
		return "Você não está visualizando nenhum servidor!";

	for (auto& server : this->servers) {
		if (server.get_nome() == this->usuarios_logados[id].first) {
			if (server.eh_canal_texto(nome))
				return "Já existe um canal com este nome!";

			CanalTexto canal(nome);
			server.add_canal_texto(canal);
			return "Canal criado com sucesso!";
		}
	}
	return "Você não é o dono do servidor...";
}

string Sistema::enter_channel(int id, const string nome)
{
	if (!this->usuarios_logados.count(id))
		return "Você não está logado!";

	if (this->usuarios_logados[id].first.empty())
		return "Você não está visualizando nenhum servidor!";

	if (!this->usuarios_logados[id].second.empty())
		return "Você já está visualizando um canal de texto!";

	for (auto& server : this->servers) {
		if (server.get_nome() == this->usuarios_logados[id].first) {
			if (server.eh_canal_texto(nome)){
				this->usuarios_logados[id].second = nome;
				return cat("O usuário ", nome, " entrou no canal!");
			}
		}
	}
	return "Canal não encontrado!";
}

string Sistema::leave_channel(int id)
{
	if (!this->usuarios_logados.count(id))
		return "Você não está logado!";

	if (this->usuarios_logados[id].first.empty())
		return "Você não está visualizando nenhum servidor!";

	if (this->usuarios_logados[id].second.empty())
		return "Você não está visualizando nenhum canal de texto!";

	string c;
	c = this->usuarios_logados[id].second;
	this->usuarios_logados[id].second = "";
	return cat("Você saiu do canal ", c, "!");

}

string Sistema::send_message(int id, const string conteudo)
{
	if (!this->usuarios_logados.count(id))
		return "Você não está logado!";

	if (this->usuarios_logados[id].second.empty())
		return "Você não está visualizando nenhum canal de texto!";

	for (auto& server : this->servers) {
		if (server.get_nome() == this->usuarios_logados[id].first) {
			if (!server.eh_canal_texto(this->usuarios_logados[id].second))
				return "Este canal não existe!";

			Mensagem mensagem(id, conteudo);
			server.enviar_mensagem(mensagem, this->usuarios_logados[id].second);
			return "Mensagem enviada!";
		}
	}
	return "Este servidor não existe!";
}

string Sistema::list_messages(int id)
{
	if (!this->usuarios_logados.count(id))
		return "Você não está logado!";

	if (this->usuarios_logados[id].first.empty())
		return "Você não está visualizando nenhum servidor!";

	if (this->usuarios_logados[id].second.empty())
		return "Você não está visualizando nenhum canal de texto!";

	for (auto& server : this->servers) {
		if (server.get_nome() == this->usuarios_logados[id].first) {
			return server.imprimir_mensagens(this->usuarios_logados[id].second, this->usuarios);
		}
	}
	return "Este servidor não existe!";
}
