#ifndef SISTEMA_H
#define SISTEMA_H
#include <map>
#include <vector>
#include <string>
#include "usuario.h"
#include "servidor.h"

using namespace std;

class Sistema {
private:
	vector<Servidor> servers; //Vetor que armazena todos os servidores.
	vector<Usuario> usuarios; //Vetor que armazena os usuários cadastrados.
	map<int,pair<string,string>> usuarios_logados; //Vetor que armazena os usuários que logaram no sistema.
	void salvarUsuarios();
    void salvarServidores();

public:

	void salvar();
	/**
	 * @brief Função que termina o programa.
	 * @return uma string que anuncia o encerramento do programa.
	 */
	string quit();

	/**
	 * @brief Função que exibe a tela de ajuda.
	 * 
	 * @return uma string contendo todos os comandos do programa.
	 */
	string help();

	/**
	 * @brief Função que cria um usuario e retorna uma string com uma mensagem de sucesso ao criar ou um erro.
	 * 
	 * @param email o email que o usuário inseriu
	 * @param senha a senha que o usuário inseriu
	 * @param nome o nome que o usuário inseriu
	 * @return uma string com uma mensagem que diz se o usuario foi criado com sucesso ou nao e, caso tenha tido sucesso, o ID.
	 */
	string create_user(const string email, const string senha, const string nome);

	/**
	 * @brief Função que realiza o login do usuário com email e senha, retorna uma string de erro ou uma mensagem
		login bem sucedido. Quando um usuário loga o sistema deve adicionar o usuário na tabela de usuários logados.
	 * 
	 * @param email o email do usuário, que o usuário insere no login.
	 * @param senha a senha inserida pelo usuário
	 * @return string que contém a confirmação do login, ou um erro.
	 */
	string login(const string email, const string senha);

	/**
	 *  @brief Função que desconecta um usuário específico do sistema, removendo a informação daquele usuário da
		tabela de usuários logados.
	 *	@param id o ID válido de um usuário logado.
	 *	@return Mensagem confirmando o logoff ou uma mensagem de erro caso falhe.
	 */
	string disconnect(int id);

	/**
	 * @brief Função que gera um novo servidor e o adiciona a lista de servidores.
	 * @param id O ID de um usuário logado no sistema.
	 * @param nome O nome do servidor recebido.
	 * @return string confirmação da criação do servidor, ou um erro caso não seja possível criá-lo.
	 */
	string create_server(int id, const string nome);

	/**
	 * @brief Função que altera o código de convite de um servidor.
	 * 
	 * @param id o ID de um usuário logado no sistema.
	 * @param nome o nome de um servidor registrado no sistema
	 * @param codigo o código de convite recebido pelo comando.
	 * @return string confirmação da alteração do código de convite ou erro em caso de falha.
	 */
	string set_server_invite_code(int id, const string nome, const string codigo);

	/**
	 * @brief Função que altera a descrição do servidor para a descrição que o usuário escolher.
	 * 
	 * @param id o ID de um usuário logado no sistema.
	 * @param nome o nome do servidor que terá sua descrição alterada.
	 * @param descricao a descrição que será inserida.
	 * @return string que confirma a alteração ou erro caso não seja possível alterar a descrição.
	 */
	string set_server_desc(int id, const string nome, const string descricao);

	/**
	 * @brief Função que lista os servidores cadastrados no sistema.
	 * 
	 * @param id o ID de um usuário cadastrado e logado no sistema.
	 * @return string com a lista de servidores no sistema ou uma mensagem de erro caso não seja possível gerar a lista.
	 */
	string list_servers(int id);

	/**
	 * @brief Função que remove um servidor da lista de servidores.
	 * 
	 * @param id o ID de um usuário tegistrado e logado no sistema.
	 * @param nome o nome de um servidor registrado no sistema.
	 * @return string com a confirmação da eliminação ou mensagem de erro em caso de falha.
	 */
	string remove_server(int id, const string nome);

	/**
	 * @brief Função que adiciona o usuário logado ao servidor usando o id e o código (caso necessário).
	 * 
	 * @param id o ID do usuário registrado e logado no sistema.
	 * @param nome o nome de um servidor registrado no sistema.
	 * @param codigo o código de convite para o servidor (caso necessário) ou uma string vazia.
	 * @return string com a confirmação de entrada no servidor ou erro caso não seja possível adicionar o usuário no servidor.
	 */
	string enter_server(int id, const string nome, const string codigo);

	/**
	 * @brief Remove o usuário conectado do servidor que ele está logado.
	 * 
	 * @param id um ID válido de um usuário cadastrado e logado no sistema.
	 * @param nome um nome válido de um servidor cadastrado no sistema.
	 * @return string Confirmação que o usuário saiu do servidor, ou um erro, caso não seja possível remover o usuário.
	 */
	string leave_server(int id, const string nome);

	/**
	 * @brief Função que lista os participantes de um servidor que esteja sendo visualizado.
	 * 
	 * @param id de um usuário cadastrado e logado no sistema.
	 * @return string com a lista de usuários no servidor ou erro caso não seja possível gerar a lista.
	 */
	string list_participants(int id);

	/**
	 * @brief Função que lista os usuários do sistema e se estão online ou offline.
	 * @return string com a lista e o status dos usuários.
	*/
	string list_users();
	
	/**
	 * @brief Lista os canais do servidor que o usuário está visualizando.
	 * 
	 * @param id um ID válido do usuário logado.
	 * @return string A lista de canais, ou erro caso não seja possível obter a lista.
	 */
	string list_channels(int id);

	/**
	 * @brief Cria um canal no servidor.
	 * 
	 * @param id um ID válido do usuário logado.
	 * @param nome O nome do novo canal.
	 * @return string Uma string que confirma a criação do canal, ou um erro caso não seja possível criar o canal.
	 */
	string create_channel(int id, const string nome);

	/*! Faz com que o usuário com id dado entre em um canal específico(com seu nome e tipo) ao entrar
		em um canal o sistema deve atualizar a tabela Sistema::usuariosLogados com a informação de
		que o usuário está vizualizando o canal em que entrou. Retorna uma mensagem de sucesso ou
		de erro em caso de falha.
		@param id um id válido de algum usuário cadastrado e logado no sistema.
		@param o nome do canal que deseja entrar,
		@return "Usuário entrou no canal <nome>!" ou uma mensagem de erro em caso de falha.
	*/
	string enter_channel(int id, const string nome);

	/**
	 * @brief Remove o usuário do canal que ele está visualizando atualmente.
	 * 
	 * @param id O ID válido do usuário logado.
	 * @return string com a confirmação de que o usuário saiu do canal, ou uma mensagem de erro não seja possível removê-lo do canal.
	 */
	string leave_channel(int id);

	/**
	 * @brief Envia uma mensagem para o canal que o usuário está visualizando.
	 * 
	 * @param id um ID válido do usuário logado.
	 * @param mensagem A mensagem que será enviada.
	 * @return string uma mensagem de confirmação do envio, ou um erro caso não seja possível enviar a mensagem.
	 */
	string send_message(int id, const string mensagem);
	
	/**
	 * @brief Lista as mensagens de um canal.
	 * 
	 * @param id um ID válido do usuário logado.
	 * @return string a lista de mensagens formatada ou um erro caso não seja possível gerar a lista.
	 */
	string list_messages(int id);
};

#endif